#pragma once
#include <iostream>
#include "DllSupport.h"

namespace Eventer
{
	
	
	template<class T>
	class __Reference Event
	{
	public:
		Event() {}
		virtual ~Event() = default;
		
		virtual T* operator()()
		{
			return static_cast<T*>(this);
		}
		
		virtual bool IsHandled() { return m_IsHandled; }
		
	protected:
		bool m_IsHandled = false;
	};
	
	
}