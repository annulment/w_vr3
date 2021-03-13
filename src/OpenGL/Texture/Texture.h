#ifndef _W_VR3_OPENGL_TEXUTRE_H
#define _W_VR3_OPENGL_TEXUTRE_H

#define GLEW_STATIC
#include<gl/glew.h>

#include<string>

#include"..//..//w_vr3/w_vr3.h"

namespace w_vr3 {
	namespace gl {
		enum  w_vr3_texture_type {
			w_vr3_texture_type_rgb = 0,
			w_vr3_texture_type_rgba = 1
		};

		class Texture {

			GLuint id;
			int width, height;

		public:

			Texture(GLuint id);
			Texture(const unsigned char* data, int width, int height, w_vr3::gl::w_vr3_texture_type t_type = w_vr3::gl::w_vr3_texture_type::w_vr3_texture_type_rgb);
			Texture();

			void create(const unsigned char* data, int width, int height, w_vr3::gl::w_vr3_texture_type t_type = w_vr3::gl::w_vr3_texture_type::w_vr3_texture_type_rgb);

			void bind();

			static void unbind();

			~Texture();

			static w_vr3::gl::Texture* load_from_file(const std::string& file_name, w_vr3::gl::w_vr3_texture_type t_type = w_vr3::gl::w_vr3_texture_type::w_vr3_texture_type_rgb);
		};
	}
}

#endif