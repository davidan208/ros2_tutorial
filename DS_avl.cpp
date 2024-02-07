#include <iostream>

using namespace std;

struct Node
{
	int value;
	Node* left;
	Node* right;
	int height;
};

int getHeight(Node* root)
{
	if (root == NULL)	return 0;
	return 1 + max(getHeight(root->left), getHeight(root->right));
}

Node* leftRotate(Node*& root)
{
	Node* current = root;
	Node* keep = current->right;

	current->right = keep->left;
	keep->left = current;

	current->height = getHeight(current);
	keep->height = getHeight(keep);
	
	return keep;
}

Node* rightRotate(Node*& root)
{
	Node* current = root;
	Node* keep = current->left;

	current->left = keep->right;
	keep->right = current;

	current->height = getHeight(current);
	keep->height = getHeight(keep);
	
	return keep;
}

Node* insert(Node*& root, int x)
{
	if (root == NULL) {
		root = new Node();
		root->value = x;
		root->height = 1;
	}

	Node* current = root;
	if (current->value > x) {
		current->left = insert(current->left, x);
	}

	else if (current->value < x)
	{
		current->right = insert(current->right, x);
	}
	else return root;

	current->height = getHeight(current);

	int balance_factor = getHeight(current->left) - getHeight(current->right);
	// LL 
	if (balance_factor > 1 && x < current->left->value)
		return rightRotate(current);
	// RR
	if (balance_factor < -1 && x > current->right->value)
		return leftRotate(current);
	// LR
	if (balance_factor > 1 && x > current->left->value)
	{
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}
	// RL
	if (balance_factor < -1 && x < current->right->value)
	{
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}
}

Node* MaxLeft(Node*& root) {
	if (root == NULL)	return root;
	Node* current = root;
	while (current->right != NULL)	current = current->right;
	return current;
}

Node* remove(Node*& root, int x)
{
	if (root == NULL)	return root;

	if (x > root->value)	return remove(root->right, x);
	else if (x < root->value)	return remove(root->left, x);
	else
	{
		Node* current = root;
		if (current->right == NULL && current->left == NULL) {
			delete current;
			return NULL;
		}
		else if (current->left && current->right == NULL)
		{
			Node* temp = current;
			current = current->left;
			delete temp;
			return current;
		}
		else if (current->right && current->left == NULL)
		{
			Node* temp = current;
			current = current->right;
			delete temp;
			return current;
		}
		else
		{
			Node* temp = MaxLeft(current->left);
			current->value = temp->value;
			current->left = remove(current->left, current->value);
			return current;
		}
	}
	
	Node* current = root;
	current->height = getHeight(current);
	int balance_factor = getHeight(current->left) - getHeight(current->right);

	if (balance_factor > 1 && getHeight(current->left->left) - getHeight(current->right->left->right) >= 0) {
		return rightRotate(current);
	}

	if (balance_factor < -1 && getHeight(current->right->left) - getHeight(current->right->right ) <= 0)
	{
		return leftRotate(current);
	}

	if (balance_factor > 1 && getHeight(current->left->left) - getHeight(current->left->right) < 0)
	{
		current->left = leftRotate(current->left);
		return rightRotate(current);
	}

	if (balance_factor < -1 && getHeight(current->right->left) - getHeight(current->right->right) > 0)
	{
		current->right = rightRotate(current->right);
		return leftRotate(current);
	}
}


bool isAVL(Node* root)
{
	if (root == NULL)	return 0;
	if (root->left == NULL && root->right == NULL) return 1;
	if (root->left == NULL && root->right != NULL)
	{
		if (getHeight(root->right) > 1 || root->right->value <= root->value)	return 0;
		return 1;
	}
	else if (root->left != NULL && root->right == NULL)
	{
		if (getHeight(root->left) > 1 || root->left->value >= root->value)	return 0;
		return 1;
	}
	else
	{
		if (isAVL(root->left) && isAVL(root->right) && root->left->value < root->value && root->value < root->right->value)	return 1;
		return 0;
	}
}

