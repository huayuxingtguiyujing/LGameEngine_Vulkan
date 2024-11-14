#pragma once
#include "vulkan_RHI.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

// NOTE: renderSystem ����ʵ����Ϸ�������Ⱦ����
// renderHandler ��Ϊ��Ⱦ������Ⱦ�������

// NOTE: ������Ϸ�������� ��Ӧ�ü��뵽 GameEngine �ռ���
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

		// final: ��ֹ����д; override: ����
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

	// ��װ vulkan �� buffer
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

		// �����������
		glm::vec3 position{ 0.0f,0.0f,0.0f };
		glm::quat rotation{ 1.0f, 0.0f, 0.0f, 0.0f };
		glm::quat inv_rotation{ 1.0f, 0.0f, 0.0f, 0.0f };
		float znear{ 1000.0f };
		float zfar{ 0.1f };
		glm::vec3 up_axis{ Z };

		float aspect{ 0.f };
		float fovx{ 89.f };
		float fovy{ 0.f };

		// FOV ����
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

	// TODO: ����ʲô���ɣ�
	inline const glm::vec3  RenderCamera::X = { 1.0f, 0.0f, 0.0f };
	inline const glm::vec3  RenderCamera::Y = { 0.0f, 1.0f, 0.0f };
	inline const glm::vec3  RenderCamera::Z = { 0.0f, 0.0f, 1.0f };

//-------------------------------------------------
	// ģ�͵�mesh����ʵ�ʴ洢�ĵط�
	struct VulkanMesh {
		bool enable_vertex_blending;

		//

		//

	};


	// mesh �� node����Ÿ�������Ⱦģ����ص�����
	struct RenderMeshNode
	{
		const glm::mat4* model_matrix{ nullptr };
		const glm::mat4* joint_matrices{ nullptr };	// ���ؽڣ�
		uint32_t           joint_count{ 0 };		// ��

		// Mesh �� material �����ݴ洢����

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

		// ���пɼ��Ľڵ�
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

		// ���� Camera
		
		// ��ǰҪ��Ⱦ�ĳ���
		// ��װ�� rhi ����Ⱦ������Դ
		// ��װ�� rhi ����Ⱦ����

	};

}

