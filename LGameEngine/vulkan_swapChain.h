#pragma once

#include <vulkan/vulkan.h>

namespace vkHelper {
	// �����װ swap chain �Ĳ���
	// swap chain: �����ڹ�������Ļ����ʾͼ��Ļ���
	class VulkanSwapChain
	{
	private:
		VkInstance instance;
		VkPhysicalDevice physicalDevice;
		VkDevice device;
		VkSurfaceKHR surface;

	public:
		VkSwapchainKHR swapChain = VK_NULL_HANDLE;

		void init(VkInstance instance, VkPhysicalDevice physicalDevice, VkDevice device);
		// Question: �Ҹ���ô����
		void initSurface();	// TODO: ����surface

		void clean();
	};

}

