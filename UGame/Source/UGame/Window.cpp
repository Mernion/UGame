#include "Window.h"

namespace UGame
{
	Window* Window::Create(const WindowProps& props)
	{
#ifdef UG_PLATFORM_WINDOWS
		return new WindowsWindow(props);
#endif
		UG_CORE_ASSERT(false, "Unimplemented platform");
		return nullptr;
	}
}