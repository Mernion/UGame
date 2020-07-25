#pragma once

#include <string>
#include <glm/glm.hpp>

namespace UGame
{
	class UGAME_API Shader
	{
	public:

		static Shader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);
		static Shader* Create(const std::string& filepath);

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) = 0;
		virtual void UploadUniformFloat4(const std::string& name, const glm::vec4& values) = 0;
		virtual void UploadUniformInt(const std::string& name, int value) = 0;

		Shader() = default;
		virtual ~Shader() = default;
	
	};
}