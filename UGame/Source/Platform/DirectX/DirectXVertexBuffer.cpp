#include "DirectXVertexBuffer.h"
#include <d3d11.h>
#include "Renderer/GraphicsContext.h"
#include "Platform/DirectX/DirectXContext.h"

namespace UGame
{
	DirectXVertexBuffer::DirectXVertexBuffer(float* data, size_t size)
	{		
		D3D11_BUFFER_DESC vertex_buff_descr = {};
		vertex_buff_descr.ByteWidth = size;
		vertex_buff_descr.Usage = D3D11_USAGE_DEFAULT;
		vertex_buff_descr.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		D3D11_SUBRESOURCE_DATA sr_data = { 0 };
		sr_data.pSysMem = data;

		DirectXContext* context = static_cast<DirectXContext*>(Application::Get().GetWindow().GetGraphicsContext());

		HRESULT hr = context->GetDevice()->CreateBuffer(
			&vertex_buff_descr,
			&sr_data,
			&vertex_buffer_ptr);
		UG_CORE_ASSERT(SUCCEEDED(hr));
	}

	void DirectXVertexBuffer::Bind()
	{
		;
	}

	void DirectXVertexBuffer::Unbind()
	{
		;
	}

	DirectXVertexBuffer::~DirectXVertexBuffer()
	{
		;
	}

}
