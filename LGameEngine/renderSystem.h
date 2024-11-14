#pragma once
#include "vulkan_RHI.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

// NOTE: renderSystem 用于实现游戏引擎的渲染部分
// renderHandler 作为渲染器的渲染功能组件

// NOTE: 所有游戏引擎的组件 都应该加入到 GameEngine 空间中
namespace GameEngine {

// RenderPipeline
//-------------------------------------------------
	class RenderPipelineBase {
		friend class RenderSystem;
	public:
		
		virtual ~RenderPipelineBase() {}

		virtual void initialize() = 0;
		virtual void clear() {};

		// virtual void 
		virtual void preparePassData() = 0;

		virtual void forwardRender() = 0;

	};

	class RenderPipeline : RenderPipelineBase {

		// final: 防止被覆写; override: 覆盖
		virtual void initialize() override final;

		// virtual void 
		virtual void preparePassData() override final;

		virtual void forwardRender()  override final;
	};

	// RHI
//-------------------------------------------------
	// render hardware interface
	class RHI {
	public:
		virtual ~RHI() = 0;
		virtual void initialize() = 0;
	};

	// 封装 vulkan 的 buffer
	class RHIBuffer {
	};

	class VulkanBuffer : RHIBuffer {
	public:
		VkBuffer resource;
	};

//-------------------------------------------------

	enum class RenderCameraType : int {
		Editor,
		Motor
	};

	class RenderCamera {
	public:

		RenderCameraType current_camera_type{ RenderCameraType ::Editor};

		static const glm::vec3 X, Y, Z;

		// 相机基本参数
		glm::vec3 position{ 0.0f,0.0f,0.0f };
		glm::quat rotation{ 1.0f, 0.0f, 0.0f, 0.0f };
		glm::quat inv_rotation{ 1.0f, 0.0f, 0.0f, 0.0f };
		float znear{ 1000.0f };
		float zfar{ 0.1f };
		glm::vec3 up_axis{ Z };

		float aspect{ 0.f };
		float fovx{ 89.f };
		float fovy{ 0.f };

		// FOV 参数
		static constexpr float MIN_FOV{ 10.0f };
		static constexpr float MAX_FOV{ 89.0f };

		static constexpr int   MAIN_VIEW_MATRIX_INDEX{ 0 };	// ?

		std::vector<glm::mat4> view_matrices{ glm::mat4(1.0f)};

		
		void move(glm::vec3 delta);
		void rotate(glm::vec2 delta);
		void zoom(float offset);
		void lookAt(const glm::vec3& position, const glm::vec3& target, const glm::vec3& up);
		
		
		// set get
		void setCurrentCameraType(RenderCameraType type);
		void setMainViewMatrix(const glm::mat4& view_matrix, RenderCameraType type = RenderCameraType::Editor);

		void setAspect(float aspect);

	};

	// TODO: 这是什么技巧？
	inline const glm::vec3  RenderCamera::X = { 1.0f, 0.0f, 0.0f };
	inline const glm::vec3  RenderCamera::Y = { 0.0f, 1.0f, 0.0f };
	inline const glm::vec3  RenderCamera::Z = { 0.0f, 0.0f, 1.0f };

//-------------------------------------------------
	// 模型的mesh数据实际存储的地方
	struct VulkanMesh {
		bool enable_vertex_blending;

		//

		//

	};


	// mesh 的 node，存放各种与渲染模型相关的数据
	struct RenderMeshNode
	{
		const glm::mat4* model_matrix{ nullptr };
		const glm::mat4* joint_matrices{ nullptr };	// ？关节？
		uint32_t           joint_count{ 0 };		// ？

		// Mesh 与 material 的数据存储区域

		VulkanMesh* ref_mesh{ nullptr };
		//VulkanPBRMaterial* ref_material{ nullptr };

		uint32_t           node_id;
		bool               enable_vertex_blending{ false };
	};

	class RenderEntity {
	public:
		uint32_t instance_id{ 0 };
		glm::mat4 model_matrix{ glm::mat4(1.0f) };

		// Mesh


		// Material


	};

	class RenderScene{

		// TODO: scene light;

		// render entities;
		std::vector<RenderEntity> render_entities;

		std::vector<RenderEntity> render_axis;

		// 所有可见的节点
		std::vector<RenderMeshNode> all_visible_mesh_nodes;

	};


//-------------------------------------------------
	class RenderSystem
	{
	public:
		RenderSystem();
		~RenderSystem();

		bool initRender(GameEngine::WindowSystem* windowSystem);
		void render();
		void endRender();


	private:
		void processSwapData();

		VulkanRHI vulkanRHI;

		// 场景 Camera
		
		// 当前要渲染的场景
		// 封装了 rhi 的渲染所需资源
		// 封装了 rhi 的渲染管线

	};

}

