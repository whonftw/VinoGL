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
		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnRender() override;
		void Begin();
		void End();
	private:
		float m_Time = 0.f;
		std::unique_ptr<Vino::EventAggregator<Vino::WindowSizeChangedEvent>::SubscriptionToken> m_SizeChangeToken;
	};
}