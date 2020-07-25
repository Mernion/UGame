#include "OpenGLShader.h"
#include "glad/glad.h"
#include <vector>
#include <glm/gtc/type_ptr.hpp>
#include "UGame/Log.h"
#include <cstring>
#include <fstream>

namespace UGame
{
	static GLenum ShaderTypeFromString(const std::string& type)
	{
		if (type == "vertex")						return GL_VERTEX_SHADER;
		if (type == "fragment" || type == "pixel")	return GL_FRAGMENT_SHADER;

		UG_CORE_ASSERT(false, "Uknown shader type");
		return 0;
	}
	
	OpenGLShader::OpenGLShader(const std::string& filename)
	{
		std::string source  = ReadFile(filename);
		auto shaderSource = PreProcess(source);
		Compile(shaderSource);
	}
	
	OpenGLShader::OpenGLShader(const std::string& vertexShaderSrc, const std::string& fragmentShaderSrc)
	{
		std::unordered_map<GLenum, std::string> sources;
		sources[GL_VERTEX_SHADER] = vertexShaderSrc;
		sources[GL_FRAGMENT_SHADER] = fragmentShaderSrc;
		Compile(sources);
	}

	void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		GLint location = glGetUniformLocation(programId, name.c_str());
		UG_CORE_ASSERT(location != -1, "Uniform location is empty!");
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& values)
	{
		GLint location = glGetUniformLocation(programId, name.c_str());
		UG_CORE_ASSERT(location != -1, "Uniform location is empty!");
		glUniform4f(location, values.x, values.y, values.z, values.w);
	}

	void OpenGLShader::UploadUniformInt(const std::string& name, int value)
	{
		GLint location = glGetUniformLocation(programId, name.c_str());
		UG_CORE_ASSERT(location != -1, "Uniform location is empty!");
		glUniform1i(location, value);
	}

	void OpenGLShader::Bind()
	{
		glUseProgram(programId);
	}

	void OpenGLShader::Unbind()
	{
		glUseProgram(0);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(programId);
	}

	std::string OpenGLShader::ReadFile(const std::string& filepath)
	{
		std::string result;
		std::ifstream in(filepath, std::ios::in, std::ios::binary);
		if (in)
		{
			in.seekg(0, std::ios::end);
			result.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&result[0], result.size());
			in.close();
		}
		else
		{
			UG_CORE_ERROR("Could not open file {0}", filepath);
		}

		return result;
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& source)
	{
		std::unordered_map<GLenum, std::string> shaderSources;

		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = source.find(typeToken, 0);
		while (pos != std::string::npos)
		{
			size_t eol = source.find_first_of("\r\n", pos);
			UG_CORE_ASSERT(eol != std::string::npos, "Syntax error");
			size_t begin = pos + typeTokenLength + 1;
			std::string type = source.substr(begin, eol - begin);
			UG_CORE_ASSERT(ShaderTypeFromString(type), "Invalid shader type specified");

			size_t nextLinePos = source.find_first_not_of("\r\n", eol);
			pos = source.find(typeToken, nextLinePos);
			shaderSources[ShaderTypeFromString(type)] = source.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));
		}

		return shaderSources;
	}

	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSrc)
	{
		programId = glCreateProgram();
		std::vector<GLenum> glShaderIDs(shaderSrc.size());
		
		for (auto& kv : shaderSrc)
		{
			GLenum shaderType = kv.first;
			const std::string& source = kv.second;

			GLuint shader = glCreateShader(shaderType);
			const GLchar* sourceCstr = source.c_str();
			glShaderSource(shader, 1, &sourceCstr, NULL);

			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				glDeleteShader(shader);

				UG_CORE_ERROR("{0}", infoLog.data());
				return;
			}

			glAttachShader(programId, shader);
			glShaderIDs.push_back(shader);
		}

		glLinkProgram(programId);

		GLint isLinked = 0;
		glGetProgramiv(programId, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(programId, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(programId, maxLength, &maxLength, &infoLog[0]);

			for (auto id : glShaderIDs)
			{
				glDeleteShader(id);
			}

			UG_CORE_ERROR("{0}", infoLog.data());
			return;
		}

		for (auto id : glShaderIDs)
		{
			glDetachShader(programId, id);
		}
	}
}