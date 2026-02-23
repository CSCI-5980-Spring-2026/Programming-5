#pragma once

#include <GopherEngine/Core/Types.hpp>
#include <SFML/Window.hpp>
#include <string>

namespace GopherEngine
{    class Window
    {
        public:
            Window(std::string title = "GopherEngine", unsigned int width = 800, unsigned int height = 600);
            ~Window();

            void set_title(std::string title);
            void set_size(unsigned int width, unsigned int height);
            void set_style(int style);
            void set_state(sf::State state);
            void set_vertical_sync(bool vertical_sync);
            void set_dirty(bool dirty);
            bool set_active(bool active);

            int get_width();
            int get_height();
            bool get_dirty();
            bool is_open();
            void set_viewport_mode(ViewportMode mode);
            ViewportMode get_viewport_mode() const;

            void create_window();
            void handle_events();
            void display();

        private:
            sf::Window* window_;
            std::string title_;
            unsigned int width_;
            unsigned int height_;
            bool dirty_;
            bool vertical_sync_;
            int style_;
            sf::State state_;
            ViewportMode viewport_mode_;
    };
}