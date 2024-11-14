#include "vulkan_swapChain.h"


namespace vkHelper {
	void VulkanSwapChain::init(VkInstance instance, VkPhysicalDevice physicalDevice, VkDevice device) {
		this->instance = instance;
		this->physicalDevice = physicalDevice;
		this->device = device;
	}

	void VulkanSwapChain::initSurface() {
		// TODO: …Ë÷√surface
	}
	
	void VulkanSwapChain::clean() {

	}



}