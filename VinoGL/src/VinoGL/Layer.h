#pragma once
#include "Core.h"

namespace Vino {
	class VINO_API Layer
	{
	public:
		Layer(const char* name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}

		inline const char* GetName() const { return m_Name; }
	protected:
		const char* m_Name;
	};
}

