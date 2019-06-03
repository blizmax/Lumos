#include "LM.h"
#include "Swapchain.h"

#ifdef LUMOS_RENDER_API_VULKAN
#include "Platform/Vulkan/VKSwapchain.h"
#endif

#ifdef LUMOS_RENDER_API_OPENGL
#include "Platform/OpenGL/GLSwapchain.h"
#endif

#include "Graphics/API/GraphicsContext.h"

namespace Lumos
{
	namespace Graphics
	{
		Swapchain* Swapchain::Create(uint width, uint height)
		{
			switch (Graphics::GraphicsContext::GetRenderAPI())
			{
#ifdef LUMOS_RENDER_API_OPENGL
			case RenderAPI::OPENGL:		return new GLSwapchain(width, height);
#endif
#ifdef LUMOS_RENDER_API_VULKAN
			case RenderAPI::VULKAN:		return new VKSwapchain(width, height);
#endif
			}
			return nullptr;
		}
	}
}
