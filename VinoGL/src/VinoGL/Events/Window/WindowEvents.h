#pragma once
#include "VinoGL/Events/EventAggregator.h"
struct WindowSizeChanged: Vino::PublicEvent
{
	int Width;
	int Height;
};

struct WindowClosed: Vino::PublicEvent
{

};