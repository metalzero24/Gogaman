#pragma once

#include "Event.h"

namespace Gogaman
{
	class EventDispatcher
	{
	public:
		EventDispatcher(Event &event)
			: m_Event(event)
		{}

		template<typename EventType>
		bool Dispatch(std::function<bool(EventType &)> callback)
		{
			if(m_Event.GetType() == EventType::GetTypeStatic())
			{
				m_Event.handled = callback(*(EventType *)&m_Event);
				return true;
			}

			return false;
		}
	private:
		Event &m_Event;
	};
}