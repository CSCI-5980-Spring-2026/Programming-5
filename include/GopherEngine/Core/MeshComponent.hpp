#pragma once

#include <GopherEngine/Core/Component.hpp>
#include <GopherEngine/Resource/Mesh.hpp>
#include <GopherEngine/Renderer/Material.hpp>
using namespace GopherEngine;

#include <memory>

namespace GopherEngine
{
    class MeshComponent : public Component
    {
        public:
            void initialize(Transform& transform) override;
            void update(Transform& transform, float delta_time) override;
            void update_matrices(const glm::mat4 &local_matrix, const glm::mat4 &world_matrix) override;
            void draw(const glm::mat4 &world_matrix, const glm::mat4 &view_matrix, const glm::mat4 &projection_matrix) override;

            void set_mesh(std::shared_ptr<Mesh> mesh);
            std::shared_ptr<Mesh> get_mesh() const;

            void set_material(std::shared_ptr<Material> material);
            std::shared_ptr<Material> get_material() const;


        protected:
            std::shared_ptr<Mesh> mesh_;
            std::shared_ptr<Material> material_;
    };
}