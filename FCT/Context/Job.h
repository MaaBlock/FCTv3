//
// Created by Administrator on 2025/5/1.
//

#ifndef JOB_H
#define JOB_H
#include "PassResource.h"
#include "ResourceLayout.h"
#include "Vertex.h"
#include "Mesh.h"

namespace FCT {
    class VertexShader;
    class PixelShader;
    class BlendState;
    class RasterizationState;
    class DepthStencilState;

    struct TraditionPipelineState
    {
        TraditionPipelineState()
        {
            vertexShader = nullptr;
            pixelShader = nullptr;
            blendState = nullptr;
            rasterizationState = nullptr;
            depthStencilState = nullptr;
        }
        PixelLayout pixelLayout;
        VertexLayout vertexLayout;
        ResourceLayout resourceLayout;
        VertexShader* vertexShader;
        PixelShader* pixelShader;
        BlendState* blendState;
        RasterizationState* rasterizationState;
        DepthStencilState* depthStencilState;
    };

    namespace RHI
    {
        class CommandBuffer;
    }

    enum class JobType
    {
        TraditionRender,
        Submit,
    };
    struct Job : RefCount
    {
        virtual JobType getType() const = 0;
        virtual void submit(RHI::CommandBuffer* cmdBuf) = 0;
    };

    struct TraditionRenderJob : Job
    {
        JobType getType() const override
        {
            return JobType::TraditionRender;
        }
        PassResource* resource;
        TraditionPipelineState* state;
        std::vector<StaticMesh<uint16_t>*> meshes16;
        std::vector<StaticMesh<uint32_t>*> meshes32;
        std::vector<DynamicMesh<uint32_t>*> meshes32Dynamic;
        std::vector<DynamicMesh<uint16_t>*> meshes16Dynamic;
        bool needsUpdate;
        bool isCreated;
        TraditionRenderJob()
          : resource(nullptr)
          , state(nullptr)
          , needsUpdate(false)
          , isCreated(false)
        {
        }
        TraditionRenderJob& addMesh(StaticMesh<uint16_t>* mesh)
        {
            meshes16.push_back(mesh);
            needsUpdate = true;
            return *this;
        }
        TraditionRenderJob& addMesh(StaticMesh<uint32_t>* mesh)
        {
            meshes32.push_back(mesh);
            needsUpdate = true;
            return *this;
        }
        TraditionRenderJob& addMesh(DynamicMesh<uint32_t>* mesh)
        {
            meshes32Dynamic.push_back(mesh);
            needsUpdate = true;
            return *this;
        }
        TraditionRenderJob& addMesh(DynamicMesh<uint16_t>* mesh)
        {
            meshes16Dynamic.push_back(mesh);
            needsUpdate = true;
            return *this;
        }
        TraditionRenderJob& setPassResource(PassResource* resource)
        {
            this->resource = resource;
            return *this;
        }
        TraditionRenderJob& setPipelineState(TraditionPipelineState* state)
        {
            this->state = state;
            return *this;
        }
        virtual void submit(RHI::CommandBuffer* cmdBuf)
        {
            for (auto& mesh : meshes16)
            {
                mesh->bind(cmdBuf);
                mesh->draw(cmdBuf);
            }
            for (auto& mesh : meshes32)
            {
                mesh->bind(cmdBuf);
                mesh->draw(cmdBuf);
            }
            for (auto& mesh : meshes32Dynamic)
            {
                mesh->bind(cmdBuf);
                mesh->draw(cmdBuf);
            }
            for (auto& mesh : meshes16Dynamic)
            {
                mesh->bind(cmdBuf);
                mesh->draw(cmdBuf);
            }
        }
    };

    struct SubmitJob : Job
    {
        JobType getType() const override
        {
            return JobType::Submit;
        }
        virtual void submit(RHI::CommandBuffer* cmdBuf)
        {

        }
    };
    struct ViewportJob : public SubmitJob
    {
        Vec2 viewportLt;
        Vec2 viewportRb;
        Vec2 scissorLt;
        Vec2 scissorRb;
        ViewportJob(Vec2 viewportLt,Vec2 viewportRb,Vec2 scissorLt,Vec2 scissorRb)
        {
            this->viewportLt = viewportLt;
            this->viewportRb = viewportRb;
            this->scissorLt = scissorLt;
            this->scissorRb = scissorRb;
        }
        JobType getType() const override
        {
            return JobType::Submit;
        }
        virtual void submit(RHI::CommandBuffer* cmdBuf)
        {
            cmdBuf->viewport(viewportLt, viewportRb);
            cmdBuf->scissor(scissorLt, scissorRb);
        }
    };
}
#endif //JOB_H
