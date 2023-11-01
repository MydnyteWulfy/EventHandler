#include <Core/Include.h>
#include <Premade/BasicInput.h>

class TestingClass
{
public:
	TestingClass() {}

	void BindEvents()
	{
		Eventer::EventDispatcher<Eventer::KeyboardEvent>* KeyDispatcher = Eventer::EventDispatcher<Eventer::KeyboardEvent>::GetInstance();
		KeyDispatcher->AddListener("W_KeyDown", [=](Eventer::KeyboardEvent* Evt) {this->TestEvent(Evt); } );
	}

	void TestEvent(Eventer::KeyboardEvent* Event)
	{
		std::cout << Event->GetName() << " Event has keycode: " << Event->GetKeyCode() << std::endl;
		Event->HandleEvent();
	}
};

int main()
{
	TestingClass TC;
	
	TC.BindEvents();
	
	Eventer::EventDispatcher<Eventer::KeyboardEvent>* KeyDispatcher = Eventer::EventDispatcher<Eventer::KeyboardEvent>::GetInstance();
	
	Eventer::KeyboardEvent KeyEvent("W_KeyDown", 87, Eventer::ButtonMode::Pressed);
	KeyDispatcher->PostEvent(&KeyEvent);

	if (KeyEvent.IsHandled())
	{
		std::cout << "Event Handled" << std::endl;
	}
}