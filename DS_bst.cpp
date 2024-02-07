#include <iostream>

using namespace std;

struct Node {
	int value;
	Node* left;
	Node* right;

	Node(int k)
	{
		value = k;
		left = NULL;
		right = NULL;
	}
};

Node* insert(Node*& root, int k)
{
	if (root == NULL) {
		root = new Node(k);
		return root;
	}

	Node* current = root;

	if (current->value > k)
	{
		if (current->left == NULL) {
			current->left = new Node(k);
			return current;
		}
		return insert(current->left, k);
	}
	else if (current->value < k)
	{
		if (current->right == NULL) {
			current->right = new Node(k);
			return current;
		}
		return insert(current->right, k);
	}
	else {
		cout << "Trung phan tu " << endl;
		return root;
	}
}

bool search(Node*& root, int k, Node*& reference)
{
	if (root == NULL)	return 0;

	Node* current = root;
	if (current->value == k) {
		reference = current;
		return 1;
	}
	else if (current->value > k) {
		return search(current->left, k, reference);
	}
	else return search(current->right, k, reference);
}

Node* FindMax(Node*& root)
{
	if (root == NULL) return NULL;
	Node* current = root;
	while (current->right != NULL)	current = current->right;
	return current;
}

Node* FindMin(Node*& root)
{
	if (root == NULL)	return NULL;
	Node* current = root;
	while (current->left != NULL)	current = current->left;
	return current;
}

Node* Delete(Node*& root, int k)
{
	if (root == NULL)	return root;
	Node* current = root;
	if (current->value > k) { 
		cout << "Truong hop k nho hon node" << endl;
		return Delete(current->left, k); }
	else if (current->value < k) {
		cout << "Truong hop k lon hon node" << endl;
		return Delete(current->right, k);
	}
	else
	{
		// Truong hop node = k la leaf
		if (current->left == NULL && current->right == NULL)
		{
			cout << "Node la" << endl;
			delete current;
			current = NULL;
		}

		// Truong hop node = k co 1 con
		else if (current->left == NULL && current->right != NULL)
		{
			cout << "Khuyet trai" << endl;
			Node* temp = current;
			current = current->right;
			delete temp;
		}

		else if (current->left != NULL && current->right == NULL)
		{
			cout << "Khuyet phai" << endl;
			Node* temp = current;
			current = current->left;
			delete temp;
		}
		// Truong hop node = k co 2 con
		else 
		{
			cout << "2 CON" << endl;
			Node* temp = FindMin(current->right);
			current->value = temp->value;
			current->right = Delete(current->right, current->value);
		}
	}
	return current;
}

int FindHeight(Node*& root)
{
	if (root == NULL)	return -1;
	Node* current = root;
	int left_side = FindHeight(current->left);
	int right_side = FindHeight(current->right);
	return max(left_side, right_side) + 1;

}

void Inorder(Node*& root)
{
	if (root == NULL)	return;
	Node* current = root;
	Inorder(current->left);
	cout << current->value << "\t";
	Inorder(current->right);
}

void Preorder(Node*& root)
{
	if (root == NULL)	return;
	Node* current = root;
	cout << current->value << "\t";
	Preorder(current->left);
	Preorder(current->right);
}

void Postorder(Node*& root)
{
	if (root == NULL)	return;
	Node* current = root;
	Postorder(current->left);
	Postorder(current->right);
	cout << current->value << "\t";
}

int countNode(Node* root)
{
	if (root == NULL)	return 0;
	if (root->left == NULL && root->right == NULL)
	{
		return 1;
	}
	return 1 + countNode(root->left) + countNode(root->right);
}

bool isBST(Node*& root, int lower, int upper)
{
	if (root == NULL)	return 0;

	if (root->left != NULL && root->right != NULL)
	{
		cout << root->left->value << "\t" << root->value << "\t" << root->right->value << endl;
		if (root->left->value < root->value && root->value < root->right->value)
		{
			if (not isBST(root->left, lower, root->value)) return 0;
			if (not isBST(root->right, root->value, upper)) return 0;
			return 1;
		}
	}
	else if (root->left != NULL && root->right == NULL)
	{
		if (root->left->value < root->value)	return isBST(root->left, lower, root->value);
		return 0;
	}
	else if (root->left == NULL && root->right != NULL)
	{
		if (root->right->value > root->value)	return isBST(root->right, root->value, upper);
		return 0;
	}
	else return 1;

	return 0;
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
	Node* root = new Node(30);
	Node* root1 = new Node(15);
	Node* root2 = new Node(60);
	Node* root1_1 = new Node(7);
	Node* root1_2 = new Node(22);
	Node* root2_1 = new Node(45);
	Node* root2_2 = new Node(75);
	Node* root1_2_1 = new Node(17);
	Node* root1_2_2 = new Node(27);

	root->left = root1;
	root->right = root2;
	root1->left = root1_1;
	root1->right = root1_2;
	root2->left = root2_1;
	root2->right = root2_2;
	root1_2->left = root1_2_1;
	root1_2->right = root1_2_2;

	int a = countNode(root);
	cout << a << endl;
	return 0;
}