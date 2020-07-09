#pragma once

#include <string>

namespace UGame
{
	class Shader
	{
	public:

		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~Shader();

		virtual void Bind() = 0;
		virtual void Unbind() = 0;
	};
}