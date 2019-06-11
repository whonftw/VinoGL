#pragma once
#include "VinoGL/Events/EventAggregator.h"
namespace Vino {

	struct WindowSizeChangedEvent : Vino::PublicEvent
	{
		WindowSizeChangedEvent(int width, int height): Width(width), Height(height){}
		int Width;
		int Height;
	};

	struct WindowClosedEvent : Vino::PublicEvent
	{

	};

}