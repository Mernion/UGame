#include "UGame/Core.h"
#include <string>
#include <vector>

namespace UGame
{
	enum class ShaderDataType
	{
		None,
		Float, Float2, Float3, Float4,
		Mat3, Mat4,
		Int, Int2, Int3, Int4, 
		Bool
	};

	static unsigned int ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
		case UGame::ShaderDataType::Float:	return 4;
		case UGame::ShaderDataType::Float2:	return 4 * 2;
		case UGame::ShaderDataType::Float3: return 4 * 3;
		case UGame::ShaderDataType::Float4: return 4 * 4;
		case UGame::ShaderDataType::Mat3:	return 4 * 3 * 3;
		case UGame::ShaderDataType::Mat4:	return 4 * 4 * 4;
		case UGame::ShaderDataType::Int:	return 4;
		case UGame::ShaderDataType::Int2:	return 4 * 2;
		case UGame::ShaderDataType::Int3:	return 4 * 3;
		case UGame::ShaderDataType::Int4:	return 4 * 4;
		case UGame::ShaderDataType::Bool:	return 1;
		}

		UG_CORE_ASSERT(false, "Unknown shader data type");
		return 0;
	}

	struct BufferElement
	{
		std::string name;
		ShaderDataType type;
		unsigned int size;
		unsigned int offset;
		bool normalized;

		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false) :
			name(name), type(type), size(ShaderDataTypeSize(type)), offset(0), normalized(normalized)
		{
			;
		}

		unsigned int GetComponentCount() const
		{
			switch (type)
			{
			case UGame::ShaderDataType::Float:	return 1;
			case UGame::ShaderDataType::Float2:	return 2;
			case UGame::ShaderDataType::Float3:	return 3;
			case UGame::ShaderDataType::Float4: return 4;
			case UGame::ShaderDataType::Mat3:	return 4 * 3;
			case UGame::ShaderDataType::Mat4:	return 4 * 4;
			case UGame::ShaderDataType::Int:	return 1;
			case UGame::ShaderDataType::Int2:	return 2;
			case UGame::ShaderDataType::Int3:	return 3;
			case UGame::ShaderDataType::Int4:	return 4;
			case UGame::ShaderDataType::Bool:	return 1;
			}

			UG_CORE_ASSERT(false, "Unknown shader data type");
			return 0;
		}
	};

	class BufferLayout
	{
	public:
		BufferLayout(const std::initializer_list<BufferElement>& elements)
			: elements(elements)
		{
			CalculateOffsetsAndStride();
		}

		inline uint32_t GetStride() const { return m_Stride; }
		inline const std::vector<BufferElement>& GetElements() const { return elements; }

		std::vector<BufferElement>::iterator begin() { return elements.begin(); }
		std::vector<BufferElement>::iterator end() { return elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return elements.cbegin(); }
		std::vector<BufferElement>::const_iterator end() const { return elements.cend(); }

	private:
		void CalculateOffsetsAndStride();

	private:
		std::vector<BufferElement> elements;
		uint32_t m_Stride = 0;
	};
}