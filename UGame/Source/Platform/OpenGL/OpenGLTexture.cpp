#include "OpenGLTexture.h"
#include "../ThirdParty/stb/stb_image.h"
#include "UGame/Core.h"
#include <glad/glad.h>

namespace UGame
{
	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
	{
		int width, height, channels;
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		UG_CORE_ASSERT(data, "Failed to load image!");

		this->width = width;
		this->height = height;

		glCreateTextures(GL_TEXTURE_2D, 1, &rendererId);
		glTextureStorage2D(rendererId, 1, GL_RGB8, this->width, this->height);

		glTextureParameteri(rendererId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(rendererId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureSubImage2D(rendererId, 0, 0, 0, this->width, this->height, GL_RGB, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}
	
	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &rendererId);
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, rendererId);
	}
}
