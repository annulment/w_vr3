#include "debugger.h"
#include<bitset>
#include<iostream>
#include<sstream>

#if defined(_MSVC_TRADITIONAL) && _MSVC_TRADITIONAL
#include <Windows.h>

#endif

w_vr3::debugger::debugger(w_vr3::w_vr3_debug_level debug_level) : debug_level(debug_level) {

}

void w_vr3::debugger::debug(const char* msg){
	if (debug_level & w_vr3::w_vr3_debug_level::w_vr3_debug_level_console) {
		std::stringstream stream;
		stream << "------------------------\n";
		stream << "debug:" << msg << "\n";
		stream << "------------------------\n";
		printf(stream.str().c_str());

#if defined(_MSVC_TRADITIONAL) && _MSVC_TRADITIONAL
		OutputDebugStringA(stream.str().c_str());
#endif
	}
	if (debug_level & w_vr3::w_vr3_debug_level::w_vr3_debug_level_file) {

	}
	if (debug_level & w_vr3::w_vr3_debug_level::w_vr3_debug_level_window) {

	}
}

void w_vr3::debugger::debug(const char* msg, uint32_t error_code){
	if (debug_level & w_vr3::w_vr3_debug_level::w_vr3_debug_level_console) {
		std::stringstream stream;
		stream << "------------------------\n";
		stream << "debug:" << msg << "\n";
		stream << "code:" << error_code << "\n";
		stream << "------------------------\n";
		printf(stream.str().c_str());

#if defined(_MSVC_TRADITIONAL) && _MSVC_TRADITIONAL
		OutputDebugStringA(stream.str().c_str());
#endif
	}
	if (debug_level & w_vr3::w_vr3_debug_level::w_vr3_debug_level_file) {

	}
	if (debug_level & w_vr3::w_vr3_debug_level::w_vr3_debug_level_window) {

	}
}

void w_vr3::debugger::error(const char* msg){
	if (debug_level & w_vr3::w_vr3_debug_level::w_vr3_debug_level_console) {
		std::stringstream stream;
		stream << "------------------------\n";
		stream << "error:" << msg << "\n";
		stream << "------------------------\n";
		printf(stream.str().c_str());

#if defined(_MSVC_TRADITIONAL) && _MSVC_TRADITIONAL
		OutputDebugStringA(stream.str().c_str());
#endif
	}
	if (debug_level & w_vr3::w_vr3_debug_level::w_vr3_debug_level_file) {

	}
	if (debug_level & w_vr3::w_vr3_debug_level::w_vr3_debug_level_window) {

	}
}

void w_vr3::debugger::error(const char* msg, uint32_t error_code){
	if (debug_level & w_vr3::w_vr3_debug_level::w_vr3_debug_level_console) {
		std::stringstream stream;
		stream << "------------------------\n";
		stream << "error:" << msg << "\n";
		stream << "code:" << error_code << "\n";
		stream << "------------------------\n";
		printf(stream.str().c_str());

#if defined(_MSVC_TRADITIONAL) && _MSVC_TRADITIONAL
		OutputDebugStringA(stream.str().c_str());
#endif
	}
	if (debug_level & w_vr3::w_vr3_debug_level::w_vr3_debug_level_file) {

	}
	if (debug_level & w_vr3::w_vr3_debug_level::w_vr3_debug_level_window) {

	}
}

w_vr3::debugger::~debugger()
{
}
