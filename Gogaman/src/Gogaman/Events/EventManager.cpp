#include "pch.h"
#include "EventManager.h"

#include "Gogaman/Logging/Log.h"
#include "Event.h"
#include "EventListener.h"

namespace Gogaman
{
	EventManager *EventManager::s_Instance = new EventManager();

	EventManager::EventManager()
	{
		GM_ASSERT(s_Instance == nullptr, "Failed to construct event queue: instance already exists");
	}

	EventManager::~EventManager()
	{}
	
	void EventManager::DispatchEvents()
	{
		while(!m_Events.empty())
		{
			for(auto listener : m_Listeners)
			{
				listener->OnEvent(*m_Events.front().get());
			}

			m_Events.pop();
		}
	}
}