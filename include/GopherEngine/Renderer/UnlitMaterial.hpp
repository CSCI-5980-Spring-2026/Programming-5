#pragma once

#include <GopherEngine/Renderer/Material.hpp>

#include <memory>

namespace GopherEngine {

class UnlitMaterial : public Material {
    public:
        UnlitMaterial();
        void draw(
            const Mesh& mesh, 
            const glm::mat4 &world_matrix, 
            const glm::mat4 &view_matrix, 
            const glm::mat4 &projection_matrix) override;
    };
}