#pragma once

#include <GopherEngine/Core/Transform.hpp>

#include <glm/glm.hpp> // general glm header for basic types like vec3 and mat4
#include <glm/gtc/quaternion.hpp> // glm quaternion functions

namespace GopherEngine
{
    class Component
    {
        public:
            Component() = default;
            virtual ~Component() = default;
            virtual void initialize(Transform& transform) = 0;
            virtual void update(Transform& transform, float delta_time) = 0;
            virtual void update_matrices(const glm::mat4 &local_matrix, const glm::mat4 &world_matrix) = 0;
            virtual void draw(const glm::mat4 &world_matrix) = 0;
    };
}