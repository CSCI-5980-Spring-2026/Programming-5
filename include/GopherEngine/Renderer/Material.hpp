#pragma once

#include <GopherEngine/Resource/Mesh.hpp>
#include <GopherEngine/Renderer/ShaderProgram.hpp>

#include <glm/glm.hpp>
#include <memory>

namespace GopherEngine
{
    class Material
    {
        public:
            Material() = default;
            virtual ~Material() = default;
            virtual void draw(
                const Mesh& mesh,
                const glm::mat4 &world_matrix, 
                const glm::mat4 &view_matrix, 
                const glm::mat4 &projection_matrix) = 0;
            
            void set_color(const glm::vec4 &color);
            glm::vec4 get_color() const;

        protected:
            void bind_shader(const ShaderProgram& shader_program, const glm::mat4 &world_matrix, const glm::mat4 &view_matrix, const glm::mat4 &projection_matrix);
            void unbind_shader(const ShaderProgram& shader_program);

            glm::vec4 color_{1.f, 1.f, 1.f, 1.f}; 
    };
}