#pragma once
#include <GopherEngine/Resource/Mesh.hpp>

#include <memory>

namespace GopherEngine
{
    class ResourceUploader
    {
        public:
            static bool upload_mesh(const Mesh& mesh);
            static void release_mesh(const Mesh& mesh);
    };
}