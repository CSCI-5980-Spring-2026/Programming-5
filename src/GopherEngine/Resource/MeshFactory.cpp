#include <GopherEngine/Resource/MeshFactory.hpp>

using namespace std;

namespace GopherEngine {

    std::shared_ptr<Mesh> MeshFactory::create_cube(float width, float height, float depth)
    {
        const float w = width  / 2.f;
        const float h = height / 2.f;
        const float d = depth  / 2.f;

        auto mesh = std::make_shared<Mesh>();

        mesh->vertices_ = {
            // Front face
            {-w, -h,  d}, {w, -h,  d}, {w,  h,  d}, {-w,  h,  d},
            // Back face
            {-w, -h, -d}, {w, -h, -d}, {w,  h, -d}, {-w,  h, -d},
            // Left face
            {-w, -h, -d}, {-w, -h,  d}, {-w,  h,  d}, {-w,  h, -d},
            // Right face
            {w, -h, -d}, {w, -h,  d}, {w,  h,  d}, {w,  h, -d},
            // Top face
            {-w,  h,  d}, {w,  h,  d}, {w,  h, -d}, {-w,  h, -d},
            // Bottom face
            {-w, -h,  d}, {w, -h,  d}, {w, -h, -d}, {-w, -h, -d},
        };

        mesh->normals_ = {
            // Front face
            {0,  0,  1}, {0,  0,  1}, {0,  0,  1}, {0,  0,  1},
            // Back face
            {0,  0, -1}, {0,  0, -1}, {0,  0, -1}, {0,  0, -1},
            // Left face
            {-1,  0,  0}, {-1,  0,  0}, {-1,  0,  0}, {-1,  0,  0},
            // Right face
            {1,  0,  0}, {1,  0,  0}, {1,  0,  0}, {1,  0,  0},
            // Top face
            {0,  1,  0}, {0,  1,  0}, {0,  1,  0}, {0,  1,  0},
            // Bottom face
            {0, -1,  0}, {0, -1,  0}, {0, -1,  0}, {0, -1,  0},
        };

        mesh->uvs_ = {
            // Front face
            {0, 1}, {1, 1}, {1, 0}, {0, 0},
            // Back face
            {1, 1}, {0, 1}, {0, 0}, {1, 0},
            // Left face
            {0, 1}, {1, 1}, {1, 0}, {0, 0},
            // Right face
            {1, 1}, {0, 1}, {0, 0}, {1, 0},
            // Top face
            {0, 1}, {1, 1}, {1, 0}, {0, 0},
            // Bottom face
            {1, 1}, {0, 1}, {0, 0}, {1, 0},
        };

        mesh->indices_ = {
            // Front face
             0,  1,  2,  2,  3,  0,
            // Back face
             4,  6,  5,  6,  4,  7,
            // Left face
             8,  9, 10, 10, 11,  8,
            // Right face
            12, 14, 13, 14, 12, 15,
            // Top face
            16, 17, 18, 18, 19, 16,
            // Bottom face
            20, 22, 21, 22, 20, 23,
        };

        return mesh;
    }
}