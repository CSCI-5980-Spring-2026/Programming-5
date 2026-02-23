#include <GopherEngine/Renderer/Material.hpp>
#include <GopherEngine/Renderer/ResourceUploader.hpp>

#include <GL/glew.h>          // Must come first
#include <SFML/OpenGL.hpp>    // After glew

#include <glm/gtc/type_ptr.hpp> // value_ptr function to convert glm types to pointer for OpenGL

namespace GopherEngine {
    void Material::set_color(const glm::vec4 &color) {
        color_ = color;
    }

    glm::vec4 Material::get_color() const {
        return color_;
    }

    void Material::bind_shader(const ShaderProgram& shader_program, const glm::mat4 &world_matrix, const glm::mat4 &view_matrix, const glm::mat4 &projection_matrix) {

        shader_program.bind();

        // Compute model-view matrix
        glm::mat4 model_view_matrix = view_matrix * world_matrix;

        // Update matrices UBO
        glBindBuffer(GL_UNIFORM_BUFFER, shader_program.get_matrices_ubo());
        glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(world_matrix));
        glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4)*1, sizeof(glm::mat4), glm::value_ptr(view_matrix));
        glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4)*2, sizeof(glm::mat4), glm::value_ptr(model_view_matrix));
        glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4)*3, sizeof(glm::mat4), glm::value_ptr(projection_matrix));

        // For now, we will just set this to 0 since we don't have texture support in the base Material class
        int use_texture = 0; 

        // Update material UBO
        glBindBuffer(GL_UNIFORM_BUFFER, shader_program.get_material_ubo());
        glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::vec4), glm::value_ptr(color_));
        glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::vec4), sizeof(int), &use_texture);
    }

    void Material::unbind_shader(const ShaderProgram& shader_program) {

        // Reset the uniform buffer binding to avoid accidental modification
        glBindBuffer(GL_UNIFORM_BUFFER, 0);

        // Reset the vertex array binding to avoid accidental modification
        glBindVertexArray(0);

        shader_program.unbind();
    }
}