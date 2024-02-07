#include <iostream>
#include <string>

using namespace std;

class Device {
public:
	string name;
	string id;
	string room;
	bool status;

	virtual void TurnOn() = 0;
	virtual void TurnOff() = 0;
};

class Den : public Device {
public:
	int dosang;
	virtual void changeLight(int number) = 0;
};

class Light : public Den {
public:
	Light(string name1, string id1, string room1, int dosang1 = 50)
	{
		name = name1;
		id = id1;
		room = room1;
		dosang = dosang1;
		status = 0;
	}
	void TurnOn() { status = 1; }
	void TurnOff() { status = 0; }
	void changeLight(int number) { dosang = number; }
};

class Lamp : public Den {
public:
	int mau;

	Lamp(string name2, string id2, string room2, int dosang2 = 50, int mau2 = 0)
	{
		name = name2;
		id = id2;
		room = room2;
		dosang = dosang2;
		mau = mau2;
		status = 0;
	}

	void changeLight(int number) { dosang = number; }
	void TurnOn() { status = 1; }
	void TurnOff() { status = 0; }

	void setMau(int color)
	{
		mau = color;
	}
};

class DHND : public Device {
public:
	int nhietdo;
	int chedo;
	int level;

	DHND(string name2, string id2, string room2,int temp1 = 28, int chedo1 = 0, int mdq1 = 1)
	{
		name = name2;
		id = id2;
		room = room2;
		nhietdo = temp1;
		chedo = chedo1;
		level = mdq1;
	}

	void TurnOn() { status = 1; }
	void TurnOff() { status = 0; }
	void ChangeTemp(int temp1) { nhietdo = temp1; }
	void ChangeMode(int mode) { chedo = mode; }
	void ChangeLevel(int level1) { level = level1; }
};

class TV : public Device {
public:
	int amluong;
	int channel;

	TV(string name1, string id1, string room1, int volume = 50, int kenh = 1)
	{
		name = name1;
		id = id1;
		room = room1;
		amluong = volume;
		channel = kenh;
	}

	void TurnOn() { status = 1; }
	void TurnOff() { status = 0; }
	void ChangeChannel(int kenh) { channel = kenh; }
	void ChangeVolume(int volume) { amluong = volume; }
};

int main_oop_basic()
{
	Device* list[2];
	Light* newlight = new Light("den ngu 1", "dn1", "living room", 24);
	DHND* dieuhoa = new DHND("dieu hoa 1", "dh1", "bedroom", 24);
	list[0] = newlight;
	list[1] = dieuhoa;

	for (int i = 0; i < 2; i++)
	{
		list[i]->TurnOn();
	}
	return 0;
}

