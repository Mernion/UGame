#pragma once
#include "Shader.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Platform/DirectX/DirectXShader.h"
#include "Renderer.h"

namespace UGame
{
	std::shared_ptr<Shader> Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			UG_CORE_ASSERT(false, "Not Implemented renderer used");
			return nullptr;
			break;
		case RendererAPI::API::DirectX:
			return std::make_shared<DirectXShader>(filepath);
			break;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLShader>(filepath);
			break;
		}

		UG_CORE_ASSERT(false, "Not implemented renderer used");
		return nullptr;
	}
	
	std::shared_ptr<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			UG_CORE_ASSERT(false, "Not Implemented renderer used");
			return nullptr;
			break;
		case RendererAPI::API::DirectX:
			return std::make_shared<DirectXShader>(name, vertexSrc, fragmentSrc);
			break;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLShader>(name, vertexSrc, fragmentSrc);
			break;
		}

		UG_CORE_ASSERT(false, "Not implemented renderer used");
		return nullptr;
	}
}
