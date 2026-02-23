#include <GopherEngine/Core/MeshComponent.hpp>
using namespace GopherEngine;

#include <iostream>

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

    void MeshComponent::draw(const glm::mat4 &world_matrix, const glm::mat4 &view_matrix, const glm::mat4 &projection_matrix) {

        if (!mesh_ || !material_)
            return;
        
        material_->draw(*mesh_, world_matrix, view_matrix, projection_matrix);
    }

    void MeshComponent::set_mesh(std::shared_ptr<Mesh> mesh) {
        mesh_ = std::move(mesh);
    }

    std::shared_ptr<Mesh> MeshComponent::get_mesh() const {
        return mesh_;
    }

    void MeshComponent::set_material(std::shared_ptr<Material> material) {
        material_ = std::move(material);
    }

    std::shared_ptr<Material> MeshComponent::get_material() const {
        return material_;
    }
}