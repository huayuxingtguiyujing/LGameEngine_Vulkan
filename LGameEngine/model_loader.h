#pragma once
#include <cstdint>
#include <string>
#include <vector>
//#include "vulkan_triangle.h"


namespace GameEngine {

	class ModelLoader
	{

		const uint32_t WIDTH = 800;
		const uint32_t HEIGHT = 600;

		const std::string MODEL_PATH = "models/viking_room.obj";
		const std::string TEXTURE_PATH = "textures/viking_room.png";

		//std::vector<Vertex> vertices;
		//std::vector<uint32_t> indices;
		//VkBuffer vertexBuffer;
		//VkDeviceMemory vertexBufferMemory;

		void loadModel();

	};
}


