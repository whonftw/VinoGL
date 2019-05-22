#pragma once
#include "VinoGL/Window.h"
#include <GLFW/glfw3.h>

namespace Vino
{
	class WindowsWindow: public Window
	{
	public:
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override;
		inline unsigned int GetHeight() const override;

		void SetVSync(bool enabled) override;
		bool IsVSyncEnabled() const override;
	protected:
		WindowsWindow(const WindowProperties& props);

		// Takes care of GLFW specific initialization
		virtual void Init();
		virtual void Shutdown();
	private:
		GLFWwindow* m_Window;
		static bool s_Initialized;
		WindowProperties m_Data;
		friend class Window;
	};
}

