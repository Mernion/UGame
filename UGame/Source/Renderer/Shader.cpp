#pragma once
#include "Shader.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Renderer.h"

namespace UGame
{
	Shader* Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			UG_CORE_ASSERT(false, "Not Implemented renderer used");
			return nullptr;
			break;
		case RendererAPI::API::OpenGL:
			return new OpenGLShader(filepath);
			break;
		}

		UG_CORE_ASSERT(false, "Not implemented renderer used");
		return nullptr;
	}
	
	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			UG_CORE_ASSERT(false, "Not Implemented renderer used");
			return nullptr;
			break;
		case RendererAPI::API::OpenGL:
			return new OpenGLShader(vertexSrc, fragmentSrc);
			break;
		}

		UG_CORE_ASSERT(false, "Not implemented renderer used");
		return nullptr;
	}
}
