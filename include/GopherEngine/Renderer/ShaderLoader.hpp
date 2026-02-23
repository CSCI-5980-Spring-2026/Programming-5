#pragma once

#include <GopherEngine/Renderer/ShaderProgram.hpp>

#include <memory>
#include <map>

namespace GopherEngine
{
    enum class ShaderType
    {
        Unlit,
        BlinnPhong,
    };

    class ShaderLoader
    {
        public:
            static std::shared_ptr<ShaderProgram> load_shader(ShaderType shader_type);
            static void release_shader(ShaderType shader_type);
            static void release_all_shaders();

        private:
            static std::map <ShaderType, std::shared_ptr<ShaderProgram>> shader_cache_;
    };
}