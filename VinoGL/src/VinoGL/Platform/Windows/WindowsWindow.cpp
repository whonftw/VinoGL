#include "vnpch.h"
#include "WindowsWindow.h"
#include "VinoGL/Events/EventAggregator.h"
#include "VinoGL/Events/WindowEvents.h"
#include <glad/glad.h>
#include "VinoGL/Events/EventAggregator.h"
#include "VinoGL/Events/InputEvents.h"

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
		glfwTerminate();
	}

	inline unsigned int WindowsWindow::GetWidth() const
	{
		return m_Data.Width;
	}

	inline unsigned int WindowsWindow::GetHeight() const
	{
		return m_Data.Height;
	}

	void * WindowsWindow::GetNativeWindow() const
	{
		return static_cast<void*>(m_Window);
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
		//GLAD
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		VN_CORE_ASSERT(status, "Failed to initialize Glad!");
		glfwSetWindowUserPointer(m_Window, &m_Data);

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			WindowProperties& data = *(WindowProperties*)glfwGetWindowUserPointer(window);
			data.Width = width;
			data.Height = height;
			glViewport(0, 0, width, height);
			Vino::EventAggregator<Vino::WindowSizeChangedEvent>::Publish({ width, height });
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			switch (action)
			{
				case GLFW_PRESS:
				{
					Vino::EventAggregator<Vino::KeyPressedEvent>::Publish({ key, false });
					break;
				}
				case GLFW_REPEAT:
				{
					Vino::EventAggregator<Vino::KeyPressedEvent>::Publish({ key, true });
					break;
				}
				case GLFW_RELEASE:
				{
					Vino::EventAggregator<Vino::KeyReleasedEvent>::Publish({ key });
					break;
				}
			}
		});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int key)
		{
			Vino::EventAggregator<Vino::KeyTypedEvent>::Publish({ key });
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
			switch (action)
			{
				case GLFW_PRESS:
				{
					Vino::EventAggregator<Vino::MouseButtonPressedEvent>::Publish({ button });
					break;
				}
				case GLFW_RELEASE:
				{
					Vino::EventAggregator<Vino::MouseButtonReleasedEvent>::Publish({ button });
					break;
				}
			}
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow*, double xoffset, double yoffset)
		{
			Vino::EventAggregator<Vino::MouseScrolledEvent>::Publish({ xoffset, yoffset });
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow*, double xpos, double ypos)
		{
			Vino::EventAggregator<Vino::MousePositionChangedEvent>::Publish({ xpos, ypos });
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
		{
			EventAggregator<WindowClosedEvent>::Publish({});
		});
	}

	void WindowsWindow::OnUpdate()
	{
		glfwSwapBuffers(m_Window);
		glfwPollEvents();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}
}