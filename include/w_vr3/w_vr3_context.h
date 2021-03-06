#ifndef _INC_W_VR3_CONTEXT_H
#define _INC_W_VR3_CONTEXT_H

#include<w_vr3/Window.h>
#include<string>

namespace w_vr3 {
	class debugger;
	class Window;

	class w_vr3_context {
		w_vr3::debugger* debugger;

	public:

		w_vr3_context(w_vr3::debugger* debugger);

		w_vr3::Window* create_window(const std::string& title, w_vr3::w_vr3_window_configuration configuration, const int width, const int height, w_vr3_window_monitor monitor);

		w_vr3::debugger* get_debugger();
	};
}

#endif 