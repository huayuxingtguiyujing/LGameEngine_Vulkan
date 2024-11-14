#pragma once

#include <vulkan/vulkan.h>

namespace vkHelper {
	// 此类封装 swap chain 的操作
	// swap chain: 是用于管理在屏幕上显示图像的机制
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
		// Question: 我该怎么做？
		void initSurface();	// TODO: 设置surface

		void clean();
	};

}

