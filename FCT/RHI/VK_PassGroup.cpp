//
// Created by Administrator on 2025/3/26.
//

#include "../FCTAPI.h"

namespace FCT
{
    namespace RHI
    {
        VK_PassGroup::VK_PassGroup(VK_Context* ctx) : m_createInfo{},m_beginInfo{},m_framebufferInfo{}
        {
            m_ctx = ctx;
        }
/*
        uint32_t VK_PassGroup::getImageIndex(FCT::Image* image)
        {
            return m_imageIndices[image];
        }
*/
        void VK_PassGroup::create()
        {
            collectAttachments();
            for (auto& pass : m_passes)
            {
                pass->create(this);
            }
            m_createInfo.attachmentCount = m_attachments.size();
            m_createInfo.dependencyCount = 0;
            m_createInfo.pAttachments = m_attachments.data();
            m_createInfo.pDependencies = nullptr;
            collectSubpasses();
            m_createInfo.pSubpasses = m_subpasses.data();
            m_createInfo.subpassCount = m_subpasses.size();
            m_renderPass = m_ctx->device().createRenderPass(m_createInfo);
            m_beginInfo.renderPass = m_renderPass;
        }

        uint32_t VK_PassGroup::getPassIndex(Pass* pass)
        {
            return m_passIndices[pass];
        }

        void VK_PassGroup::beginSubmit()
        {
            collectImageViews();
            m_framebufferInfo.attachmentCount = m_framebufferViews.size();
            m_framebufferInfo.pAttachments = m_framebufferViews.data();
            //m_framebufferInfo.width =
        }

        void VK_PassGroup::collectSubpasses()
        {
            for (auto& srcPass : m_passes)
            {
                auto pass = (VK_Pass*&)(srcPass);
                m_passIndices[pass] = m_subpasses.size();
                m_subpasses.push_back(pass->getDescription());
            }
        }

        void VK_PassGroup::collectAttachments()
        {
            for (auto& pass : m_passes)
            {
                for (auto& targetPair : pass->renderTargets())
                {
                    auto& image = targetPair.second;
                    vk::AttachmentDescription desc;
                    desc.format = ToVkFormat(image->format());
                    desc.samples = ToVkSampleCount(image->samples());
                    desc.loadOp = vk::AttachmentLoadOp::eDontCare;
                    desc.storeOp = vk::AttachmentStoreOp::eStore;
                    desc.initialLayout = vk::ImageLayout::eUndefined;
                    //todo:优化initialLayout
                    if (image->getType() == RenderTargetType::WindowTarget && !m_nextPassGroup.size())
                    {
                        desc.finalLayout = vk::ImageLayout::ePresentSrcKHR;
                    } else
                    {
                        desc.finalLayout = vk::ImageLayout::eGeneral;
                        //Todo: 根据nextPassGroup来优化finalLayout，或者由外部手动指定finalLayout
                    }
                    desc.stencilLoadOp = vk::AttachmentLoadOp::eDontCare;
                    desc.stencilStoreOp = vk::AttachmentStoreOp::eDontCare;
                    //m_imageIndices[image] = m_attachments.size();
                    m_attachmentSlots[m_attachments.size()] = AttachmentSlot(
                        image,
                        ImageUsage::RenderTarget,
                        targetPair.first);
                    auto vkPass = static_cast<VK_Pass*>(pass);
                    vkPass->targetAttachmentIndices()[targetPair.first] = m_attachments.size();
                    m_attachments.push_back(desc);
                }
            }
        }

        void VK_PassGroup::collectImageViews() // 注意，顺序要保持和collectAttachments一样
        {

            for (auto& pass : m_passes)
            {
                for (auto& targetPair : pass->renderTargets())
                {
                    auto& image = targetPair.second;
                    m_framebufferViews.push_back(
                        static_cast<VK_RenderTargetView*>(image->currentTargetView())->view());
                //    m_attachments.push_back(desc);
                }
            }
        }
    }
}
