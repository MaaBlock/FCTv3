//
// Created by Administrator on 2025/3/22.
//
#include "../ThirdParty.h"
#include "./Window.h"
#include "../Runtime/Runtime.h"
#ifndef GLFW_WINDOW_H
#define GLFW_WINDOW_H

namespace FCT
{
    class GLFW_Window : public Window
    {
    public:
        GLFW_Window(GLFW_UICommon* common, Runtime* rt);
        ~GLFW_Window();
        void invokeResizeCallbacks(int width, int height);
        void invokeMouseMoveCallbacks(int xpos, int ypos);
        void invokeMouseCallbacks(int button, int action, int mods);
        void invokeKeyCallbacks(int key, int scancode, int action, int mods);
        void invokeScrollCallbacks(int xoffset, int yoffset);
        void create();
        bool isRunning() const override;
        void bind(Context* ctx) override;
        void swapBuffers() override;
        int getWidth() override;
        int getHeight() override;
        void setCursorPos(int x, int y) override;
        Image* getImage() const override;
        //std::vector<Image*> getTargetImages() override;
        ImageRenderTarget* getCurrentTarget() override;
        RHI::Semaphore* getImageAvailableSemaphore() override;
        void addRenderFinshSemaphore(RHI::Semaphore* semaphore) override;
        void setPresentFinshSemaphore(RHI::Semaphore* semaphore) override;

    private:
        GLFWwindow* m_window;
        Runtime* m_rt;
        GLFW_UICommon* m_common;
        Context* m_ctx;
        void recreateSwapchain(int width, int height);
#ifdef FCT_USE_VULKAN
        VkSurfaceKHR m_vkSurface;
#endif

        void* m_swapchainNativeHandle;
        //std::function<void()> recreateSwapChain;
        //std::function<void()> present;
    };

    class GLFW_UICommon;
}

#endif //GLFW_WINDOW_H
