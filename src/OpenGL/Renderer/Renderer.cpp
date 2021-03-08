#include "Renderer.h"

#include "..//..//debugger/debugger.h"
#include "..//..//w_vr3_context/w_vr3_context.h"
#include <glm/gtc/type_ptr.hpp>

w_vr3::w_vr3_operation_status w_vr3::gl::init(w_vr3::w_vr3_context* ctx) {
	
	glewExperimental = GL_TRUE;
	GLenum code = glewInit();

	if (code != GLEW_OK) {
		auto debug = ctx->get_debugger();
		std::string error_string;
		error_string = "can't initialize glew:\n";
		error_string += (const char*)glewGetString(code);
		debug->debug(error_string.c_str(), code);

		return w_vr3::w_vr3_operation_status::w_vr3_operation_status_error;
	}

	return w_vr3::w_vr3_operation_status::w_vr3_operation_status_success;
}

void w_vr3::gl::clear_color(const float red, const float green, const float blue, const float alpha){
	glClearColor(red, green, blue, alpha);
}

void w_vr3::gl::clear(GLuint mask) {
	glClear(mask);
}

w_vr3::gl::VAO::VAO()
	: indices_buffer(0), indices_count(0){
	glGenVertexArrays(1, &vao);
	bind();
}

void w_vr3::gl::VAO::bind(){
	glBindVertexArray(vao);
}

void w_vr3::gl::VAO::draw(GLenum primitive, int count){
	bind();
	for (size_t i = 0; i < buffers.size(); i++) {
		glEnableVertexAttribArray(i);
	}
	glDrawArrays(primitive, 0, count);
	for (size_t i = 0; i < buffers.size(); i++) {
		glDisableVertexAttribArray(i);
	}
}

void w_vr3::gl::VAO::draw(int count){
	bind();
	for (size_t i = 0; i < buffers.size(); i++) {
		glEnableVertexAttribArray(i);
	}
	glDrawArrays(GL_TRIANGLES, 0, count);
	for (size_t i = 0; i < buffers.size(); i++) {
		glDisableVertexAttribArray(i);
	}
}

void w_vr3::gl::VAO::draw_elements(GLenum primitive, int count){
	assert(indices_buffer != 0);
	bind();

	for (size_t i = 0; i < buffers.size(); ++i){
		glEnableVertexAttribArray(i);
	}
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_buffer);
	glDrawElements(primitive, indices_count, GL_UNSIGNED_INT, nullptr);

	for (size_t i = 0; i < buffers.size(); ++i){
		glDisableVertexAttribArray(i);
	}
}

void w_vr3::gl::VAO::add_object(const std::vector<float>& data){
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(buffers.size(), 1, GL_FLOAT, GL_FALSE, 0, nullptr);
	buffers.push_back(vbo);
}

void w_vr3::gl::VAO::add_object(const std::vector<float>& data, int count){
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(buffers.size(), count, GL_FLOAT, GL_FALSE, 0, nullptr);
	buffers.push_back(vbo);
}

template<class type>
inline void w_vr3::gl::VAO::add_object(const std::vector<type>& data, int count) {
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(type), data.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(buffers.size(), count, GL_FLOAT, GL_FALSE, 0, nullptr);
	buffers.push_back(vbo);
}

void w_vr3::gl::VAO::add_object(const std::vector<glm::vec2>& data) {
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(glm::vec2), data.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(buffers.size(), 2, GL_FLOAT, GL_FALSE, 0, nullptr);
	buffers.push_back(vbo);
}

void w_vr3::gl::VAO::add_object(const std::vector<glm::vec3>& data) {
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(glm::vec3), data.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(buffers.size(), 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	buffers.push_back(vbo);
}

void w_vr3::gl::VAO::add_object(const std::vector<glm::vec4>& data) {
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(glm::vec4), data.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(buffers.size(), 4, GL_FLOAT, GL_FALSE, 0, nullptr);
	buffers.push_back(vbo);
}

void w_vr3::gl::VAO::add_indices(const std::vector<unsigned>& data){
	assert(indices_buffer == 0);
	
	indices_count = data.size();

	glGenBuffers(1, &indices_buffer);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(unsigned), data.data(), GL_STATIC_DRAW);
}

void w_vr3::gl::VAO::clear_indices_buffer(){
	assert(indices_buffer != 0);
	glDeleteBuffers(1, &indices_buffer);
	indices_buffer = 0;
	indices_count = 0;
}

w_vr3::gl::VAO::~VAO(){
	glDeleteBuffers(buffers.size(), buffers.data());
	if(indices_buffer != 0)
		glDeleteBuffers(1, &indices_buffer);
	glDeleteVertexArrays(1, &vao);
}

