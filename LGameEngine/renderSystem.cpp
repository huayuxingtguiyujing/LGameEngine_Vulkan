#include "RenderSystem.h"

#include <iostream>



namespace GameEngine {


	//-----------------------------------------
	// TODO: complete this!
	void RenderCamera::move(glm::vec3 delta) {

	}
	void RenderCamera::rotate(glm::vec2 delta) {

	}
	void RenderCamera::zoom(float offset) {

	}
	void RenderCamera::lookAt(const glm::vec3& position, const glm::vec3& target, const glm::vec3& up) {

	}


	// set get
	void RenderCamera::setCurrentCameraType(RenderCameraType type) {
		current_camera_type = type;
	}
	void RenderCamera::setMainViewMatrix(const glm::mat4& view_matrix, RenderCameraType type ) {
		current_camera_type = type;
		view_matrices[0] = view_matrix;

		// 通过相机的变换矩阵计算当前位置
		glm::vec3 s = glm::vec3(view_matrix[0][0], view_matrix[0][1], view_matrix[0][2]);
		glm::vec3 u = glm::vec3(view_matrix[1][0], view_matrix[1][1], view_matrix[1][2]);
		glm::vec3 f = glm::vec3(-view_matrix[2][0], -view_matrix[2][1], -view_matrix[2][2]);
		position = s * (-view_matrix[0][3]) + u * (-view_matrix[1][3]) + f * view_matrix[2][3];
	}

	void RenderCamera::setAspect(float aspect) {
		// TODO: Aspect
		this->aspect = aspect;

	}


	//------------------------------------------
	RenderSystem::RenderSystem() {
	}
	RenderSystem::~RenderSystem() {
	}

	bool RenderSystem::initRender(GameEngine::WindowSystem* windowSystem) {
		vulkanRHI.initVulkan(windowSystem);

		std::cout << "renderSystem 成功初始化" << std::endl;
		return true;
	}

	void RenderSystem::render() {
		vulkanRHI.renderFrame();
	}

	void RenderSystem::endRender() {
		vulkanRHI.endVulkan();
	}

}