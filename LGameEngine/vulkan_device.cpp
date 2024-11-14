#include "vulkan_device.h"
#include <iostream>

namespace vkHelper {
	VulkanDevice::VulkanDevice(VkPhysicalDevice physicalDevice) {

		this->physicalDevice = physicalDevice;

		// ��ȡ�����豸�� Properties/ Features
		vkGetPhysicalDeviceProperties(physicalDevice, &properties);
		vkGetPhysicalDeviceFeatures(physicalDevice, &features);
		vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memoryProperties);

		// Queue family properties
		uint32_t queueFamilyCount;
		vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);
		queueFamilyProperties.resize(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilyProperties.data());

		// Get list of supported extensions
		uint32_t extCount = 0;
		vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extCount, nullptr);
		if (extCount > 0)
		{
			std::vector<VkExtensionProperties> extensions(extCount);
			if (vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extCount, &extensions.front()) == VK_SUCCESS)
			{
				for (auto& ext : extensions)
				{
					supportedExtensions.push_back(ext.extensionName);
				}
			}
		}

	}

	VulkanDevice::~VulkanDevice() {

	}

	VkResult VulkanDevice::createLogicDevice(VkPhysicalDeviceFeatures enabledFeatures, std::vector<const char*> enabledExtensions, void* pNextChain, bool useSwapChain, VkQueueFlags requestedQueueTypes) {
		std::vector<VkDeviceQueueCreateInfo> queueCreateInfos{};

		const float defaultQueuePriority(0.0f);

		// �� queueFamilyProperties ���ҵ����趨��Ӧ�� queue
		// Graphic Queue: queue�����֪ʶ����ȥ���£�queue�Ƕ�gpu��ײ�ĳ���
		if (requestedQueueTypes & VK_QUEUE_GRAPHICS_BIT) {
			queueFamilyIndices.graphics = getQueueFamilyIndex(VK_QUEUE_GRAPHICS_BIT);
			VkDeviceQueueCreateInfo queueInfo{};
			queueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queueInfo.queueFamilyIndex = queueFamilyIndices.graphics;
			queueInfo.queueCount = 1;
			queueInfo.pQueuePriorities = &defaultQueuePriority;
			queueCreateInfos.push_back(queueInfo);
		}else {
			queueFamilyIndices.graphics = 0;
		}

		// Compute Queue: 
		if (requestedQueueTypes & VK_QUEUE_COMPUTE_BIT) {
			queueFamilyIndices.compute = getQueueFamilyIndex(VK_QUEUE_COMPUTE_BIT);
			if (queueFamilyIndices.compute != queueFamilyIndices.graphics)
			{
				VkDeviceQueueCreateInfo queueInfo{};
				queueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
				queueInfo.queueFamilyIndex = queueFamilyIndices.compute;
				queueInfo.queueCount = 1;
				queueInfo.pQueuePriorities = &defaultQueuePriority;
				queueCreateInfos.push_back(queueInfo);
			}
		}else{
			queueFamilyIndices.compute = queueFamilyIndices.graphics;
		}

		// transfer queue
		if (requestedQueueTypes & VK_QUEUE_TRANSFER_BIT) {
			queueFamilyIndices.transfer = getQueueFamilyIndex(VK_QUEUE_TRANSFER_BIT);
			if ((queueFamilyIndices.transfer != queueFamilyIndices.graphics) && (queueFamilyIndices.transfer != queueFamilyIndices.compute))
			{
				VkDeviceQueueCreateInfo queueInfo{};
				queueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
				queueInfo.queueFamilyIndex = queueFamilyIndices.transfer;
				queueInfo.queueCount = 1;
				queueInfo.pQueuePriorities = &defaultQueuePriority;
				queueCreateInfos.push_back(queueInfo);
			}
		}else {
			queueFamilyIndices.transfer = queueFamilyIndices.graphics;
		}


		// logical device 
		// deviceExtensions
		std::vector<const char*> deviceExtensions(enabledExtensions);
		if (useSwapChain) {
			deviceExtensions.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
		}

		// �����߼��豸 �� create info
		VkDeviceCreateInfo deviceCreateInfo = {};
		deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		deviceCreateInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());;
		deviceCreateInfo.pQueueCreateInfos = queueCreateInfos.data();
		deviceCreateInfo.pEnabledFeatures = &enabledFeatures;

		// Ϊ deviceCreateInfo ���� deviceExtensions
		// �����õ��� supportedExtensions �ڹ��캯���л�ȡ
		if (deviceExtensions.size() > 0) {
			for (const char* enabledExtension : deviceExtensions)
			{
				auto extensionResult = std::find(supportedExtensions.begin(), supportedExtensions.end(), enabledExtension);
				if (extensionResult == supportedExtensions.end()) {
					std::cerr << "Enabled device extension \"" << enabledExtension << "\" is not present at device level" << std::endl;
				}
			}
			deviceCreateInfo.enabledExtensionCount = (uint32_t)deviceExtensions.size();
			deviceCreateInfo.ppEnabledExtensionNames = deviceExtensions.data();
		}
		this->enabledFeatures = enabledFeatures;

		// ���� �߼��豸
		VkResult result = vkCreateDevice(physicalDevice, &deviceCreateInfo, nullptr, &logicalDevice);
		if (result != VK_SUCCESS) {
			return result;
		}

		// Command Pool: ��������ڴ洢�͹��������������
		// Create a default command pool for graphics command buffers
		commandPool = createCommandPool(queueFamilyIndices.graphics);

		return result;
	}


	uint32_t VulkanDevice::getQueueFamilyIndex(VkQueueFlags queueFlags) const {

		// Q: ֱ�� == ������ΪʲôҪ�� & ��
		// �ҵ��豸��֧�� compute ����֧�� graphics �� queue family index 
		if ((queueFlags & VK_QUEUE_COMPUTE_BIT) == queueFlags)
		{
			for (uint32_t i = 0; i < static_cast<uint32_t>(queueFamilyProperties.size()); i++)
			{
				if ((queueFamilyProperties[i].queueFlags & VK_QUEUE_COMPUTE_BIT) && ((queueFamilyProperties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) == 0))
				{
					return i;
				}
			}
		}

		// Dedicated queue for transfer
		// �ҵ��豸��֧�� transfer ����֧�� graphics and compute �� queue family index 
		if ((queueFlags & VK_QUEUE_TRANSFER_BIT) == queueFlags)
		{
			for (uint32_t i = 0; i < static_cast<uint32_t>(queueFamilyProperties.size()); i++)
			{
				if ((queueFamilyProperties[i].queueFlags & VK_QUEUE_TRANSFER_BIT) && ((queueFamilyProperties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) == 0) && ((queueFamilyProperties[i].queueFlags & VK_QUEUE_COMPUTE_BIT) == 0))
				{
					return i;
				}
			}
		}

		// For other queue types or if no separate compute queue is present, 
		// return the first one to support the requested flags
		// ���� queue type
		for (uint32_t i = 0; i < static_cast<uint32_t>(queueFamilyProperties.size()); i++)
		{
			if ((queueFamilyProperties[i].queueFlags & queueFlags) == queueFlags)
			{
				return i;
			}
		}

		return 0;	// ����
	}

	VkCommandPool VulkanDevice::createCommandPool(uint32_t queueFamilyIndex, VkCommandPoolCreateFlags createFlags)
	{
		VkCommandPoolCreateInfo cmdPoolInfo = {};
		cmdPoolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		cmdPoolInfo.queueFamilyIndex = queueFamilyIndex;
		cmdPoolInfo.flags = createFlags;
		VkCommandPool cmdPool;
		vkCreateCommandPool(logicalDevice, &cmdPoolInfo, nullptr, &cmdPool);
		return cmdPool;
	}

}

