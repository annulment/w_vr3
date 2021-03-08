#ifndef _INC_W_VR3_GL_RENDERER_H
#define _INC_W_VR3_GL_RENDERER_H

#include <w_vr3/w_vr3.h>
#include <vector>
#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>

namespace w_vr3 {
	class w_vr3_context;

	namespace gl {
		enum w_vr3_shader_compilation_status : uint8_t {
			w_vr3_shader_compilation_status_success = w_vr3::w_vr3_operation_status::w_vr3_operation_status_success,
			w_vr3_shader_compilation_status_error_vertex_shader = 2,
			w_vr3_shader_compilation_status_error_fragment_shader = 3,
			w_vr3_shader_compilation_status_linking_error = 4
		};

		w_vr3::w_vr3_operation_status init(w_vr3::w_vr3_context* ctx);

		void clear_color(const float red, const float green, const float blue, const float alpha);
		void clear(GLuint mask);

		class VAO {
			GLuint vao;
			std::vector<GLuint> buffers;

			GLuint indices_buffer;
			size_t indices_count;

		public:

			VAO();

			void bind();

			void draw(GLenum primitive, int count);
			void draw(int count);

			void draw_elements(GLenum primitive, int count);

			void add_object(const std::vector<float>& data);
			void add_object(const std::vector<float>& data, int count);
			template<class type>
			void add_object(const std::vector<type>& data, int count);
			void add_object(const std::vector<glm::vec2>& data);
			void add_object(const std::vector<glm::vec3>& data);
			void add_object(const std::vector<glm::vec4>& data);

			void add_indices(const std::vector<unsigned>& data);

			void clear_indices_buffer();

			~VAO();

			static void unbind();
		};

		class shader {
			GLuint id;

		public:
			shader(const GLchar* vertex_data, const GLchar* fragment_data, w_vr3_context* ctx);
			shader(GLuint id);
			shader();

			w_vr3::gl::w_vr3_shader_compilation_status compile(const GLchar* vertex_data, const GLchar* fragment_data, w_vr3_context* ctx);

			void use();

			GLuint get_location(const std::string& name);

			static void unbind();

			void set_uniform_int(GLuint location, const int value);
			void set_uniform_int_array(GLuint location, const int* value, const size_t count);
			void set_uniform_float(GLuint location, const float value);
			void set_uniform_float_array(GLuint location, const float* value, const size_t count);
			void set_uniform_float2(GLuint location, const glm::vec3& value);
			void set_uniform_float3(GLuint location, const glm::vec3& value);
			void set_uniform_float4(GLuint location, const glm::vec4& value);
			void set_uniform_mat3(GLuint location, const glm::mat3& value);
			void set_uniform_mat4(GLuint location, const glm::mat4& value);

			GLuint get_id();

			~shader();

			static w_vr3::gl::shader* load_shader_from_file(const std::string& vertex_file_name, const std::string& fragment_file_name, w_vr3::w_vr3_context* ctx);
		};
	}
}

#endif