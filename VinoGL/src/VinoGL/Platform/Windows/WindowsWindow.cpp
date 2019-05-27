#include "vnpch.h"
#include "WindowsWindow.h"
#include "VinoGL/Events/EventAggregator.h"
#include "VinoGL/Events/Window/WindowEvents.h"
namespace Vino
{
	//static initialization
	bool WindowsWindow::s_Initialized;

	Window* Vino::Window::Create(const WindowProperties& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProperties& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;
		m_Data.VSync = props.VSync;
		Init();
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

	inline unsigned int WindowsWindow::GetWidth() const
	{
		return m_Data.Width;
	}

	inline unsigned int WindowsWindow::GetHeight() const
	{
		return m_Data.Height;
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);
		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSyncEnabled() const
	{
		return m_Data.VSync;
	}

	void WindowsWindow::Init()
	{
		VN_CORE_INFO("Creating Window {0} with resolution: {1}x{2}", m_Data.Title, m_Data.Width, m_Data.Height);
		if (!s_Initialized)
		{
			int success = glfwInit();
			VN_CORE_ASSERT(success, "Could not initialize GLFW!");
			s_Initialized = true;
		}

		m_Window = glfwCreateWindow((int)m_Data.Width, (int)m_Data.Height, m_Data.Title, nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			WindowProperties& data = *(WindowProperties*)glfwGetWindowUserPointer(window);
			data.Width = width;
			data.Height = height;
			EventAggregator<WindowSizeChanged>::Publish({ width, height });
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
		{
			EventAggregator<WindowClosed>::Publish({});
		});
	}
	
	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}
}