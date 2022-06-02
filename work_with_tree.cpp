#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#pragma warning(disable : 4996)

struct Node
{
	int data;
	Node* left;
	Node* right;
};

struct stackNode
{
	Node* info;
	stackNode* next;
};

Node* newNode(int num);
void AddTree(Node* root, int num);
void FindTree(Node* root, int num, Node*& ad, Node*& adr);
Node* DeleteTree(Node* root, int num);
Node* DeleteTreeP(Node* root, int num, char p);
void ViewTree1(Node* root);

int main()
{

}

Node* newNode(int num)
{
	Node* new_node;
	new_node->data = num;
	new_node->left = NULL;
	new_node->right = NULL;
	return new_node;
}

void AddTree(Node* root, int num)
{
	if (root == NULL)
	{
		root = newNode(num);
		return;
	}

	Node* cur = root;
	while (cur)
	{
		if (cur->data > num)
			if (cur->left == NULL)
			{
				cur->left = newNode(num);
				return;
			}
			else
				cur = cur->left;
		else
			if (cur->right == NULL)
			{
				cur->right = newNode(num);
				return;
			}
			else
				cur = cur->right;
	}

	return;
}

void FindTree(Node* root, int num, Node*& ad, Node*& adr)
{
	ad = root;
	adr = NULL;

	while (ad != NULL)
	{
		if (ad->data > num)
		{
			adr = ad;
			ad = ad->left;
		}
		else if (ad->data < num)
		{
			adr = ad;
			ad = ad->right;
		}
		else
			return;
	}

	adr = NULL;
}

Node* DeleteTree(Node* root, int num)
{
	Node* cur = NULL, * parent = NULL, * temp;
	FindTree(root, num, cur, parent);

	while (true)
	{
		if (cur == NULL) return root;
		if (parent == NULL)
		{
			if (cur->left == NULL && cur->right == NULL)
			{
				delete cur;
				return NULL;
			}
			else if (cur->left == NULL)
			{
				temp = cur->right;
				delete(cur);
				return temp;
			}
			else if (cur->right == NULL)
			{
				temp = cur->left;
				delete(cur);
				return temp;
			}
		}
		if (cur->left == NULL && cur->right == NULL)
		{
			if (parent->left == cur) parent->left = NULL;
			else parent->right = NULL;
			delete cur;
			return root;
		}
		else if (cur->left == NULL)
		{
			if (parent->left == cur) parent->left = cur->right;
			else parent->right = cur->right;
			delete cur;
			return root;
		}
		else if (cur->left == NULL)
		{
			if (parent->left == cur) parent->left = cur->left;
			else parent->right = cur->left;
			delete cur;
			return root;
		}
		else
		{
			temp = cur;
			parent = cur;
			cur = cur->right;

			while (cur->left != NULL)
			{
				parent = cur;
				cur= cur->left;
			}
			temp->data = cur->data;
			delete temp;
		}
	}

	return root;
}

Node* DeleteTreeP(Node* root, int num, char p)
{
	Node* cur = NULL, * parent = NULL, * temp, * tempParent;
	bool flag;

	FindTree(root, num, cur, parent);

	if (cur == NULL)
		return root;
	flag = (p == 'L');
	parent = cur;
	if (flag)
		cur = cur->left;
	else
		cur = cur->right;

	tempParent = parent;
	temp = cur;

	while ((flag && tempParent->left != NULL) || (!flag and tempParent->right != NULL))
	{
		parent = tempParent;
		cur = temp;

		while (cur->left != NULL || cur->right != NULL)
		{
			while (cur->left != NULL)
			{
				parent = cur;
				cur = cur->left;
			}
			while (cur->right != NULL)
			{
				parent = cur;
				cur = cur->right;
			}
		}

		if (parent->left == cur) cur->left = NULL;
		else parent->right = NULL;
		delete (cur);
	}

	return root;
}

void ViewTree1(Node* root)
{
	if (root == NULL) return;

	Node* cur = NULL;

}
