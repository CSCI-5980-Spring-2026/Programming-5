#include <GopherEngine/Core/MainLoop.hpp>
#include <GopherEngine/Renderer/Renderer.hpp>
#include <GopherEngine/Core/Scene.hpp>
#include <GopherEngine/Core/Camera.hpp>

#include <iostream>
using namespace std;

namespace GopherEngine {
    MainLoop::MainLoop()
    {
        scene_ = make_shared<Scene>();
    }

    MainLoop::~MainLoop()
    {
    }

    int MainLoop::run()
    {
        configure();

        window_.create_window();

        if(!window_.set_active(true)) {
            cerr << "Failed to set window to active" << endl;
            return EXIT_FAILURE;
        }

        renderer_.initialize();
        initialize();

        handle_resize();
        
        // Reset the clock to start measuring time from the beginning of the main loop
        clock_.reset();

        while(window_.is_open())
        {
            window_.handle_events();

            float delta_time = clock_.delta_time();

            update(delta_time);
            scene_->update(delta_time);

            handle_resize();

            renderer_.draw(*scene_);
            window_.display();
        }
        
        return EXIT_SUCCESS;
    }

    void MainLoop::handle_resize() {
        
        auto camera = scene_->get_camera();

        if(camera) 
        {
            // If either the window or the camera's projection matrix is dirty,
            // we need to resize the viewport and reset the dirty flags.
            if(window_.get_dirty() || camera->get_projection_matrix_dirty())
            {
                // This will be extended to support camera aspect ratio
                renderer_.resize_viewport(
                    window_.get_width(), 
                    window_.get_height(), 
                    camera->get_aspect_ratio(),
                    window_.get_viewport_mode()
                );

                // Reset the dirty flags after resizing the viewport
                window_.set_dirty(false);
                camera->set_projection_matrix_dirty(false);
            }

        }  
        else 
        {
            // If there is no camera in the scene, then we only need to check
            // if the window is dirty, and if so, resize the viewport.
            if(window_.get_dirty() ) 
            {
                renderer_.resize_viewport(
                    window_.get_width(), 
                    window_.get_height(), 
                    static_cast<float>(window_.get_width()) / static_cast<float>(window_.get_height()),
                    window_.get_viewport_mode()
                );

                window_.set_dirty(false);
            }
        }
    }
}