void w_vr3::gl::VAO::unbind(){
	glBindVertexArray(0);
}

w_vr3::gl::shader::shader(const GLchar* vertex_data, const GLchar* fragment_data, w_vr3_context* ctx){
	this->compile(vertex_data, fragment_data, ctx);
}

w_vr3::gl::shader::shader(GLuint id)
	:id(id){
}

w_vr3::gl::shader::shader(){

}

w_vr3::gl::w_vr3_shader_compilation_status w_vr3::gl::shader::compile(const GLchar* vertex_data, const GLchar* fragment_data, w_vr3_context* ctx){
	GLuint vertex_shader_id, fragment_shader_id;
	GLint status;

	// compiling vertex shader
	vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader_id, 1, &vertex_data, nullptr);
	glCompileShader(vertex_shader_id);
	glGetShaderiv(vertex_shader_id, GL_COMPILE_STATUS, &status);
	if (!status) {
		GLchar infolog[512];
		glGetShaderInfoLog(vertex_shader_id, 512, nullptr, infolog);

		std::string debug_string = "[w_vr3][opengl][core]vertex shader compilation error:\n";
		debug_string += infolog;

		auto debug = ctx->get_debugger();
		debug->error(debug_string.c_str());
		
		return w_vr3::gl::w_vr3_shader_compilation_status::w_vr3_shader_compilation_status_error_vertex_shader;
	}

	// compiling fragment shader
	fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader_id, 1, &fragment_data, nullptr);
	glCompileShader(fragment_shader_id);
	glGetShaderiv(fragment_shader_id, GL_COMPILE_STATUS, &status);
	if (!status) {
		GLchar infolog[512];
		glGetShaderInfoLog(fragment_shader_id, 512, nullptr, infolog);

		std::string debug_string = "[w_vr3][opengl][core]fragment shader compilation error:\n";
		debug_string += infolog;

		auto debug = ctx->get_debugger();
		debug->error(debug_string.c_str());

		return w_vr3::gl::w_vr3_shader_compilation_status::w_vr3_shader_compilation_status_error_fragment_shader;
	}

	id = glCreateProgram();
	glAttachShader(id, vertex_shader_id);
	glAttachShader(id, fragment_shader_id);

	glLinkProgram(id);
	glGetProgramiv(id, GL_LINK_STATUS, &status);
	if (!status) {
		GLchar infolog[512];
		glGetProgramInfoLog(id, 512, nullptr, infolog);
		glDeleteShader(vertex_shader_id);
		glDeleteShader(fragment_shader_id);

		std::string debug_string = "[w_vr3][opengl][core]program linking failed:\n";
		debug_string += infolog;

		auto debug = ctx->get_debugger();
		debug->error(debug_string.c_str());

		return w_vr3::gl::w_vr3_shader_compilation_status::w_vr3_shader_compilation_status_linking_error;
	}

	return w_vr3::gl::w_vr3_shader_compilation_status::w_vr3_shader_compilation_status_success;
}

void w_vr3::gl::shader::use(){
	glUseProgram(id);
}

GLuint w_vr3::gl::shader::get_location(const std::string& name){
	return glGetUniformLocation(id, name.c_str());
}

void w_vr3::gl::shader::unbind(){
	glUseProgram(0);
}

void w_vr3::gl::shader::set_uniform_int(GLuint location, const int value){
	glUniform1i(location, value);
}

void w_vr3::gl::shader::set_uniform_int_array(GLuint location, const int* value, const size_t count){
	glUniform1iv(location, count, value);
}

void w_vr3::gl::shader::set_uniform_float(GLuint location, const float value){
	glUniform1f(location, value);
}

void w_vr3::gl::shader::set_uniform_float_array(GLuint location, const float* value, const size_t count){
	glUniform1fv(location, count, value);
}

void w_vr3::gl::shader::set_uniform_float2(GLuint location, const glm::vec3& value){
	glUniform2f(location, value.x, value.y);
}

void w_vr3::gl::shader::set_uniform_float3(GLuint location, const glm::vec3& value){
	glUniform3f(location, value.x, value.y, value.z);
}

void w_vr3::gl::shader::set_uniform_float4(GLuint location, const glm::vec4& value){
	glUniform4f(location, value.x, value.y, value.z, value.w);
}

void w_vr3::gl::shader::set_uniform_mat3(GLuint location, const glm::mat3& value){
	glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void w_vr3::gl::shader::set_uniform_mat4(GLuint location, const glm::mat4& value){
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

GLuint w_vr3::gl::shader::get_id(){
	return id;
}

w_vr3::gl::shader::~shader(){
	glDeleteProgram(id);
}


