#pragma once
#include "VinoGL/Core.h"
#include "VinoGL/Layer.h"
namespace Vino {

	class VINO_API ImGuiLayer : public Vino::Layer
	{
	public:
		ImGuiLayer();
		virtual ~ImGuiLayer();
		void OnAttach();
		void OnDetach();
		void OnUpdate();
	private:
		float m_Time = 0.f;
	};
}