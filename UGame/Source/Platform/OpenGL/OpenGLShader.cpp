#include "OpenGLShader.h"
#include "glad/glad.h"
#include <vector>
#include <glm/gtc/type_ptr.hpp>
#include "UGame/Log.h"

namespace UGame
{
	OpenGLShader::OpenGLShader(const std::string& vertexShaderSrc, const std::string& fragmentShaderSrc) : Shader(vertexShaderSrc, fragmentShaderSrc)
	{
		const GLchar* vertexSrc = vertexShaderSrc.c_str();
		unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexSrc, NULL);
		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(vertexShader);

			UG_CORE_ERROR("{0}", infoLog.data());
			return;
		}

		unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		const GLchar* fragmentSrc = fragmentShaderSrc.c_str();
		glShaderSource(fragmentShader, 1, &fragmentSrc, NULL);
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);
			
			UG_CORE_ERROR("{0}", infoLog.data());
			return;
		}

		programId = glCreateProgram();
		glAttachShader(programId, vertexShader);
		glAttachShader(programId, fragmentShader);
		glLinkProgram(programId);

		GLint isLinked = 0;
		glGetProgramiv(programId, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(programId, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(programId, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			UG_CORE_ERROR("{0}", infoLog.data());
			return;
		}

		glDetachShader(programId, vertexShader);
		glDetachShader(programId, fragmentShader);

		glUseProgram(programId);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
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
}