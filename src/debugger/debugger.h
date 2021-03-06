#ifndef _W_VR3_DEBUGGER_H
#define _W_VR3_DEBUGGER_H
#include "../w_vr3/w_vr3.h"

namespace w_vr3 {
	
	class debugger {
		w_vr3::w_vr3_debug_level debug_level;

	public:
		
		debugger(w_vr3::w_vr3_debug_level debug_level);

		void debug(const char* msg);
		void debug(const char* msg, uint32_t error_code);

		void error(const char* msg);
		void error(const char* msg, uint32_t error_code);

		~debugger();
	};

}

#endif // !_W_VR3_DEBUGGER_H