#pragma once
#include "Renderer/Shader.h"
#include <d3dcommon.h>

namespace UGame
{
	class DirectXShader : public Shader
	{
	public:
		DirectXShader(const std::string name, const std::string& vertexSrc, const std::string& fragmentSrc);
		DirectXShader(const std::string& filepath);
		~DirectXShader();

		void Bind() override;
		void Unbind() override;

		const std::string& GetName() const override { return name; }

		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) override;
		void UploadUniformFloat4(const std::string& name, const glm::vec4& values) override;
		void UploadUniformInt(const std::string& name, int value) override;
		
	private:

		std::string name;

		ID3DBlob* vs_blob = nullptr;
		ID3DBlob* ps_blob = nullptr;
		ID3DBlob* error_blob = nullptr;

	};
}
