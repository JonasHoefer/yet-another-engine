//
// Created by jonas on 17.12.2017.
//

#include "yae/window.hpp"

namespace yae
{
    /**
     * @brief helper function to allow each window to handle resize calls independent
     *
     * @param glfw_window - pointer to a GLFWwindow
     * @param width - new width of the window
     * @param height - new height of the window
     */
    static void glfw_resize_fun(GLFWwindow* glfw_window, int width, int height)
    {
        static_cast<window*>(glfwGetWindowUserPointer(glfw_window))->resize(static_cast<unsigned int>(width),
                                                                            static_cast<unsigned int>(height));
    }

    window::window(const char* title, unsigned int width, unsigned int height)
            : m_width(width), m_height(height)
    {
        if (utils::counter<window>::instance_count == 1)
        {
            if (!glfwInit())
            {
                std::cerr << "[Window|ERROR] Could not initialize GLFW!" << std::endl;
            }
            else
            {
                std::cout << "[Window|INFO] Initialized GLFW!" << std::endl;
            }
        }


        glfwWindowHint(GLFW_SAMPLES, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        p_window = glfwCreateWindow(m_width, m_height, title, nullptr, nullptr);


        if (!p_window)
        {
            glfwTerminate();
            std::cerr << "[Window|ERROR] Could not create window!" << std::endl;
        }

        glfwSetWindowSizeCallback(p_window, glfw_resize_fun);
        glfwSetWindowUserPointer(p_window, this);
        glfwMakeContextCurrent(p_window);

        glewExperimental = GL_TRUE;
        if (glewInit() != GLEW_OK)
        {
            std::cerr << "[Window|ERROR] Could not initialize GLEW!" << std::endl;
        }
        else
        {
            std::cout << "[Window|INFO] Initialized GLEW!" << std::endl;
        }

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glFrontFace(GL_CCW);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    }

    window::~window()
    {
        glfwDestroyWindow(p_window);
        if (utils::counter<window>::instance_count == 1)
        {
            glfwTerminate();
            std::cout << "[Window|INFO] terminated GLFW!" << std::endl;
        }
    }

    unsigned int window::get_width() const
    {
        return m_width;
    }

    unsigned int window::get_height() const
    {
        return m_height;
    }

    void window::update()
    {
        glfwPollEvents();
        glfwSwapBuffers(p_window);
    }

    bool window::should_close() const
    {
        return glfwWindowShouldClose(p_window) != 0;
    }

    void window::clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void window::resize(unsigned int width, unsigned int height)
    {
        m_width = width;
        m_height = height;

        int framebuffer_width, framebuffer_height;
        glfwGetFramebufferSize(p_window, &framebuffer_width, &framebuffer_height);
        glViewport(0, 0, framebuffer_height, framebuffer_height);
    }
}
