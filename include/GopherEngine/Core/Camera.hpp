#pragma once

#include <GopherEngine/Core/Component.hpp>

namespace GopherEngine {

    class Camera : public Component
    {
        public:
            void initialize(Transform& transform) override;
            void update(Transform& transform, float delta_time) override ;
            void update_matrices(const glm::mat4 &local_matrix, const glm::mat4 &world_matrix) override;
            void draw(const glm::mat4 &world_matrix, const glm::mat4 &view_matrix, const glm::mat4 &projection_matrix) override; 

            const glm::vec3& get_position() const;
            void set_position(const glm::vec3& position);

            const glm::quat& get_rotation() const;
            void set_rotation(const glm::quat& rotation);
            
            const glm::mat4& get_view_matrix() const;
            const glm::mat4& get_projection_matrix() const;

            bool get_projection_matrix_dirty() const;
            void set_projection_matrix_dirty(bool dirty);

            float get_aspect_ratio() const;

            void set_perspective(float fov, float aspect_ratio, float near, float far);
            void set_frustum(float left, float right, float bottom, float top, float near, float far);
            void set_orthographic(float left, float right, float bottom, float top, float near, float far);

        private:
            glm::vec3 position_{0.f, 0.f, 0.f};
            glm::quat rotation_{1.f, 0.f, 0.f, 0.f};
            glm::mat4 view_matrix_{1.f};

            float aspect_ratio_{1.f};
            bool projection_matrix_dirty_{true};
            glm::mat4 projection_matrix_{1.f};
    };
} 