#ifndef _W_VR3_EVENTS_H
#define _W_VR3_EVENTS_H
#include<vector>

struct GLFWwindow;

namespace w_vr3 {
	class Window;

	class Events {
		static std::vector<w_vr3::Window*> windows;
		
		friend void window_size_callback(GLFWwindow* window, int width, int height);
		friend void cursor_position_callBack(GLFWwindow* window, double xpos, double ypos);
		friend void mouse_button_callback(GLFWwindow* window, int button, int action, int mode);
		friend void key_callBack(GLFWwindow* window, int key, int scancode, int action, int mode);

		static GLFWwindow* last_window_handle;
	public:

		static float delta_time;
		static float last_frame;
		static bool* _keys;
		static uint32_t* _frames;
		static uint32_t _current;
		static float deltaX;
		static float deltaY;
		static float x;
		static float y;
		static bool _cursor_locked;
		static bool _cursor_started;

		static void init();

		static void shutdown();

		static void add_window(w_vr3::Window* wnd);
		static void pullEvents();

		static bool check_window_handle(w_vr3::Window* wnd);

		static bool pressed(int keycode);
		static bool jpressed(int keycode);

		static bool clicked(int button);
		static bool jclicked(int button);

		static void ToggleCursor(w_vr3::Window* wnd);
		static float GetDeltaTime();
	};
}

#endif