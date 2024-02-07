#include <iostream>
#define MAX 1000
using namespace std;

class Observer {
public:
	virtual void update() = 0;
};

class Frame : public Observer {
public:
	void update() {
		cout << "Frame update" << endl;
	}
};

class Window : public Observer {
public:
	void update() {
		cout << "Window update" << endl;
	}
};

class Button {
private:
	Observer** list_observer;
	int size;
public:
	Button()
	{
		list_observer = new Observer * [MAX];
		size = 0;
	}
	void addObserver(Observer* observer_object)
	{
		cout << "Add new object" << endl;
		list_observer[size] = observer_object;
		size += 1;
	}

	void removeObserver(Observer* observer_object)
	{
		cout << "Remove an object" << endl;
		if (size > 0)	size -= 1;
	}

	void notify()
	{
		cout << "Found notification" << endl;

		for (int i = 0; i < size; i++)
		{
			list_observer[i]->update();
		}
		cout << "----------------------" << endl;
	}

	int getSize()
	{
		return size;
	}
};

int main()
{
	Button* newButton = new Button();
	Frame* newFrame = new Frame();
	Window* newWindow = new Window();
	newButton->addObserver(newFrame);
	newButton->addObserver(newWindow);
	newButton->notify();
	return 0;
}