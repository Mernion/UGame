#include "Window.h"

#include "Platform/Windows/WindowsWindow.h"
#include "Platform/OpenGL/LinuxWindow.h"

namespace UGame
{
	Window* Window::Create(const WindowProps& props)
	{
#ifdef UG_PLATFORM_WINDOWS
		return new WindowsWindow(props);
#elif UG_PLATFORM_LINUX
		return new LinuxWindow(props);
#endif
		UG_CORE_ASSERT(false, "Unimplemented platform");
		return nullptr;
	}
}
