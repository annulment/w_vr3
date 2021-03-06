#include "w_vr3_context.h"

w_vr3::w_vr3_context::w_vr3_context(w_vr3::debugger* debugger) : debugger(debugger){

}

w_vr3::Window* w_vr3::w_vr3_context::create_window(const std::string& title, w_vr3::w_vr3_window_configuration configuration, const int width, const int height, w_vr3_window_monitor monitor){
	w_vr3::Window* wnd = new w_vr3::Window();
	wnd->create(title, configuration, width, height, this, monitor);

	return wnd;
}

w_vr3::debugger* w_vr3::w_vr3_context::get_debugger(){
	return debugger;
}
