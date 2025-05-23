//
// Created by Administrator on 2025/3/27.
//
#include "../ThirdParty.h"
#include "./Image.h"
#ifndef FCT_VK_BUFFER_H
#define FCT_VK_BUFFER_H

namespace FCT
{
    namespace RHI
    {
        class VK_Image : public Image {
        public:
            VK_Image(VK_Context* ctx);
            ~VK_Image();
            void create() override;
            void uploadInitialData();
            void updateData(const void* data, size_t dataSize);
            void updateData(const void* data, size_t dataSize, Fence* fence, std::function<void()>* onCompletion);
            void create(vk::Image image); // 注意，格式信息还是给自己填
            vk::Image getVkImage();
        private:
            VK_Context* m_ctx;
            vk::Image m_image;
            vk::DeviceMemory m_memory;
            bool m_owns;
        };
    }
}


#endif //FCT_VK_BUFFER_H
