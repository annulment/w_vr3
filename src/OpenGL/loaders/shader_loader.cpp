#include "..//Renderer/Renderer.h"
#include <fstream>
#include <sstream>
#include "..//..//w_vr3_context/w_vr3_context.h"
#include "..//..//debugger/debugger.h"

w_vr3::gl::shader* w_vr3::gl::shader::load_shader_from_file(const std::string& vertex_file_name, const std::string& fragment_file_name, w_vr3::w_vr3_context* ctx) {
	std::string vertex_code;
	std::string fragment_code;
	std::ifstream vertex_shader_file_stream;
	std::ifstream fargment_shader_file_stream;

	vertex_shader_file_stream.exceptions(std::ifstream::badbit);
	fargment_shader_file_stream.exceptions(std::ifstream::badbit);
	try {
		vertex_shader_file_stream.open(vertex_file_name);
		fargment_shader_file_stream.open(fragment_file_name);
		std::stringstream vertex_shader_stream, fargment_shader_stream;

		vertex_shader_stream << vertex_shader_file_stream.rdbuf();
		fargment_shader_stream << fargment_shader_file_stream.rdbuf();

		vertex_shader_file_stream.close();
		fargment_shader_file_stream.close();

		vertex_code = vertex_shader_stream.str();
		fragment_code = fargment_shader_stream.str();
	}
	catch (std::ifstream::failure& e) {
		std::string error_string = "[w_vr3][opengl][core] cannot load shaders from file: \n";
		error_string += e.what();

		auto debug = ctx->get_debugger();
		debug->error(error_string.c_str());

		return nullptr;
	}

	if (vertex_code.empty() || fragment_code.empty()) {
		std::string error_string = "[w_vr3][opengl][core] file don't readed!\n";

		auto debug = ctx->get_debugger();
		debug->error(error_string.c_str());

		return nullptr;
	}

	w_vr3::gl::shader* tmp_shader = new w_vr3::gl::shader();
	
	auto code = tmp_shader->compile(vertex_code.c_str(), fragment_code.c_str(), ctx);

	if (code != w_vr3::gl::w_vr3_shader_compilation_status::w_vr3_shader_compilation_status_success)
		return nullptr;

	return tmp_shader;
}