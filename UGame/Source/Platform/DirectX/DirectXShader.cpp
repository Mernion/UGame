#include "DirectXShader.h"
#include <vector>
#include "UGame/Log.h"
#include <cstring>
#include <fstream>

#include "DirectXContext.h"

namespace UGame
{
	DirectXShader::DirectXShader(const std::string& filename)
	{
	}
	
	DirectXShader::DirectXShader(const std::string name, const std::string& vertexShaderSrc, const std::string& fragmentShaderSrc)
		: name(name)
	{
		UINT flags = D3DCOMPILE_ENABLE_STRICTNESS;
		flags |= D3DCOMPILE_DEBUG;
		
		HRESULT hr = D3DCompile(vertexShaderSrc.c_str(), vertexShaderSrc.length(),
			nullptr, nullptr, nullptr, "vs_main", "vs_5_0", flags, 0, &vs_blob, &error_blob);
		if (FAILED(hr))
		{
			if (error_blob)
			{
				UG_CORE_ERROR("Failed to compile vs shader : {0}", (char*) error_blob->GetBufferPointer());
			}
		}

		hr = D3DCompile(fragmentShaderSrc.c_str(), fragmentShaderSrc.length(),
			nullptr, nullptr, nullptr, "ps_main", "ps_5_0", flags, 0, &ps_blob, &error_blob);

		if (FAILED(hr))
		{
			if (error_blob)
			{
				UG_CORE_ERROR("Failed to compile vs shader : {0}", (char*)error_blob->GetBufferPointer());
			}
		}

		DirectXContext* context = static_cast<DirectXContext*>(Application::Get().GetWindow().GetGraphicsContext());


		hr = context->GetDevice()->CreateVertexShader(
			vs_blob->GetBufferPointer(),
			vs_blob->GetBufferSize(),
			NULL,
			&vertexShader);
		UG_CORE_ASSERT(SUCCEEDED(hr));

		hr = context->GetDevice()->CreatePixelShader(
			ps_blob->GetBufferPointer(),
			ps_blob->GetBufferSize(),
			NULL,
			&pixelShader);
		UG_CORE_ASSERT(SUCCEEDED(hr));
	}

	void DirectXShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{

	}

	void DirectXShader::UploadUniformFloat4(const std::string& name, const glm::vec4& values)
	{

	}

	void DirectXShader::UploadUniformInt(const std::string& name, int value)
	{

	}

	void DirectXShader::Bind()
	{
		
	}

	void DirectXShader::Unbind()
	{
		
	}

	DirectXShader::~DirectXShader()
	{
		
	}

}
