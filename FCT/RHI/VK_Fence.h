//
// Created by Administrator on 2025/4/2.
//
#include "./Fence.h"
#ifndef VK_FENCE_H
#define VK_FENCE_H

namespace FCT
{
    class VK_Context;
}

namespace FCT
{
    namespace RHI
    {
        class VK_Fence : public Fence{
        public:
            VK_Fence(VK_Context* ctx);
            void reset() override;
            void create() override;
            void waitFor() override;
        private:
            VK_Context* m_ctx;
            vk::Fence m_fence;
        };
    }
}


#endif //VK_FENCE_H
