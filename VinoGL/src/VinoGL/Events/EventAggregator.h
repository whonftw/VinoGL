#pragma once
#include "VinoGL/Core.h"
#include <functional>
#include <vector>
#include <algorithm>
namespace Vino
{
	struct PublicEvent
	{
		bool Handled;
	};

	template<typename Derived, typename = typename std::enable_if<std::is_base_of<PublicEvent, Derived>::value>::type>
	class EventAggregator;
	
	template<typename T>
	class EventAggregator<T>
	{
	public:
		EventAggregator()
		{
			static_assert(std::is_base_of<PublicEvent, T>::value, "Class template argument not a subclass of PublicEvent");
		}

		static void Subscribe(std::function<void(T)>&& callback)
		{
			s_Callbacks.push_back(std::move(callback));
		}
		static void Subscribe(std::function<void(T)>& callback)
		{
			s_Callbacks.push_back(callback);
		}
		static void ClearSubscriptions()
		{
			s_Callbacks.clear();
		}

		static bool Publish(const T& args)
		{
			if (s_Callbacks.size())
			{
				for (auto& cb : s_Callbacks)
				{
					cb(args);
				}
				return true;
			}
			return false;
		}

	private:
		static std::vector < std::function<void(T)>> s_Callbacks;
	};
	template<typename T>
	std::vector<std::function<void(T)>> EventAggregator<T>::s_Callbacks;
}