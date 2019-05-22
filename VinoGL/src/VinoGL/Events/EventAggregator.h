#pragma once
#include "VinoGL/Core.h"
#include <functional>
#include <vector>
#include <algorithm>
namespace Vino
{
	template<typename T>
	class EventAggregator
	{
	public:
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