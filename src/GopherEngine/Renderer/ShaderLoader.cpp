#include "UNLIT_VERT_SHADER.h"
#include "UNLIT_FRAG_SHADER.h"

#include <GopherEngine/Renderer/ShaderLoader.hpp>

#include <stdexcept>
using namespace std;

namespace GopherEngine
{
    // Definition of static shader cache
    std::map<ShaderType, std::shared_ptr<ShaderProgram>> ShaderLoader::shader_cache_;

    shared_ptr<ShaderProgram> ShaderLoader::load_shader(ShaderType shader_type)
    {
        switch(shader_type)
        {
            case ShaderType::Unlit:
            {
                if(shader_cache_.find(shader_type) != shader_cache_.end())
                    return shader_cache_[shader_type];

                auto shader = make_shared<ShaderProgram>(UNLIT_VERT_SHADER, UNLIT_FRAG_SHADER);
                shader_cache_[shader_type] = shader;
                return shader;
            }

            case ShaderType::BlinnPhong:
            {
                throw runtime_error("Blinn Phong shader not implemented yet");
            }

            default:
                throw runtime_error("Unknown shader type");
        }
    }

    void ShaderLoader::release_shader(ShaderType shader_type)
    {
        shader_cache_.erase(shader_type);
    }

    void ShaderLoader::release_all_shaders()
    {
        shader_cache_.clear();
    }
}