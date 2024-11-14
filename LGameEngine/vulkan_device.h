#pragma once

#include <vector>
#include <string>

#include "vulkan/vulkan.h"

namespace vkHelper {
	// �ýṹ ר������ �� �����豸תΪ�߼��豸
	struct VulkanDevice
	{
		// --------�����豸--------
		VkPhysicalDevice physicalDevice;
		// Properties
		VkPhysicalDeviceProperties properties;
		// Features
		VkPhysicalDeviceFeatures features;
		// Enable Features
		VkPhysicalDeviceFeatures enabledFeatures;
		// MemoryProperties
		VkPhysicalDeviceMemoryProperties memoryProperties;

		// --------�߼��豸--------
		VkDevice logicalDevice;
		std::vector<VkQueueFamilyProperties> queueFamilyProperties;
		std::vector<std::string> supportedExtensions;

		VkCommandPool commandPool = VK_NULL_HANDLE;

		// ���ڼ�¼ queue family index
		struct {
			uint32_t graphics;
			uint32_t compute;
			uint32_t transfer;
		} queueFamilyIndices;

		explicit VulkanDevice(VkPhysicalDevice physicalDevice);
		~VulkanDevice();
		VkResult createLogicDevice(VkPhysicalDeviceFeatures enabledFeatures, std::vector<const char*> enabledExtensions, void* pNextChain, 
			bool useSwapChain = true, VkQueueFlags requestedQueueTypes = VK_QUEUE_GRAPHICS_BIT | VK_QUEUE_COMPUTE_BIT);


		uint32_t getQueueFamilyIndex(VkQueueFlags queueFlags) const;

		VkCommandPool   createCommandPool(uint32_t queueFamilyIndex, VkCommandPoolCreateFlags createFlags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT);
	};

}
