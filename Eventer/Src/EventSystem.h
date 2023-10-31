#pragma once
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <map>
#include <vector>
#include <functional>
#include "DllSupport.h"

#ifdef DEBUG
	#ifndef SYSTEM_USE_ERROR
		#define WARN(x) std::cout << x << std::endl;
		#define ERROR(x) throw(std::runtime_error(x));
	#endif
#else
	#define WARN(x)
	#define ERROR(x)
#endif

namespace Eventer
{
	
	//basic event class. All events should inherit from this class. EX: 'class MyEvent : public Event<MyEvent>'
	
	template<class T>
	class Event
	{
	public:
		__Reference Event(std::string EventName)
			:m_EventName(EventName) {}
		
		__Reference virtual ~Event() = default;
		
		__Reference std::string GetName() { return m_EventName; }

		__Reference virtual T* operator()()
		{
			return static_cast<T*>(this);
		}
		
		__Reference virtual operator T* ()
		{
			return static_cast<T*>(this);
		}
		
		__Reference virtual bool IsHandled() { return m_IsHandled; }
		
	protected:
		bool m_IsHandled = false;
		std::string m_EventName = "";
	};

	
	enum class QueueType
	{
		NONE = 0, // No queue, halt and dispatch events immediately upon calling PostEvent(). 
		SINGLE = 1, //Queue events and dispatch a single event per call to Update().
		ALL = 2 //Queue events and dispatch all queued events per call to Update(). 
	};
	
	//EventDispatcher class. This class is used to dispatch events of a specific type to listeners.
	template<typename T>
	class EventDispatcher
	{
	public:
		__Reference EventDispatcher() {}
		__Reference virtual ~EventDispatcher() = default;

		__Reference void PostEvent(Event<T>* Evt)
		{
			switch (m_QueueType)
			{
			case Eventer::QueueType::NONE:
				DispatchEvent(Evt);
				break;
			case Eventer::QueueType::SINGLE:
				m_EventQueue.push_back(Evt);
				break;
			case Eventer::QueueType::ALL:
				m_EventQueue.push_back(Evt);
				break;
			default:
				WARN("Invalid QueueType specified for EventDispatcher. Defaulting to NONE.");
				DispatchEvent(Evt);
				break;
			}
		}

		__Reference void AddListener(std::string EventName, std::function<void(T*)> Callback)
		{
			if (m_Listeners.find(EventName) != m_Listeners.end())
			{
				WARN("Listener already exists for event: " << EventName);
				return;
			}

			m_Listeners[EventName] = Callback;
		}
		__Reference void RemoveListener(std::string EventName, std::function<void(T*)> Callback)
		{
			if (m_Listeners.find(EventName) == m_Listeners.end())
			{
				WARN("Listener does not exist for event: " << EventName);
				return;
			}

			m_Listeners.erase(EventName);
		}
		
		__Reference void ChangeQueueType(QueueType NewQueueType)
		{
			if (m_QueueType == NewQueueType)
			{
				WARN("QueueType specified is already in use");
				return;
			}
			
			m_QueueType = NewQueueType;
		}
		
		__Reference void Update()
		{
			switch (m_QueueType)
			{
			case Eventer::QueueType::NONE:
				WARN("Update() called with QueueType of NONE. No events to dispatch.");
				break;
			case Eventer::QueueType::SINGLE:
				if (m_EventQueue.size() > 0)
				{
					DispatchEvent(m_EventQueue[0]);
					m_EventQueue.erase(m_EventQueue.front());
				}
				break;
			case Eventer::QueueType::ALL:
				while (m_EventQueue.size() > 0)
				{
					DispatchEvent(m_EventQueue[0]);
					m_EventQueue.erase(m_EventQueue.front());
				}
				break;
			default:
				WARN("Update called with invalid QueueType specified. No event dispatching will occur.");
				break;
			}
		}
	protected:
		void DispatchEvent(Event<T>* Evt)
		{
			if (m_Listeners.find(Evt->GetName()) == m_Listeners.end())
			{
				WARN("No listeners found for event: " << Evt->GetName());
				return;
			}

			auto IterPair = m_Listeners.equal_range(Evt->GetName());
			for (auto Iter = IterPair.first; Iter != IterPair.second; ++Iter)
			{
				if (!Evt->IsHandled())
				{
					Iter->second(Evt());
				}
				else if (Evt->IsHandled())
				{
					WARN("Event already handled. Skipping remaining listeners.");
					break;
				}
				else
				{
					ERROR("Unhandled exception occurred while dispatching event: " << Evt->Name);
				}
			}
		}
		
	private:
		std::map<std::string /*EventName*/, std::function<void(T*)> /*Callback*/> m_Listeners;
		
		std::vector<Event<T>*> m_EventQueue;
		QueueType m_QueueType;
	};
}