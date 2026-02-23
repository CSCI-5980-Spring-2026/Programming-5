#pragma once

#include <GopherEngine/Core/MeshComponent.hpp>
using namespace GopherEngine;

class TestCube : public MeshComponent
{
    public:
        TestCube();
        void initialize(Transform& transform) override;
        void update(Transform& transform, float delta_time) override;
};
