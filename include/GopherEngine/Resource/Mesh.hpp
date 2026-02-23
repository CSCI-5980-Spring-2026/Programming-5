#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace GopherEngine {
    struct Mesh {

         // CPU-side data
        std::vector<glm::vec3> vertices_;
        std::vector<glm::vec3> normals_;
        std::vector<glm::vec4> colors_;
        std::vector<glm::vec2> uvs_;
        std::vector<unsigned int> indices_;   

        // CPU-side buffer and GPU-side handles (mutable: populated lazily by the renderer)
        mutable std::vector<float> buffer_;
        mutable unsigned int vao_{0};
        mutable unsigned int vbo_{0};
        mutable unsigned int ebo_{0};
        mutable std::function<void()> gpu_release_{0};

        // Destructor to clean up GPU resources if they were allocated
        ~Mesh()
        {
            if(gpu_release_) gpu_release_();
        }

        // Make the mesh non-copyable but moveable to avoid accidental double release of GPU resources
        Mesh() = default;
        Mesh(const Mesh&) = delete;
        Mesh& operator=(const Mesh&) = delete;
        Mesh(Mesh&&) = default;
        Mesh& operator=(Mesh&&) = default;

    };
}