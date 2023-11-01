#pragma once
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <functional>
#include "DllSupport.h"

//Error handling
#ifdef DEBUG
	#ifndef SYSTEM_USE_ERROR //Check for pre-existing error handling module.
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
		Event(std::string EventName)
			:m_EventName(EventName) {}
		
		virtual ~Event() = default;
		
		std::string GetName() { return m_EventName; }

		virtual T* operator()()
		{
			return static_cast<T*>(this);
		}
		
		virtual T* As()
		{
			return static_cast<T*>(this);
		}
		
		virtual bool IsHandled() { return m_IsHandled; }
		virtual void HandleEvent() = 0;
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
#define EVENTER_USE_FUNCTIONAL
#ifdef EVENTER_USE_FUNCTIONAL
	template<typename T>
	using EventCallback = std::function<void(T*)>;
#else
	
#endif
	
	//EventDispatcher class. This class is used to dispatch events of a specific type to listeners.
	template<typename T>
	class EventDispatcher
	{
	
	private:
		EventDispatcher() {}
		virtual ~EventDispatcher() = default;
		
	public:
		static EventDispatcher<T>* GetInstance()
		{
			if (m_Instance == nullptr)
			{
				m_Instance = new EventDispatcher<T>();
			}
			return m_Instance;
		}
		
		static void DeleteInstance()
		{
			if (!m_Instance)
			{
				return;
			}
			else
			{
				m_Instance->~EventDispatcher();
			}
		}

		void PostEvent(Event<T>* Evt)
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

		void AddListener(std::string EventName, std::function<void(T*)> Callback)
		{
			if (m_Listeners.find(EventName) != m_Listeners.end())
			{
				WARN("Listener already exists for event: " << EventName);
				return;
			}

			m_Listeners[EventName] = Callback;
		}
		void RemoveListener(std::string EventName, std::function<void(T*)> Callback)
		{
			if (m_Listeners.find(EventName) == m_Listeners.end())
			{
				WARN("Listener does not exist for event: " << EventName);
				return;
			}

			m_Listeners.erase(EventName);
		}
		
		void ChangeQueueType(QueueType NewQueueType)
		{
			if (m_QueueType == NewQueueType)
			{
				WARN("QueueType specified is already in use");
				return;
			}
			
			m_QueueType = NewQueueType;
		}
		
		void Update()
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
					Iter->second(Evt->As());
				}
				else if (Evt->IsHandled())
				{
					WARN("Event already handled. Skipping remaining listeners.");
					break;
				}
				else
				{
					ERROR("Unhandled exception occurred while dispatching event: " + Evt->GetName());
				}
			}
		}
		
	private:
		std::map<std::string /*EventName*/, std::function<void(T*)> /*Callback*/> m_Listeners;
		
		std::vector<Event<T>*> m_EventQueue;
		QueueType m_QueueType = QueueType::NONE;

		static inline EventDispatcher<T>* m_Instance = nullptr;
	};
}