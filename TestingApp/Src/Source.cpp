#include <Core/Include.h>
#include <Premade/BasicInput.h>

class TestingClass
{
public:
	TestingClass() {}

	void BindEvents()
	{
		Eventer::EventDispatcher<Eventer::KeyboardEvent>* KeyDispatcher = Eventer::EventDispatcher<Eventer::KeyboardEvent>::GetInstance();
		void(TestingClass::* FN)(Eventer::KeyboardEvent*) = &TestingClass::TestEvent;
		KeyDispatcher->AddListener("W_KeyDown", MakeFunction(FN, this));
	}

	void TestEvent(Eventer::KeyboardEvent* Event)
	{
		std::cout << Event->GetName() << " Event has keycode: " << Event->GetKeyCode() << ". And checking class with: " << code << std::endl;
		Event->HandleEvent();
	}
	int code = 0;
};

int main()
{
	TestingClass TC;
	
	TC.BindEvents();
	
	TC.code = 1;
	Eventer::EventDispatcher<Eventer::KeyboardEvent>* KeyDispatcher = Eventer::EventDispatcher<Eventer::KeyboardEvent>::GetInstance();
	
	Eventer::KeyboardEvent KeyEvent("W_KeyDown", 87, Eventer::ButtonMode::Pressed);
	KeyDispatcher->PostEvent(&KeyEvent);

	if (KeyEvent.IsHandled())
	{
		std::cout << "Event Handled" << std::endl;
	}
}