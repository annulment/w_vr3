#include "w_vr3.h"
#include "..//w_vr3_context/w_vr3_context.h"
#include "..//debugger/debugger.h"
#include "..//Events/Events.h"

#include<GLFW/glfw3.h>

w_vr3::w_vr3_operation_status w_vr3::init(w_vr3::w_vr3_debug_level debug_level, w_vr3_context*& ctx){
	auto debugger = new w_vr3::debugger(debug_level);

	int code = glfwInit();
	if (code != GLFW_TRUE) {
		debugger->error("can't initialize GLFW!", code);

		return w_vr3::w_vr3_operation_status::w_vr3_operation_status_error;
	}

	ctx = new w_vr3::w_vr3_context(debugger);

	w_vr3::Events::init();

	return w_vr3::w_vr3_operation_status::w_vr3_operation_status_success;
}

void w_vr3::shutdown(w_vr3_context*& ctx){
	glfwTerminate();

	delete ctx;
}
