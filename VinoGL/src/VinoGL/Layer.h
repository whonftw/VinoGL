#pragma once
#include "Core.h"
#include "Events/InputEvents.h"

namespace Vino {
	class VINO_API Layer
	{
	public:
		Layer(const char* name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnMouseButtonPressed(Vino::MouseButtonPressedEvent&) { }
		virtual void OnMouseButtonReleased(Vino::MouseButtonReleasedEvent&) { }
		virtual void OnMousePositionChanged(Vino::MousePositionChangedEvent&) { }
		virtual void OnMouseScrolled(Vino::MouseScrolledEvent&) { }
		virtual void OnKeyPressed(Vino::KeyPressedEvent&) { }
		virtual void OnKeyReleased(Vino::KeyReleasedEvent&) { }
		virtual void OnKeyTyped(Vino::KeyTypedEvent&) {}
		inline const char* GetName() const { return m_Name; }
	protected:
		const char* m_Name;
	};
}

