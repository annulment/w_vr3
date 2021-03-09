#ifndef _INC_W_VR3_OPENGL_CAMERA_H
#define _INC_W_VR3_OPENGL_CAMERA_H

#include <glm/glm.hpp>

namespace w_vr3 {
	class Window;

	namespace gl {
		class w_vr3_camera_transform;

		class Camera {
			w_vr3::Window* window;

			friend w_vr3_camera_transform;

		public:

			glm::vec3 position;
			glm::vec3 front;
			glm::vec3 up;
			glm::vec3 right;
			glm::vec3 world_up;

			float yaw;
			float pitch;

			float speed;
			float zoom;

			Camera(w_vr3::Window* window, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = -90.0f, float pitch = 0.0f);

			glm::mat4 getViewMatrix();
			glm::mat4 getProjection();

			void update_vectors();
		};

		class w_vr3_camera_transform {
			Camera* camera;
		public:
			float mouse_sensitivity;

			enum camera_direction {
				cd_FORWARD,
				cd_BACKWARD,
				cd_LEFT,
				cd_RIGHT
			};

			w_vr3_camera_transform(Camera* camera, float mouse_sensitivity);

			void mouse_transform(bool constrainPitch = true);

			void position_transform(camera_direction direction);
		};
	}
}

#endif