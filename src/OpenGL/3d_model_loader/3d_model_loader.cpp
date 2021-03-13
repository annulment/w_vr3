#include "3d_model_loader.h"

#include <cstdio>
#include <string>

#include <glm/glm.hpp>
#include <vector>

#include "..//Renderer/Renderer.h"

uint8_t w_vr3::d3_model_loader::d3_model_loader::load_obj(const char* file_name) {

	FILE* file = fopen(file_name, "r");
	if (file == NULL) {
		return 3;
	}

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	std::vector<unsigned int>vertex_indices, uv_indices, normal_indices;


	while (1) {
		char line[128];
		int res = fscanf(file, "%s", line);
		if (res == EOF) {
			break;
		}

		if (strcmp(line, "v") == 0) {
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			vertices.push_back(vertex);
		}
		else if (strcmp(line, "vt") == 0) {
			glm::vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			uv.y = -uv.y;
			uvs.push_back(uv);
		}
		else if (strcmp(line, "vn") == 0) {
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			normals.push_back(normal);
		}
		else if (strcmp(line, "f") == 0) {
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9) {
				printf("File can't be read by our simple parser : ( Try exporting with other options\n");
				return 4;
			}

			vertex_indices.push_back(vertexIndex[0]);
			vertex_indices.push_back(vertexIndex[1]);
			vertex_indices.push_back(vertexIndex[2]);
			uv_indices.push_back(uvIndex[0]);
			uv_indices.push_back(uvIndex[1]);
			uv_indices.push_back(uvIndex[2]);
			normal_indices.push_back(normalIndex[0]);
			normal_indices.push_back(normalIndex[1]);
			normal_indices.push_back(normalIndex[2]);
		}
		else {
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}
	}
	
	std::vector<glm::vec3> final_vertices;
	std::vector<glm::vec2> final_uvs;
	std::vector<glm::vec3> final_normals;


	for (unsigned int i = 0; i < vertex_indices.size(); i++) {


		unsigned int vertexIndex = vertex_indices[i];
		unsigned int uvIndex = uv_indices[i];
		unsigned int normalIndex = normal_indices[i];


		glm::vec3 vertex = vertices[vertexIndex - 1];
		glm::vec2 uv = uvs[uvIndex - 1];
		glm::vec3 normal = normals[normalIndex - 1];


		final_vertices.push_back(vertex);
		final_uvs.push_back(uv);
		final_normals.push_back(normal);

	}

	fclose(file);

	models.push_back(new w_vr3::d3_model_loader::d3_model(final_vertices, final_uvs, final_normals));

	normal_indices.clear();
	vertex_indices.clear();
	uv_indices.clear();

	vertices.clear();
	normals.clear();
	uvs.clear();

	return 1;
}

uint8_t w_vr3::d3_model_loader::d3_model_loader::load(const char* file_name, w_vr3::d3_model_loader::d3_model_loader_file_type f_type) {

	switch (f_type) {
	case w_vr3::d3_model_loader::d3_model_loader_file_type_none:
		return 2;
		break;
	case w_vr3::d3_model_loader::d3_model_loader_file_type_obj:

		return this->load_obj(file_name);

		break;
	default:
		return 2;
		break;
	}

	return 1;
}

void w_vr3::d3_model_loader::d3_model_loader::unload_all_model(){
	for (size_t i = 0; i < models.size(); i++){
		if (!IS_PTR_EMPTY(models[i])) {
			delete models[i];
		}
	}
}

w_vr3::d3_model_loader::d3_model* w_vr3::d3_model_loader::d3_model_loader::get_model(uint32_t model_id){
	assert(model_id < models.size());
	return models[model_id];
}

w_vr3::d3_model_loader::d3_model::d3_model(std::vector<glm::vec3>& vertices, std::vector<glm::vec2>& uvs, std::vector<glm::vec3>& normals){
	vao = new w_vr3::gl::VAO();

	vao->add_object(vertices);
	vao->add_object(uvs);
	vao->add_object(normals);

	vertices_count = vertices.size();
}

w_vr3::d3_model_loader::d3_model::~d3_model(){
	delete vao;
}

void w_vr3::d3_model_loader::d3_model::draw(){
	vao->draw(GL_TRIANGLES, vertices_count);
}
