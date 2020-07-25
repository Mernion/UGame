#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include "UGame/Core.h"

namespace UGame
{
	class UGAME_API Texture
	{
	public:
		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void Bind(uint32_t slot = 0) const = 0;

		virtual ~Texture() = default;
	};

	class UGAME_API Texture2D : public Texture
	{
	public:
		static std::shared_ptr<Texture2D> Create(const std::string& path);
	};
}