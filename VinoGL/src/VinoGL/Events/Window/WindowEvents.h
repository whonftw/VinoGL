#pragma once
#include "VinoGL/Events/EventAggregator.h"
namespace Vino {

	struct WindowSizeChanged : Vino::PublicEvent
	{
		WindowSizeChanged(int width, int height): Width(width), Height(height){}
		int Width;
		int Height;
	};

	struct WindowClosed : Vino::PublicEvent
	{

	};

}