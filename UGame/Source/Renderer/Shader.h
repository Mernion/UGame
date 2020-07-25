#pragma once

#include <string>
#include <glm/glm.hpp>
#include <memory>
#include <unordered_map>
#include "UGame/Core.h"

namespace UGame
{
	class UGAME_API Shader
	{
	public:

		static std::shared_ptr<Shader> Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		static std::shared_ptr<Shader> Create(const std::string& filepath);

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual const std::string& GetName() const = 0;

		virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) = 0;
		virtual void UploadUniformFloat4(const std::string& name, const glm::vec4& values) = 0;
		virtual void UploadUniformInt(const std::string& name, int value) = 0;

		virtual ~Shader() = default;
	
	};
}