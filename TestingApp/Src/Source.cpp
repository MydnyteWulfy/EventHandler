#include <Include.h>

class KeyEvent : public Eventer::Event<KeyEvent>
{
public:
	KeyEvent(std::string EventName)
		:Event(EventName) {}

	void Print() { std::cout << "Key Event Triggered!" << std::endl; }
};

void TestCallback(KeyEvent* K)
{
	K->Print();
}

int main()
{
	Eventer::EventDispatcher<KeyEvent> Dispatcher;
	
	Dispatcher.AddListener("Test", TestCallback);
	
}