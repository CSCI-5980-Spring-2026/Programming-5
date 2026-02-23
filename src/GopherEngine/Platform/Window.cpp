#include <GopherEngine/Platform/Window.hpp>

#include <iostream>

namespace GopherEngine {
    Window::Window(std::string title, unsigned int width, unsigned int height) {
        window_ = nullptr;
        title_ = title;
        width_ = width;
        height_ = height;
        dirty_ = false;
        vertical_sync_ = true;
        style_ = sf::Style::Default;
        state_ = sf::State::Windowed;
        viewport_mode_ = ViewportMode::Fit;
    }

    Window::~Window() {
        if(window_ != nullptr)
            delete window_;
    }

    void Window::set_size(unsigned int width, unsigned int height) {
        width_ = width;
        height_ = height;   
    }

    void Window::set_style(int style) {
        style_ = style;
    }
    
    void Window::set_state(sf::State state) {
        state_ = state;
    }

    void Window::set_title(std::string title) {
        title_ = title;
    }

    void Window::set_vertical_sync(bool vertical_sync) {
        vertical_sync_ = vertical_sync;
    }

    bool Window::set_active(bool active) {
        if (window_ == nullptr) {
            std::cerr << "Error: window has not been created yet" << std::endl;
            return false;
        }
        return window_->setActive(active);
    }

    int Window::get_width() {
        return width_;
    }
    
    int Window::get_height() {
        return height_;
    }

    bool Window::is_open() {
        if(window_ != nullptr)
            return window_->isOpen();
        else
            return false;
    }

    void Window::set_dirty(bool dirty) {
        dirty_ = dirty;
    }

    bool Window::get_dirty() {
        return dirty_;
    }

    void Window::set_viewport_mode(ViewportMode mode) {
        viewport_mode_ = mode;
        dirty_ = true;
    }

    ViewportMode Window::get_viewport_mode() const {
        return viewport_mode_;
    }

    void Window::create_window() {
        if(window_ != nullptr)
            delete window_;
        
        sf::ContextSettings contextSettings;
        contextSettings.depthBits   = 24;
        contextSettings.sRgbCapable = true;

        window_ = new sf::Window(sf::VideoMode({width_, height_}), 
                        static_cast<sf::String>(title_),
                        style_,
                        state_,
                        contextSettings);
                        
        window_->setVerticalSyncEnabled(vertical_sync_);
    }

    void Window::handle_events() {
        if(window_ == nullptr) {
            std::cerr << "Error: window has not been created yet" << std::endl;
            return;
        }

        // Handle events
        while (const std::optional event = window_->pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window_->close();
            }
            else if (const auto* resized = event->getIf<sf::Event::Resized>())
            {
                width_ = resized->size.x;
                height_ = resized->size.y;
                dirty_ = true;
            }
        }
    }

    void Window::display() {
        if(window_ == nullptr) {
            std::cerr << "Error: window has not been created yet" << std::endl;
        }
        else {
            window_->display();
        }
    }
}