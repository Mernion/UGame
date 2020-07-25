#include "ShaderLibrary.h"
#include "UGame/Core.h"

namespace UGame
{
	void ShaderLibrary::Add(const std::string& name, const std::shared_ptr<Shader>& shader)
	{
		UG_CORE_ASSERT(shaders.find(name) == shaders.end(), "Shader already exist");
		shaders[name] = shader;
	}

	void ShaderLibrary::Add(const std::shared_ptr<Shader>& shader)
	{
		auto& name = shader->GetName();
		Add(name, shader);
	}

	std::shared_ptr<Shader> ShaderLibrary::Load(const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(shader);
		return shader;
	}

	std::shared_ptr<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(name, shader);
		return shader;
	}

	std::shared_ptr<Shader> ShaderLibrary::Get(const std::string& name)
	{
		UG_CORE_ASSERT(shaders.find(name) != shaders.end(), "Shader already exist");
		return shaders[name];
	}
}
