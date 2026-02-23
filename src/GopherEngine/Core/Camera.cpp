#include <GopherEngine/Core/Camera.hpp>

namespace GopherEngine {

    void Camera::initialize(Transform& transform) {

        // Initialize camera-specific properties here if needed.

    }

    void Camera::update(Transform& transform, float delta_time) {

        // Copy the camera's position and rotation to the transform 
        // so that the node's local matrix will be computed correctly.
        transform.position_ = position_;
        transform.rotation_ = rotation_;

    }

    void Camera::update_matrices(const glm::mat4 &local_matrix, const glm::mat4 &world_matrix) {
        view_matrix_ = glm::inverse(world_matrix);
    }


    void Camera::draw(const glm::mat4 &world_matrix, const glm::mat4 &view_matrix, const glm::mat4 &projection_matrix) {
        // Camera does not draw anything itself.
    }

    const glm::vec3& Camera::get_position() const {
        return position_;
    }

    void Camera::set_position(const glm::vec3& position) {
        position_ = position;
    }

    const glm::quat& Camera::get_rotation() const {
        return rotation_;
    }

    void Camera::set_rotation(const glm::quat& rotation) {
        rotation_ = rotation;
    }
    
    const glm::mat4& Camera::get_view_matrix() const {
        return view_matrix_;
    }

    const glm::mat4& Camera::get_projection_matrix() const {
        return projection_matrix_;
    }

    bool Camera::get_projection_matrix_dirty() const {
        return projection_matrix_dirty_;
    }

    void Camera::set_projection_matrix_dirty(bool dirty) {
        projection_matrix_dirty_ = dirty;
    }

    void Camera::set_perspective(float fov, float aspect_ratio, float near, float far) {
        projection_matrix_ = glm::perspective(glm::radians(fov), aspect_ratio, near, far);
        aspect_ratio_ = aspect_ratio;
    }

    void Camera::set_frustum(float left, float right, float bottom, float top, float near, float far) {
        projection_matrix_ = glm::frustum(left, right, bottom, top, near, far);
        aspect_ratio_ = (right - left) / (top - bottom);
    }

    void Camera::set_orthographic(float left, float right, float bottom, float top, float near, float far) {
        projection_matrix_ = glm::ortho(left, right, bottom, top, near, far);
        aspect_ratio_ = (right - left) / (top - bottom);
    }

    float Camera::get_aspect_ratio() const {
        return aspect_ratio_;
    }
}
