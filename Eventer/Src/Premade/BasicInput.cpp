#include "BasicInput.h"

void Eventer::KeyboardEvent::HandleEvent()
{
	if (m_ButtonMode != ButtonMode::UNDEFINED)
	{
		m_IsHandled = true;
	}
	else
	{
		ERROR("Attempted to handle event before any specifiers have been set.");
	}
}

void Eventer::KeyboardEvent::SetKeyCode(uint8_t KeyCode)
{
	if (m_KeyCode != 0)
	{
		WARN("Keycode already defined for given event. failed to overwrite pre existing keycode");
		return;
	}
	else
	{
		m_KeyCode = KeyCode;
	}
}

void Eventer::KeyboardEvent::SetButtonMode(ButtonMode Mode)
{
	if (m_ButtonMode != ButtonMode::UNDEFINED)
	{
		WARN("Button mode already defined for given event. failed to overwrite pre existing mode");
	}
}

void Eventer::MouseButtonEvent::HandleEvent()
{
	if (m_ButtonMode != ButtonMode::UNDEFINED)
	{
		m_IsHandled = true;
	}
	else
	{
		ERROR("Attempted to handle event before any specifiers have been set.");
	}
}

void Eventer::MouseButtonEvent::SetButton(uint8_t Button)
{
	if (m_Button != 0)
	{
		WARN("Button already defined for given event. failed to overwrite pre existing button");
	}
	else
	{
		m_Button = Button;
	}
}

void Eventer::MouseButtonEvent::SetButtonMode(ButtonMode Type)
{
	if (m_ButtonMode != ButtonMode::UNDEFINED)
	{
		WARN("Button mode already defined for given event. failed to overwrite pre existing button mode");
	}
	else
	{
		m_ButtonMode = Type;
	}
}

void Eventer::MouseScrollEvent::HandleEvent()
{
	if (m_ScrollDirection != 0)
	{
		m_IsHandled = true;
	}
	else
	{
		ERROR("Attempted to handle event before any specifiers have been set");
	}
}

void Eventer::MouseScrollEvent::SetScrollDirection(short ScrollDirection)
{
	if (m_ScrollDirection != 0)
	{
		WARN("Scroll direction already defined for given event. failed to overwrite pre existing scroll direction");
	}
}

void Eventer::MouseMoveEvent::HandleEvent()
{
	if (m_OperationMode != MousePositionDataMode::UNDEFINED)
	{
		m_IsHandled = true;
	}
	else
	{
		ERROR("Attempted to handle event before any specifiers have been set");
	}
}

void Eventer::MouseMoveEvent::SetOperationMode(MousePositionDataMode Mode)
{
	if (Mode == MousePositionDataMode::UNDEFINED)
	{
		ERROR("Positional data must be sent as either 'absolute' or 'relative'.");
		return;
	}
	else
	{
		if (m_OperationMode == Mode)
		{
			WARN("Positional data already being sent via specified mode");
		}
		else
		{
			m_OperationMode = Mode;
		}
	}
}
