#include "TestCube.hpp"

#include <GopherEngine/Resource/MeshFactory.hpp>
#include <GopherEngine/Renderer/UnlitMaterial.hpp>
#include <GopherEngine/Core/Utils.hpp>
using namespace GopherEngine;

#include <memory>
using namespace std;

TestCube::TestCube() {
    
}

void TestCube::initialize(Transform& transform) {
    transform.position_.z = -3.f; 

    mesh_ = MeshFactory::create_cube();
    material_ = make_shared<UnlitMaterial>();
    material_->set_color(glm::vec4(1.f, 0.5f, 1.f, 1.f));

    // Push a random color for each vertex to demonstrate vertex colors
    for(auto &vertex : mesh_->vertices_) {
         mesh_->colors_.push_back(glm::vec4(
            Random::value(),
            Random::value(),
            Random::value(),
            1.f
        ));
    }
}

void TestCube::update(Transform& transform, float delta_time) {

    // Rotate the node around the Y axis at a constant speed of 45 degrees per second
    auto frame_rotation = glm::angleAxis(
        delta_time * glm::radians(45.f), 
        glm::vec3(0.f, 1.f, 0.f)
    );
    transform.rotation_ =  frame_rotation * transform.rotation_;

}