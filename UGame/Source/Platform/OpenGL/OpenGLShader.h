#pragma once
#include "Renderer/Shader.h"
#include "glad/glad.h"

namespace UGame
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string name, const std::string& vertexSrc, const std::string& fragmentSrc);
		OpenGLShader(const std::string& filepath);
		~OpenGLShader();

		void Bind() override;
		void Unbind() override;

		const std::string& GetName() const override { return name; }

		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) override;
		void UploadUniformFloat4(const std::string& name, const glm::vec4& values) override;
		void UploadUniformInt(const std::string& name, int value) override;
		
	private:
		std::string ReadFile(const std::string& filepath);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSrc);
		
		unsigned int programId;
		std::string name;
	};
}
