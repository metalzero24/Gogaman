#pragma once

#include "Gogaman/Core.h"
#include "Event.h"

namespace Gogaman
{
	class GOGAMAN_API WindowEvent : public Event
	{
	public:
		inline virtual EventCategory GetCategory() const override { return EventCategory::Window; }
	protected:
		WindowEvent()
		{}
	};

	class GOGAMAN_API WindowCloseEvent : public WindowEvent
	{
	public:
		WindowCloseEvent()
		{}

		inline static  EventType GetEventType() { return WindowClose; }
		inline virtual EventType GetType() const override { return GetEventType(); }
	};

	class GOGAMAN_API WindowResizeEvent : public WindowEvent
	{
	public:
		WindowResizeEvent(const int width, const int height)
			: m_Width(width), m_Height(height)
		{}

		inline static  EventType GetEventType() { return WindowResize; }
		inline virtual EventType GetType() const override { return GetEventType(); }

		inline int GetWidth()  const { return m_Width; }
		inline int GetHeight() const { return m_Height; }
	private:
		int m_Width, m_Height;
	};

	class GOGAMAN_API WindowFocusEvent : public WindowEvent
	{
	public:
		WindowFocusEvent()
		{}

		inline static  EventType GetEventType() { return WindowFocus; }
		inline virtual EventType GetType() const override { return GetEventType(); }
	};

	class GOGAMAN_API WindowUnfocusEvent : public WindowEvent
	{
	public:
		WindowUnfocusEvent()
		{}

		inline static  EventType GetEventType() { return WindowUnfocus; }
		inline virtual EventType GetType() const override { return GetEventType(); }
	};
}