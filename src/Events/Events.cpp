#include "Events.h"
#include "..//Window/Window.h"
#include <GLFW/glfw3.h>

std::vector<w_vr3::Window*> w_vr3::Events::Events::windows;

bool* w_vr3::Events::_keys;
uint32_t* w_vr3::Events::_frames;
uint32_t  w_vr3::Events::_current = 0;
float w_vr3::Events::deltaX = 0.f;
float w_vr3::Events::deltaY = 0.f;
float w_vr3::Events::x = 0.f;
float w_vr3::Events::y = 0.f;
bool  w_vr3::Events::_cursor_locked = false;
bool  w_vr3::Events::_cursor_started = false;
float w_vr3::Events::delta_time = 0.f;
float w_vr3::Events::last_frame = 0.f;
GLFWwindow* w_vr3::Events::last_window_handle = nullptr;

#define _MOUSE_BUTTONS 1024

void w_vr3::Events::init(){
	_keys = new bool[1032];
	_frames = new uint32_t[1032];

	memset(_keys, false, 1032);
	memset(_frames, 0, 1032);
}

void w_vr3::Events::shutdown(){
	if (_keys != nullptr) {
		delete _keys;
	}

	if (_frames != nullptr) {
		delete _frames;
	}
}

void w_vr3::key_callBack(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (action == GLFW_PRESS) {
		Events::_keys[key] = true;
		Events::_frames[key] = Events::_current;
	}
	else if (action == GLFW_RELEASE) {
		Events::_keys[key] = false;
		Events::_frames[key] = Events::_current;
	}
}

void w_vr3::mouse_button_callback(GLFWwindow* window, int button, int action, int mode){
	w_vr3::Events::last_window_handle = window;

	if (action == GLFW_PRESS) {
		w_vr3::Events::_keys[_MOUSE_BUTTONS + button] = true;
		w_vr3::Events::_frames[_MOUSE_BUTTONS + button] = w_vr3::Events::_current;
	}
	else if (action == GLFW_RELEASE) {
		w_vr3::Events::_keys[_MOUSE_BUTTONS + button] = false;
		w_vr3::Events::_frames[_MOUSE_BUTTONS + button] = w_vr3::Events::_current;
	}
}

void w_vr3::cursor_position_callBack(GLFWwindow* window, double xpos, double ypos){
	w_vr3::Events::last_window_handle = window;

	if (w_vr3::Events::_cursor_started) {
		w_vr3::Events::deltaX += xpos - w_vr3::Events::x;
		w_vr3::Events::deltaY += ypos - w_vr3::Events::y;
	}
	else {
		w_vr3::Events::_cursor_started = true;
	}

	w_vr3::Events::x = xpos;
	w_vr3::Events::y = ypos;
}

void w_vr3::window_size_callback(GLFWwindow* window, int width, int height){
	for (size_t i = 0; i < w_vr3::Events::windows.size(); i++){
		if (w_vr3::Events::windows[i]->get_raw_window_handle() == window) {
			w_vr3::Events::windows[i]->update_window_size(width, height);
		}
	}
}

void w_vr3::Events::add_window(w_vr3::Window* wnd){
	w_vr3::Events::windows.push_back(wnd);

	glfwSetKeyCallback(wnd->get_raw_window_handle(), key_callBack);
	glfwSetMouseButtonCallback(wnd->get_raw_window_handle(), mouse_button_callback);
	glfwSetCursorPosCallback(wnd->get_raw_window_handle(), cursor_position_callBack);
	glfwSetWindowSizeCallback(wnd->get_raw_window_handle(), window_size_callback);
}

void w_vr3::Events::pullEvents(){
	_current++;
	deltaX = 0.f;
	deltaY = 0.f;
	glfwPollEvents();

	float current_frame = glfwGetTime();
	delta_time = current_frame - last_frame;
	last_frame = current_frame;
}

bool w_vr3::Events::check_window_handle(w_vr3::Window* wnd){
	return wnd->get_raw_window_handle() == w_vr3::Events::last_window_handle;
}

bool w_vr3::Events::pressed(int keycode){
	if (keycode < 0 || keycode >= _MOUSE_BUTTONS)
		return false;
	return _keys[keycode];
}

bool w_vr3::Events::jpressed(int keycode){
	if (keycode < 0 || keycode >= _MOUSE_BUTTONS)
		return false;
	return _keys[keycode] && _frames[keycode] == _current;
}

bool w_vr3::Events::clicked(int button){
	int index = _MOUSE_BUTTONS + button;
	return _keys[index];
}

bool w_vr3::Events::jclicked(int button){
	int index = _MOUSE_BUTTONS + button;
	return _keys[index] && _frames[index] == _current;
}

void w_vr3::Events::ToggleCursor(){
	//_cursor_locked = !_cursor_locked;
	//Events::Window->setCursorMode(_cursor_locked ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
}

float w_vr3::Events::GetDeltaTime(){
	return Events::delta_time;
}