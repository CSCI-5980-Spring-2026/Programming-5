#pragma once

#include <GopherEngine/Core/Types.hpp>
#include <GopherEngine/Core/Scene.hpp>

namespace GopherEngine
{
    class Renderer
    {
        public:
            Renderer();
            ~Renderer();
            void initialize();
            void resize_viewport(unsigned int window_width, unsigned int window_height, float camera_aspect_ratio, ViewportMode mode);
            void draw(Scene &scene);
    };
}