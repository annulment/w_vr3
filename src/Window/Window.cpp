#include "Window.h"
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "..//w_vr3_context/w_vr3_context.h"
#include "..//debugger/debugger.h"
#include "..//Events/Events.h"

w_vr3::w_vr3_operation_status w_vr3::Window::create(const std::string& title, w_vr3::w_vr3_window_configuration configuration,
	const int width, const int height, w_vr3::w_vr3_context* ctx, w_vr3_window_monitor monitor){
	
	this->width = width;
	this->height = height;

	if (configuration & w_vr3::w_vr3_window_configuration::w_vr3_window_configuration_dont_resizeble) {
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	}

	window = glfwCreateWindow(width, height, title.c_str(), monitor, NULL);

	if (window == NULL) {
		std::string error_string = "cannot create window: \"";
		error_string += title;
		error_string += "\"\n";

		ctx->get_debugger()->error(error_string.c_str());

		return w_vr3::w_vr3_operation_status::w_vr3_operation_status_error;
	}

	if (configuration & w_vr3::w_vr3_window_configuration::w_vr3_window_configuration_fullscreen) {
		
		w_vr3::w_vr3_window_monitor monitor = get_window_monitor();
		const GLFWvidmode* video_mode = w_vr3::get_video_mode(monitor);

		set_window_monitor(monitor, 0, 0, video_mode->width, video_mode->height, video_mode->refreshRate);
	}

	w_vr3::Events::add_window(this);

	return w_vr3::w_vr3_operation_status::w_vr3_operation_status_success;
}

bool w_vr3::Window::is_should_window_close(){
	return glfwWindowShouldClose(window);
}

void w_vr3::Window::swap_buffer(){
	glfwSwapBuffers(window);
}

void w_vr3::Window::destroy(){
	glfwDestroyWindow(window);
}

GLFWwindow* w_vr3::Window::get_raw_window_handle(){
	return window;
}

w_vr3::w_vr3_window_monitor w_vr3::Window::get_window_monitor(){
	return glfwGetWindowMonitor(window);
}

void w_vr3::Window::set_window_monitor(w_vr3::w_vr3_window_monitor monitor, const int x, const int y, const int width, const int height, int refrash_rate){
	glfwSetWindowMonitor(window, monitor, x, y, width, height, refrash_rate);
}

void w_vr3::Window::update_window_size(const int width, const int height){
	this->width = width;
	this->height = height;

	glViewport(0, 0, width, height);
}

const int w_vr3::Window::get_window_height(){
	return height;
}

const int w_vr3::Window::get_window_width(){
	return width;
}

void w_vr3::Window::set_should_close(int flag){
	glfwSetWindowShouldClose(window, flag);
}

void w_vr3::Window::set_cursor_mode(int mode){
	glfwSetInputMode(window, GLFW_CURSOR, mode);
}

void w_vr3::Window::make_current_context(){
	glfwMakeContextCurrent(window);
}

const w_vr3::w_vr3_window_monitor w_vr3::get_primary_monitor(){
	return glfwGetPrimaryMonitor();
}

const GLFWvidmode* w_vr3::get_video_mode(w_vr3::w_vr3_window_monitor monitor){
	return glfwGetVideoMode(monitor);
}
