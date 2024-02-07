#include <iostream>
using namespace std;

// Bai 1
struct Book {
	char name[255];
	int year;
	double price;
};

Book find_by_year(Book mang[], int size, int year, bool &pos) {
	int left = 0;
	int right = size - 1;
	int mid = (left + right) / 2;
	while (right >= left)
	{
		if (mang[mid].year > year) { right = mid - 1; }
		else if (mang[mid].year < year) { left = mid + 1; }
		else { pos = true;	 return mang[mid]; }
	}
	pos = false;
	return mang[0];
}

void print_name(Book mang[], int size, double price_below, double price_above)
{
	for (int i = 0; i < size; i++)
	{
		if (mang[i].price >= price_below && mang[i].price <= price_above)	cout << mang[i].name << endl;
	}
}


// Bai 2
// a
struct Node
{
	int value;
	Node* prev;
	Node* next;

};

void InsertHead(Node*& head, int k)
{
	Node* add = new Node;
	add->value = k;
	add->next  = head;
	head = add;
}
// b
Node* findK(Node* current, int k)
{
	// TH no la k va truoc no la null hoac khong
	if (current->value == k)
	{
		if (current->prev == NULL)	return NULL;
		return current->prev;
	}

	// TH no nam o vi tri nao do khac
	while (current->value != k and current->next != NULL)
	{
		current = current->next;
	}
	if (current->value == k) return current->prev;
	return NULL;
}

// Xoa node = k
// c
bool deleteNodeK(Node*& head, int k)
{
	if (head == NULL)	return 0;
	if (head->value == k)
	{
		if (head->next == NULL) {
			head = nullptr;
			return 1;
		}
		head = head->next;
		head->prev = nullptr;
		return 1;
	}
	Node* tmp = head;
	while (tmp->next != NULL && tmp->next->value != k)
	{
		tmp = tmp->next;
	}
	if (tmp->next == NULL)	return 0;
	Node* found = tmp->next;
	tmp->next = found->next;
	found->next->prev = tmp;
	delete found;
	return 1;
}

void deleteAllK(Node*& head, int k)
{
	while (deleteNodeK(head, k));
}


// d
Node* merge(Node*& head1, Node*& head2)
{
	if (head1 == NULL and head2 == NULL)	return NULL;
	else if (head1 != NULL and head2 == NULL)	return head1;
	else if (head1 == NULL and head2 != NULL)	return head2;

	Node* tmp1 = head1;
	Node* tmp2 = head2;
	if (tmp1->value < tmp2->value)
	{
		Node* temper = merge(tmp1->next, tmp2);
		tmp1->next = temper;
		temper->prev = tmp1;
		return tmp1;
	}
	else {
		Node* temper = merge(tmp1, tmp2->next);
		tmp2->next = temper;
		temper->prev = tmp2;
		return tmp2;
	}
}


// Bai 3

class Observer {
public:
	virtual void update() = 0;
};

class Frame : public Observer {
public:
	void update() {
	}
};

class Window : public Observer {
public:
	void update(){
	}
};

class Button {
public:
	Observer* addObservers(Observer* obs) {
		counter += 1;
	}
	Observer* removeObservers(Observer* obs) {
		(counter > 0) ? counter -= 1 : counter = 0;
	}
	Observer* notify(Observer* list) {
		for (int i = 0; i < counter; i++)
		{
			list[i].update();
		}
	}

private:
	int counter = 0;
	Observer** observers;
};

int main_cho_cau3()
{
	Window* new_window = new Window();
	Frame* new_frame = new Frame();
	Button* new_button = new Button();
	new_button->addObservers(new_window);
	new_button->addObservers(new_frame);
}


int main()
{
	// Day 1//
	Node* node1_1 = new Node;	node1_1->prev = NULL;		node1_1->value = 1;	
	Node* node1_2 = new Node;	node1_2->prev = node1_1;	node1_2->value = 3;
	Node* node1_3 = new Node;	node1_3->prev = node1_2;	node1_3->value = 5;
	node1_1->next = node1_2;	node1_2->next = node1_3;	node1_3->next = NULL;

	// Day 2//
	Node* node2_1 = new Node;	node2_1->prev = NULL;		node2_1->value = 2;
	Node* node2_2 = new Node;	node2_2->prev = node2_1;	node2_2->value = 4;
	Node* node2_3 = new Node;	node2_3->prev = node2_2;	node2_3->value = 6;
	node2_1->next = node2_2;	node2_2->next = node2_3;	node2_3->next = NULL;
	
	Node* merging = merge(node1_1, node2_1);

	while (merging != NULL)
	{
		cout << merging->value << endl;
		merging = merging->next;
	}
}