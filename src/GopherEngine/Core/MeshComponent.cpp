#include <GopherEngine/Core/MeshComponent.hpp>
using namespace GopherEngine;

#include <iostream>

// We will eventually remove these when we add draw functionality to the material
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include <SFML/OpenGL.hpp>

namespace GopherEngine {

    void MeshComponent::initialize(Transform& transform) {
        // Empty, but can be overriden by derived classes
    }

    void MeshComponent::update(Transform& transform, float delta_time) {
        // Empty, but can be overriden by derived classes
    }   

    void MeshComponent::update_matrices(const glm::mat4 &local_matrix, const glm::mat4 &world_matrix) {
        // Empty, but can be overriden by derived classes
    }

    void MeshComponent::draw(const glm::mat4 &world_matrix) {

        if (!mesh_ || mesh_->vertices_.empty())
            return;


        // Fixed function pipeline
        // This code will finally be removed in this class!

        // Enable the position vertex component
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(
            3,                              // x,y,z
            GL_FLOAT,                       // component type
            sizeof(glm::vec3),              // stride (handles possible padding/alignment)
            value_ptr(mesh_->vertices_[0])  // pointer to first float
        );

        // Disable normal, color, and texture coordinate vertex components
        // We have not added shaders yet, so we will not use these attributes
        glDisableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);

        // Set the modelview matrix to the identity matrix
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        // Load the model matrix into OpenGL
        glLoadMatrixf(glm::value_ptr(world_matrix));

        // Submit the geometry to the GPU
        glDrawElements(
            GL_TRIANGLES,                        // primitive type
            mesh_->indices_.size(),              // number of indices
            GL_UNSIGNED_INT,                     // index type
            mesh_->indices_.data()               // pointer to index array
        );
            
    }

    void MeshComponent::set_mesh(std::shared_ptr<Mesh> mesh) {
        mesh_ = std::move(mesh);
    }

    std::shared_ptr<Mesh> MeshComponent::get_mesh() const {
        return mesh_;
    }
}