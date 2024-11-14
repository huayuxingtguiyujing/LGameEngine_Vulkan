#pragma once
#include <string>
#include <glm/glm.hpp>
#include <glm/ext/matrix_float4x4.hpp>


namespace GameEngine {
	
	struct Joint {
		const std::string m_joint_name;

		uint32_t m_parent_joint_index;
		
		glm::mat4 m_bind_pose_translation;
	
	};

	struct Skeletion {

	};

}


