#include <iostream>

using namespace std;

class CEO {
public:
	string name;
	static int count_CEO;
	static CEO* getInstance()
	{
		if (count_CEO >= 1)	return NULL;
		CEO* newCEO = new CEO();
		count_CEO++;
		return newCEO;
	}
private:
	CEO() = default;
};

int CEO::count_CEO = 0;

int main()
{
	CEO* s1 = CEO::getInstance();
	CEO* s2 = CEO::getInstance();
	if (s2 == NULL)
	{
		cout << "Code Chuan" << endl;
	}
	return 0;
}