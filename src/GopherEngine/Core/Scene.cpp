#include <GopherEngine/Core/Scene.hpp>

using namespace std;

namespace GopherEngine {

    Scene::Scene() {

    }

    Scene::~Scene() {

    }

    void Scene::create_default_camera() {

        camera_ = make_shared<Camera>();
        camera_->set_perspective(60.f, 4.f/3.f, 0.1f, 1000.f);

        auto camera_node = create_node();
        camera_node->add_component(camera_);
    }

    shared_ptr<Camera> Scene::get_camera() const {
        return camera_;
    }

    void Scene::set_camera(shared_ptr<Camera> camera) {
        camera_ = camera;
        camera_->set_projection_matrix_dirty(true);
    }

    void Scene::add_node(shared_ptr<Node> node) {

        nodes_.push_back(node);

    }

    shared_ptr<Node> Scene::create_node() {

        shared_ptr<Node> node = make_shared<Node>();
        nodes_.push_back(node);
        return node;

    }

    void Scene::update(float delta_time) {

        for(auto& node: nodes_) {
            node->update(delta_time);
        }

    }

    void Scene::draw() {

        for(auto& node: nodes_) {
            node->update_matrices();
        }

        if(camera_) {
            for(auto& node: nodes_) {
                node->draw();
            }
        }

    }
}