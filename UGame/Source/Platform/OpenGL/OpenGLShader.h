#pragma once
#include "Renderer/Shader.h"

namespace UGame
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~OpenGLShader();

		void Bind() override;
		void Unbind() override;

		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) override;
		
	private:

		unsigned int programId;
	};
}
