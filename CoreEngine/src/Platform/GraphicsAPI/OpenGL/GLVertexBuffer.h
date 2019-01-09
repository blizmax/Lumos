#pragma once

#include "Graphics/API/VertexBuffer.h"
#include "GLDebug.h"

namespace jm
{
	class GLVertexBuffer : public VertexBuffer
	{
	private:
		uint m_Handle{};
		BufferUsage m_Usage;
		uint m_Size;
		graphics::BufferLayout m_Layout;
	public:
		explicit GLVertexBuffer(BufferUsage usage);
		~GLVertexBuffer();

		void Resize(uint size) override;
		void SetLayout(const graphics::BufferLayout& layout) override;
		void SetData(uint size, const void* data) override;
		void SetDataSub(uint size, const void* data, uint offset) override;

		void ReleasePointer() override;

		void Bind() override;
		void Unbind() override;
	protected:
		void* GetPointerInternal() override;
	};
}