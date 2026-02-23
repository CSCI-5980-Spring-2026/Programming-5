
#include <GopherEngine/Renderer/UnlitMaterial.hpp>
#include <GopherEngine/Renderer/ResourceUploader.hpp>
#include <GopherEngine/Renderer/ShaderLoader.hpp>

#include <glm/gtc/type_ptr.hpp> // value_ptr function to convert glm types to pointer for OpenGL

#include <GL/glew.h>          // Must come first
#include <SFML/OpenGL.hpp>    // After glew

#include <iostream>
#include <memory>
using namespace std;

namespace GopherEngine {

    UnlitMaterial::UnlitMaterial() {
        
    }

    void UnlitMaterial::draw(const Mesh& mesh, const glm::mat4 &world_matrix, const glm::mat4 &view_matrix, const glm::mat4 &projection_matrix) {
       
        // Skip drawing if mesh has no geometry
        if(mesh.vertices_.empty() || mesh.indices_.empty())
            return;

        // Lazily upload to GPU on first draw, return if upload fails
        if(mesh.vao_ == 0 && !ResourceUploader::upload_mesh(mesh))
            return;

        // Retrieve and bind the shader program
        auto shader_program = ShaderLoader::load_shader(ShaderType::Unlit);
        bind_shader(*shader_program, world_matrix, view_matrix, projection_matrix);

        // Bind the vertex array and draw the mesh
        glBindVertexArray(mesh.vao_);
        glDrawElements(GL_TRIANGLES, mesh.indices_.size(), GL_UNSIGNED_INT, 0);

        // Unbind the shader and vertex array to clean up state
        unbind_shader(*shader_program);
    }
}