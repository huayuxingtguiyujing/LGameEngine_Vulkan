#pragma once


//#include "vulkan_RHI.h"

#include "windowSystem.h"
#include "renderSystem.h"

namespace GameEngine {

	class Engine
	{
	public:
		bool init();
		void tick();
		void end();

	private:
		WindowSystem windowSystem;

		RenderSystem renderSystem;
		//VulkanRHI vulkanRHI;


	};

}