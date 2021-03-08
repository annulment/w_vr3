#ifndef _W_VR3_H
#define _W_VR3_H

#include<cstdint>

namespace w_vr3 {

	class w_vr3_context;

	enum w_vr3_operation_status : uint8_t {
		w_vr3_operation_status_error = 0,
		w_vr3_operation_status_success = 1
	};

	enum w_vr3_debug_level : uint8_t {
		w_vr3_debug_level_none = -1,
		w_vr3_debug_level_file = 0,
		w_vr3_debug_level_console = 1,
		w_vr3_debug_level_window = 2
	};

	w_vr3::w_vr3_operation_status init(w_vr3::w_vr3_debug_level debug_level, w_vr3_context*& ctx);

	void shutdown(w_vr3_context*& ctx);
}

#endif 