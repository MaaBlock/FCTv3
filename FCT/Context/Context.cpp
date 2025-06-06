//
// Created by Administrator on 2025/3/16.
//
#include "../FCTAPI.h"
#include "Context.h"

namespace FCT {
    void Context::nextFrame() {
        m_nextFrame = true;
    }

    void Context::currentFlush() {
        m_currentFlush = true;
    }


    Image* Context::loadTexture(const std::string& filename)
    {
        auto data = m_imageLoader->load(filename);
        SingleBufferImage* image = new SingleBufferImage(this);
        image->width(data.width);
        image->height(data.height);

        bool isSRGB = true;


        Format format;
        switch (data.channels) {
        case 1:
            format = Format::R8_UNORM;
            break;
        case 2:
            format = Format::R8G8_UNORM;
            break;
        case 3:
            format = isSRGB ? Format::R8G8B8A8_SRGB : Format::R8G8B8_UNORM;
            break;
        case 4:
            format = isSRGB ? Format::R8G8B8A8_SRGB : Format::R8G8B8A8_UNORM;
            break;
        default:
            ferr << "Unsupported number of channels: " << data.channels << std::endl;
            format = isSRGB ? Format::R8G8B8A8_SRGB : Format::R8G8B8A8_UNORM;
            break;
        }

        image->format(format);
        image->as(ImageUsage::Texture);
        image->initData(data.data.data(), data.data.size());
        image->create();
        return image;
    }


    void Context::swapQueue() {
        //std::swap(m_pushQueue,m_submitQueue);

    }


    Context::Context(Runtime* runtime) {
        m_defaultGraph = new RenderGraph(this);
        m_currentGraph = m_defaultGraph;
        m_currentGraph->addRef();
        m_compiler = nullptr;
        m_ctxRunning = true;
        //m_flushWnd = nullptr;
        m_nextFrame = false;
        m_currentFlush = true;
        bool isInited = false;
        m_submitThread = std::thread([this,&isInited]
        {
            m_submitThreadId = std::this_thread::get_id();
            isInited = true;
            submitThread();
        });
        FCT_WAIT_FOR(isInited);
        m_ticker = std::bind(&Context::defaultTick,this);
        createCompiler();
        m_generator = new ShaderGenerator();
        m_frameIndex = 0;
        m_maxFrameInFlight = 3;
        m_imageLoader = runtime->createImageLoader();
        m_modelLoader = runtime->createModelLoader();
    }

    Context::~Context() {
        m_ctxRunning = false;
        m_currentGraph->release();
        m_defaultGraph->release();
        m_submitThread.join();
    }
}