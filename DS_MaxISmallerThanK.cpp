#include <iostream>
#define MAX 100000
#define MIN -100000
using namespace std;

struct Node
{
	int key;
	Node* left;
	Node* right;

	Node(int k, Node* pLeft, Node* pRight)
	{
		key = k;
		left = pLeft;
		right = pRight;
	}
};


bool search(Node*& root, int k)
{
	if (root == NULL)	return 0;
	Node* temp = root;
	while (temp != NULL)
	{
		if (temp->key == k)
		{
			delete temp;
			return 1;
		}
		if (temp->key > k)	temp = temp->left;
		if (temp->key < k)  temp = temp->right;
	}
	delete temp;
	return 0;
}

void printLeaf(Node*& root)
{
	if (root == NULL)	return;
	printLeaf(root->right);
	printLeaf(root->left);
	if (root->left == NULL && root->right == NULL)	cout << root->key << endl;
}

bool checkBST(Node*& root, int lowmin, int upmax)
{
	if (root == NULL)	return 1;
	if (root->key >= upmax || root->key <= lowmin)	return 0;
	else
	{
		return checkBST(root->left, lowmin, root->key) && checkBST(root->right, root->key, upmax);
	}
	return 0;
}

Node* findMax(Node*& root)
{
	if (root == NULL)	return NULL;
	Node* temp = root;
	while (temp->right != NULL)	temp = temp->right;
	return temp;
}

void FindMaxSmaller(Node*& root, int k, Node*& res)
{
	if (root == NULL)	return;
	cout << root->key << endl;
	if (root->key < k)
	{
		res = root;
		if (root->right == NULL)	return;
		if (root->right->key == k)
		{
			Node* temp = findMax(root->right->left);
			if (temp != NULL)	res = temp;
			return;
		}
		FindMaxSmaller(root->right, k, res);
		return;
	}
	
	if (root->key > k)
	{
		if (root->left == NULL)	return;
		if (root->left->key == k)
		{	
			Node* temp = findMax(root->left->left);
			if (temp != NULL)	res = temp;
			return;
		}
		FindMaxSmaller(root->left, k, res);
		return;
	}

	if (root->key == k)
	{
		res = findMax(root->left);
		return;
	}
	return;
}
int main()
{
	Node* node55 = new Node(55, NULL, NULL);
	Node* node70 = new Node(70, NULL, NULL);
	Node* node103 = new Node(103, NULL, NULL);
	Node* node113 = new Node(113, NULL, NULL);
	Node* node180 = new Node(180, NULL, NULL);

	Node* node10 = new Node(10, NULL, NULL);
	Node* node40 = new Node(40, NULL, NULL);
	Node* node65 = new Node(65, node55, node70);
	Node* node85 = new Node(85, NULL, NULL);
	Node* node105 = new Node(105, node103, NULL);
	Node* node115 = new Node(115, node113, NULL);
	Node* node130 = new Node(130, NULL, NULL);
	Node* node160 = new Node(160, NULL, node180);

	Node* node30 = new Node(30, node10, node40);
	Node* node80 = new Node(80, node65, node85);
	Node* node110 = new Node(110, node105, node115);
	Node* node140 = new Node(140, node130, node160);

	Node* node50 = new Node(50, node30, node80);
	Node* node120 = new Node(120, node110, node140);

	Node* node100 = new Node(100, node50, node120);

	Node* res = new Node(0, NULL, NULL);
	FindMaxSmaller(node100, 86, res);
	
	cout << res->key << endl;

	return 0;
}