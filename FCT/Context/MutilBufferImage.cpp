//
// Created by Administrator on 2025/3/30.
//

#include "../FCTAPI.h"
namespace FCT
{
    MutilBufferAffterCreateImageBehavior::MutilBufferAffterCreateImageBehavior(MutilBufferImage* image)
    {
        m_image = image;
    }

    Format MutilBufferAffterCreateImageBehavior::format() const
    {
        return static_cast<MutilBufferImage*>(m_image)->m_images[0]->format();
    }

    Samples MutilBufferAffterCreateImageBehavior::samples() const
    {
        return static_cast<MutilBufferImage*>(m_image)->m_images[0]->samples();
    }

    MutilBufferImage::MutilBufferImage(Context* ctx) : Image(ctx)
    {
        m_behavior = new BeforeCreateImageBehavior(this);
    }

    void MutilBufferImage::create()
    {
    }

    void MutilBufferImage::create(std::vector<RHI::Image*> images)
    {
        for (auto img : m_images)
        {
            FCT_SAFE_RELEASE(img);
        }
        for (auto rtv : m_rtvs)
        {
            rtv->release();
        }
        m_rtvs.clear();
        m_images = images;
        for (auto img : m_images)
        {
            FCT_SAFE_ADDREF(img);
        }
        m_width = images[0]->width();
        m_height = images[0]->height();
        delete m_behavior;
        m_behavior = new MutilBufferAffterCreateImageBehavior(this);
        if (m_usage & ImageUsage::RenderTarget)
        {
            for (auto img : m_images)
            {
                auto rtv = m_ctx->createRenderTargetView();
                rtv->image(img);
                rtv->create();
                m_rtvs.push_back(rtv);
            }
        }
    }

    void MutilBufferImage::as(ImageUsageFlags usage)
    {
        m_usage |= usage;
        if (usage & ImageUsage::RenderTarget && m_rtvs.empty())
        {
            for (auto img : m_images)
            {
                auto rtv = m_ctx->createRenderTargetView();
                rtv->image(img);
                rtv->create();
                m_rtvs.push_back(rtv);
            }
        }
    }

    void MutilBufferImage::bind(Context* ctx)
    {
        Image::bind(ctx);
    }

    std::vector<Image*> MutilBufferImage::getTargetImages()
    {
        if (m_rtvs.size()) {
            return {this};
        }
        return {};
    }

    RHI::RenderTargetView* MutilBufferImage::currentTargetView()
    {
        return m_rtvs[m_currentIndex];
    }
}
