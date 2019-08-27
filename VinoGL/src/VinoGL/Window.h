#pragma once
#include "VinoGL/Core.h"

namespace Vino
{
	struct WindowProperties
	{
		const char* Title = "Vino Renderer";
		unsigned int Width = 1280;
		unsigned int Height = 720;
		bool VSync = true;
	};

	class VINO_API Window
	{
	public:
		virtual ~Window() {}
		virtual void OnUpdate() = 0;
		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSyncEnabled() const = 0;
		virtual void* GetNativeWindow() const = 0;
		// To be implemented per platform
		static Window* Create(const WindowProperties& properties = WindowProperties());
	};
}