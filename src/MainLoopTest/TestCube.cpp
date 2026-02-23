#include "TestCube.hpp"

#include <GopherEngine/Resource/MeshFactory.hpp>
#include <GopherEngine/Core/Utils.hpp>
using namespace GopherEngine;

#include <memory>
using namespace std;

TestCube::TestCube() {
    
}

void TestCube::initialize(Transform& transform) {
    transform.position_.z = -3.f; 

    mesh_ = MeshFactory::create_cube();
}

void TestCube::update(Transform& transform, float delta_time) {

    // Rotate the node around the Y axis at a constant speed of 45 degrees per second
    auto frame_rotation = glm::angleAxis(
        delta_time * glm::radians(45.f), 
        glm::vec3(0.f, 1.f, 0.f)
    );
    transform.rotation_ =  frame_rotation * transform.rotation_;

}