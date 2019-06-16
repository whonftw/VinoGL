#pragma once
#include "EventAggregator.h"
#include "VinoGL/Core.h"

namespace Vino
{
	struct VINO_API InputEvent : public Vino::PublicEvent
	{
	protected:
		InputEvent(bool handled = false) : Handled(handled) {}
	public:
		bool Handled;
	};

	struct VINO_API KeyPressedEvent : Vino::InputEvent
	{
		KeyPressedEvent(int key, bool repeat) : Key(key), Repeat(repeat) {}

		int Key;
		bool Repeat;
	};

	struct VINO_API KeyReleasedEvent : Vino::InputEvent
	{
		KeyReleasedEvent(int key) : Key(key) {}

		int Key;
	};

	struct VINO_API MouseButtonPressedEvent : public Vino::InputEvent
	{
		MouseButtonPressedEvent(int button) : Button(button) {}

		int Button;
	};

	struct VINO_API MouseButtonReleasedEvent : public Vino::InputEvent
	{
		MouseButtonReleasedEvent(int button) : Button(button) {}

		int Button;
	};

	struct VINO_API MouseScrolledEvent : public Vino::InputEvent
	{
		MouseScrolledEvent(double xoffset, double yoffset) : xOffset(xoffset), yOffset(yoffset) {}

		double xOffset;
		double yOffset;
	};

	struct VINO_API MousePositionChangedEvent : public Vino::InputEvent
	{
		MousePositionChangedEvent(double xpos, double ypos) : xPos(xpos), yPos(ypos) {}

		double xPos;
		double yPos;
	};

	struct VINO_API KeyTypedEvent : public Vino::InputEvent
	{
		KeyTypedEvent(unsigned int key) : Key(key) {}
		unsigned int Key;
	};
}