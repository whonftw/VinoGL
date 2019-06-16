#pragma once
#include "VinoGL/Core.h"
#include "VinoGL/Layer.h"
#include "VinoGL/Events/EventAggregator.h"
#include "VinoGL/Events/WindowEvents.h"
namespace Vino {

	class VINO_API ImGuiLayer : public Vino::Layer
	{
	public:
		ImGuiLayer();
		virtual ~ImGuiLayer();
		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnMouseButtonPressed(Vino::MouseButtonPressedEvent&);
		void OnMouseButtonReleased(Vino::MouseButtonReleasedEvent&);
		void OnMousePositionChanged(Vino::MousePositionChangedEvent&);
		void OnMouseScrolled(Vino::MouseScrolledEvent&);
		void OnKeyPressed(Vino::KeyPressedEvent&);
		void OnKeyReleased(Vino::KeyReleasedEvent&);
		void OnKeyTyped(Vino::KeyTypedEvent&);
	private:
		float m_Time = 0.f;
		std::unique_ptr<Vino::EventAggregator<Vino::WindowSizeChangedEvent>::SubscriptionToken> m_SizeChangeToken;
	};
}