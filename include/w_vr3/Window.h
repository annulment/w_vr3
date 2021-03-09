#ifndef _INC_W_VR3_WINDOW_H
#define _INC_W_VR3_WINDOW_H
#include <w_vr3/w_vr3.h>
#include<string>

struct GLFWwindow;
struct GLFWmonitor;
struct GLFWvidmode;

namespace w_vr3 {
	class w_vr3_context;

	typedef GLFWmonitor* w_vr3_window_monitor;
	typedef GLFWvidmode* w_vr3_monitor_video_mode;

	const w_vr3::w_vr3_window_monitor get_primary_monitor();
	const GLFWvidmode* get_video_mode(w_vr3::w_vr3_window_monitor monitor);

	enum w_vr3_window_configuration : uint8_t {
		w_vr3_window_configuration_windowed = 0,
		w_vr3_window_configuration_fullscreen = 1,
		w_vr3_window_configuration_dont_resizeble = 2
	};

	class Window {
		GLFWwindow* window;
		int width, height;

	public:

		w_vr3::w_vr3_operation_status create(const std::string& title, w_vr3::w_vr3_window_configuration configuration, const int width, const int height, w_vr3::w_vr3_context* ctx, w_vr3_window_monitor monitor);

		bool is_should_window_close();
		void swap_buffer();

		void destroy();

		GLFWwindow* get_raw_window_handle();

		w_vr3::w_vr3_window_monitor get_window_monitor();
		void set_window_monitor(w_vr3::w_vr3_window_monitor monitor, const int x, const int y, const int width, const int height, int refrash_rate);

		void update_window_size(const int width, const int height);

		void set_should_close(int flag);

		const int get_window_height();
		const int get_window_width();

		void set_cursor_mode(int mode);

		void make_current_context();
	};
}
#endif