#pragma once
namespace FCT {
    enum class PipelineResourceType {
        VertexShader,
        PixelShader,
        VertexBuffer,
        IndexBuffer,
        InputLayout,
        DepthStencilState,
        RasterizerState,
        BlendState,
        Texture,
        DrawCall,
        ConstBuffer,
        TextureArray
    };
    class IPipelineResource : public RefCount {
    public:
        virtual ~IPipelineResource() {};

        virtual PipelineResourceType getType() const = 0;
        virtual void bind() = 0;
        virtual void unbind() = 0;
    };

}// namespace FCT
