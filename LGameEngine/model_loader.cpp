#include "model_loader.h"

// ����ڶ���ļ��ж������˺꣬��ô�ᱨ�� link2005
//// tiny_obj_loader.h ʹ��ǰҪ�ȶ���һ����
//#define TINYOBJLOADER_IMPLEMENTATION
//#include "tiny_obj_loader.h"

namespace GameEngine {

	void ModelLoader::loadModel() {
        //tinyobj::attrib_t attrib;
        //std::vector<tinyobj::shape_t> shapes;
        //std::vector<tinyobj::material_t> materials;
        //std::string warn, err;

        //// tinyobj, loadobj ����
        ////bool res = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, MODEL_PATH.c_str());
        ////if (!res) {
        ////    throw std::runtime_error(warn + err);
        ////}

        //// shape ��ʲô��
        //for (const auto& shape : shapes) {
        //    for (const auto& index : shape.mesh.indices) {
        //        Vertex vertex{};

        //        // ����vertex����
        //        vertex.pos = {
        //        attrib.vertices[3 * index.vertex_index + 0],
        //        attrib.vertices[3 * index.vertex_index + 1],
        //        attrib.vertices[3 * index.vertex_index + 2]
        //        };
        //        vertex.texCoord = {
        //        attrib.texcoords[2 * index.texcoord_index + 0],
        //        1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
        //        };
        //        vertex.color = { 1.0f, 1.0f, 1.0f };

        //        // ����
        //        vertices.push_back(vertex);
        //        indices.push_back(indices.size());
        //    }
        //}

        
	}
}
