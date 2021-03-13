#ifndef _INC_W_VR3_3D_MODEL_LOADER_H
#define _INC_W_VR3_3D_MODEL_LOADER_H

#include<inttypes.h>

#include <glm/glm.hpp>
#include <vector>

#define IS_PTR_EMPTY(ptr)(ptr)

namespace w_vr3 {
	namespace gl {
		class VAO;
	}

	namespace d3_model_loader {

		enum d3_model_loader_file_type : uint8_t {
			d3_model_loader_file_type_none = 0,
			d3_model_loader_file_type_obj = 1
		};

		enum d3_model_loader_load_status : uint8_t {
			d3_model_loader_load_status_success = 1,
			d3_model_loader_load_status_unsupported_file_type = 2,
			d3_model_loader_load_status_cannot_open_file = 3,
			d3_model_loader_load_status_parser_error = 4
		};

		class d3_model {

			w_vr3::gl::VAO* vao;

			unsigned int vertices_count;

		public:

			d3_model(std::vector<glm::vec3>& vertices, std::vector<glm::vec2>& uvs, std::vector<glm::vec3>& normals, std::vector<unsigned int>vertex_indices);

			~d3_model();

			void draw();
		};

		class d3_model_loader {

			uint8_t load_obj(const char* file_name);

			std::vector<d3_model*>models;

		public:

			uint8_t load(const char* file_name, w_vr3::d3_model_loader::d3_model_loader_file_type f_type = d3_model_loader_file_type_none);

			void unload_all_model();

			d3_model* get_model(uint32_t model_id);
		};
	}
}

#endif