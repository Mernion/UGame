#pragma once

#include <string>
#include <glm/glm.hpp>

namespace UGame
{
	class Shader
	{
	public:

		static Shader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) = 0;

		virtual ~Shader();
		
	protected:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
	};
}