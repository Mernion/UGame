#include "BufferLayout.h"

namespace UGame
{
	void BufferLayout::CalculateOffsetsAndStride()
	{
		uint32_t offset = 0;
		m_Stride = 0;
		for (auto& element : elements)
		{
			element.offset = offset;
			offset += element.size;
			m_Stride += element.size;
		}
	}
}