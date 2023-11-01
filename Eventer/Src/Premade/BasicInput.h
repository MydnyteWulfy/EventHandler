#pragma once
#include "../Core/EventSystem.h"

namespace Eventer
{
	enum class ButtonMode
	{
		Pressed,
		Released,
		Held,
		UNDEFINED
	};
	
	//Key Events
	class __Reference KeyboardEvent : public Event<KeyboardEvent> // generic keyboard events. Keypresses and releases
	{
	public:
		KeyboardEvent(std::string EventName)
			:Event(EventName) {}

		KeyboardEvent(std::string EventName, uint8_t KeyCode, ButtonMode Mode)
			:Event(EventName), m_KeyCode(KeyCode), m_ButtonMode(Mode) {}

		void HandleEvent() override;
		
		uint8_t GetKeyCode() { return m_KeyCode; }
		ButtonMode GetButtonMode() { return m_ButtonMode; }
		
		void SetKeyCode(uint8_t KeyCode);
		void SetButtonMode(ButtonMode Mode);
		
	private:
		uint8_t m_KeyCode = 0;
		ButtonMode m_ButtonMode = ButtonMode::UNDEFINED;
	};

	//Mouse Events
	class __Reference MouseButtonEvent : public Event<MouseButtonEvent> // Generic mouse presses and releases. 
	{
	public:
		MouseButtonEvent(std::string EventName)
			:Event(EventName) {}
		
		MouseButtonEvent(std::string EventName, uint8_t Button, ButtonMode Mode)
			:Event(EventName), m_Button(Button), m_ButtonMode(Mode) {}

		void HandleEvent() override;
		
		uint8_t GetButton() { return m_Button; }
		ButtonMode GetButtonMode() { return m_ButtonMode; }

		void SetButton(uint8_t Button);
		void SetButtonMode(ButtonMode Type);
		
	private:
		uint8_t m_Button = 0;
		ButtonMode m_ButtonMode = ButtonMode::UNDEFINED;
	};
	
	class __Reference MouseScrollEvent : public Event<MouseScrollEvent> // Generic mouse scroll event. 
	{
	public:
		MouseScrollEvent(std::string EventName)
			:Event(EventName) {}

		MouseScrollEvent(std::string EventName, short ScrollDirection)
			:Event(EventName), m_ScrollDirection(ScrollDirection) {}

		void HandleEvent() override;

		short GetScrollDirection() { return m_ScrollDirection; }
		
		void SetScrollDirection(short ScrollDirection);
		
	private:
		short m_ScrollDirection = 0;
	};
	
	enum class MousePositionDataMode
	{
		Absolute, //gives mouse data as an exact location on the screen (useful for seen cursor)
		Relative, // gives mouse data as a vector relative to the previous position. (useful for hidden cursor) 
		UNDEFINED
	};
	
	class __Reference MouseMoveEvent : public Event<MouseMoveEvent> // Generic mouse move event. Uses specified operation mode
	{
	public:
		MouseMoveEvent(std::string EventName)
			:Event(EventName) {}
		
		MouseMoveEvent(std::string EventName, float Position[2])
			:Event(EventName), m_Position{ Position[0], Position[1] } {}

		void HandleEvent() override;
		
		float* GetPosition() { return m_Position; }
		
		void SetPosition(float Position[2]) { m_Position[0] = Position[0]; m_Position[1] = Position[1]; }
		
		static void SetOperationMode(MousePositionDataMode Mode);
		
	private:
		static inline MousePositionDataMode m_OperationMode = MousePositionDataMode::UNDEFINED;
		float m_Position[2] = {};
	};
}
