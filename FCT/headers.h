//
// Created by Administrator on 2025/2/19.
//
#define FCT_USE_MEMORY_CHECK
#ifndef FCT_HEADER_H
#define FCT_HEADER_H
#include "ThirdParty.h"
#include "ToolDefine.h"
#include "./predefine.h"
#include "./MutilThreadBase/SharePtr.h"
#include "./DebugTools/MemoryCheak.h"
#include "./DebugTools/ScopeTimer.h"
#include "./Base/Flags.h"
#include "./Bases.h"
#include "./Memory/ObjectPool.h"
#include "Runtime/Runtime.h"
#include "./Context/Vertex.h"
#include "./Context/Mesh.h"
#include "./Context/ResourceLayout.h"
#include "./Context/ShaderGenerator.h"
#include "./Context/VertexShader.h"
#include "./Context/PixelShader.h"
#include "./Context/ImageRenderTarget.h"
#include "./Context/Image.h"
#include "./Context/SingleBufferImage.h"
#include "./Context/MutilBufferImage.h"
#include "./Context/Uniform.h"
#include "./Context/PassResource.h"
#include "./Context/Object.h"
#include "DebugTools/OutStream.h"
#include "./RHI/ViewportState.h"
#include "./RHI/RasterizationState.h"
#include "./RHI/RootSign.h"
#include "./RHI/RasterizationPipeline.h"
#include "./RHI/Pass.h"
#include "./RHI/PassGroup.h"
#include "./RHI/Swapcain.h"
#include "./RHI/RenderPass.h"
#include "./RHI/Image.h"
#include "./RHI/RenderTargetView.h"
#include "./RHI/VertexShader.h"
#include "./RHI/PixelShader.h"
#include "./RHI/CommandBuffer.h"
#include "./RHI/CommandPool.h"
#include "./RHI/Semaphore.h"
#include "./RHI/Fence.h"
#include "./RHI/DepthStencilView.h"
#include "./RHI/ShaderBinary.h"
#include "./RHI/BlendState.h"
#include "./RHI/VertexBuffer.h"
#include "./RHI/IndexBuffer.h"
#include "./RHI/ConstBuffer.h"
#include "./RHI/DescriptorPool.H"
#include "./RHI/TextureView.h"
#include "./RHI/DepthStencilView.h"
#include "./RHI/Sampler.h"
#include "./RHI/DepthStencilState.h"
#include "./Context/FencePool.h"
#include "./Context/SemaphorePool.h"
#include "./Context/RenderGraph.h"
#include "./Context/TraditionRenderPass.h"
#include "./ModelLoader/ModelLoader.h"
#include "./VertexAndText/VertexContext.h"
#include "./VertexAndText/Freetype_FontCommon.h"
#include "./VertexAndText/Freetype_Font.h"
//#include "MutilThreadBase/RefCount.h"
//#include "MutilThreadBase/TlsPtr.h"
#include "./Context/Context.h"
#include "./Context/Context.hpp"
#include "./Context/Primitives.h"
//#include "Context/Image.h"
//#include "UI/Window.h"
#include "./UI/AutoViewport.h"
#endif //FCT_HEADER_H