#include <GopherEngine/Core/Node.hpp>

#include <glm/gtc/matrix_transform.hpp>

using namespace std;

namespace GopherEngine {

    // Static member variable initialization for the id counter
    std::atomic<std::uint32_t> Node::id_counter_{0};

    // This constructor incremenents the static id counter and assigns a unique id to each node.
    Node::Node() : id_(id_counter_.fetch_add(1, std::memory_order_relaxed)) {
        
    }

    Node::~Node() {

    }

    void Node::add_component(shared_ptr<Component> component) {
        component->initialize(transform_);
        components_.push_back(component);
    }

    void Node::update(float delta_time) {
        for (const auto& component : components_) {
            component->update(transform_, delta_time);
        }
    }

    void Node::update_matrices() {
        local_matrix_ = glm::mat4(1.f); 
        local_matrix_ = glm::translate(local_matrix_, transform_.position_);
        local_matrix_ = local_matrix_ * glm::mat4_cast(transform_.rotation_);
        local_matrix_ = glm::scale(local_matrix_, transform_.scale_);

        // For now, we will just set the world matrix equal to the local matrix 
        // because we have not implemented parent-child relationships yet.
        world_matrix_ = local_matrix_; 

        for (const auto& component : components_) {
            component->update_matrices(local_matrix_, world_matrix_);
        }
    }
    
    void Node::draw() {
        for (const auto& component : components_) {
            component->draw(world_matrix_);
        }
    }
}