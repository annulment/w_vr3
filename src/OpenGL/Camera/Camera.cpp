#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include "..//..//Window/Window.h"
#include "..//..//Events/Events.h"

w_vr3::gl::Camera::Camera(w_vr3::Window* window, glm::vec3 position
    , glm::vec3 up, float yaw, float pitch) : speed(2.5f), zoom(45.0f), front(glm::vec3(0.0f, 0.0f, -1.0f)),
    window(window){
    this->position = position;
    this->world_up = up;
    this->yaw = yaw;
    this->pitch = pitch;

    this->update_vectors();
}

glm::mat4 w_vr3::gl::Camera::getViewMatrix(){
    return glm::lookAt(position, position + front, up);
}

glm::mat4 w_vr3::gl::Camera::getProjection(){
    return  glm::perspective(glm::radians(zoom), (float)window->get_window_width() / (float)window->get_window_height(), 0.1f, 100.0f);
}

void w_vr3::gl::Camera::update_vectors(){
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    this->front = glm::normalize(front);

    right = glm::normalize(glm::cross(front, world_up));
    up = glm::normalize(glm::cross(right, front));
}

w_vr3::gl::w_vr3_camera_transform::w_vr3_camera_transform(Camera* camera, float mouse_sensitivity)
    : camera(camera), mouse_sensitivity(mouse_sensitivity){
}

void w_vr3::gl::w_vr3_camera_transform::mouse_transform(bool constrainPitch){
    float x_offset = w_vr3::Events::deltaX;
    float y_offset = -w_vr3::Events::deltaY;

    x_offset *= this->mouse_sensitivity;
    y_offset *= this->mouse_sensitivity;

    camera->yaw += x_offset;
    camera->pitch += y_offset;

    if (constrainPitch) {
        if (camera->pitch > 89.0f)
            camera->pitch = 89.0f;
        if (camera->pitch < -89.0f)
            camera->pitch = -89.0f;
    }

    this->camera->update_vectors();
}

void w_vr3::gl::w_vr3_camera_transform::position_transform(camera_direction direction){
    float velocity = camera->speed * w_vr3::Events::delta_time;

    switch (direction){
    case w_vr3::gl::w_vr3_camera_transform::cd_FORWARD:
        camera->position += camera->front * velocity;
        break;
    case w_vr3::gl::w_vr3_camera_transform::cd_BACKWARD:
        camera->position -= camera->front * velocity;
        break;
    case w_vr3::gl::w_vr3_camera_transform::cd_LEFT:
        camera->position -= camera->right * velocity;
        break;
    case w_vr3::gl::w_vr3_camera_transform::cd_RIGHT:
        camera->position += camera->right * velocity;
        break;
    }
}
