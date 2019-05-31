#pragma once
#include "VinoGL/Core.h"
#include <functional>
#include <vector>
#include <algorithm>

namespace Vino
{
	struct PublicEvent
	{
		PublicEvent() {}
		virtual ~PublicEvent(){}
	};

	template<typename Derived, typename = typename std::enable_if<std::is_base_of<PublicEvent, Derived>::value>::type>
	class EventAggregator;
	
	template<typename T>
	class EventAggregator<T>
	{
		EventAggregator() = delete;
	public:
		struct SubscriptionToken
		{
		private:
			unsigned int id;
		public:
			SubscriptionToken(unsigned int id)
			{
				SubscriptionToken::id = id;
			}
			~SubscriptionToken()
			{
				s_RegisteredCallbacks.erase(SubscriptionToken::id);
			}
		};

		[[nodiscard]] static std::unique_ptr<SubscriptionToken> Subscribe(std::function<void(T)>&& callback) noexcept
		{
			s_RegisteredCallbacks[s_CallbacksCounter] = std::move(callback);
			return std::unique_ptr<SubscriptionToken>(new SubscriptionToken(s_CallbacksCounter++));
		}

		static bool Publish(const T& args) noexcept
		{
			if (s_RegisteredCallbacks.size())
			{
				for (auto& cb : s_RegisteredCallbacks)
				{
					cb.second(args);
				}
				return true;
			}
			return false;
		}

	private:
		static unsigned int s_CallbacksCounter;
		static std::unordered_map<unsigned int, std::function<void(T)>> s_RegisteredCallbacks;
	};

	template<typename T>
	std::unordered_map<unsigned int, std::function<void(T)>> EventAggregator<T>::s_RegisteredCallbacks;
	template<typename T>
	unsigned int EventAggregator<T>::s_CallbacksCounter;
}
