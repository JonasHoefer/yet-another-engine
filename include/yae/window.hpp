//
// Created by jonas on 17.12.2017.
//

#ifndef YAE_WINDOWS_HPP
#define YAE_WINDOWS_HPP

#include <iostream>

#define GLEW_STATIC

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include "yae/utils/counter.hpp"


namespace yae {
    /**
     * @brief wrapper around a GLFW3 window
     */
    class window : public utils::counter<window> {
    public:
        /**
         * @brief creates a new window with the given width, height and title
         *
         * @param title of the window
         * @param width of the window
         * @param height of the window
         *
         * initializes glfw and glew
         */
        explicit window(const char* title, unsigned int width, unsigned int height);

        /**
         * deletes this window and terminates glfw
         */
        ~window() override;

    private:

        /**
         * current width of the window
         */
        unsigned int m_width;

        /**
         * current height of the window
         */
        unsigned int m_height;

    public:
        /**
         * pointer to the glfw window
         */
        GLFWwindow* p_window;

    public:
        /**
         * swaps the buffer of the window and updates event inputs
         */
        void update();

        /**
         * clears window and OpenGL color and depth buffer
         */
        void clear();

        /**
         * @return was the close button of the window pressed?
         */
        bool should_close() const;

        /**
         * @return width of the window
         */
        unsigned int get_width() const;

        /**
         * @return height of the window
         */
        unsigned int get_height() const;

        /**
         * @brief called by a glfw helper function on resize
         *
         * @param width new width
         * @param height new height
         */
        void resize(unsigned int width, unsigned int height);
    };
}

#endif //YAE_WINDOWS_HPP
