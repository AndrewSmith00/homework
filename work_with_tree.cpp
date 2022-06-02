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

Node* newNode(int num);
void AddTree(Node* root, int num);
void FindTree(Node* root, int num, Node*& ad, Node*& adr);
Node* DeleteTree(Node* root, int num);

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
	Node* leaf = NULL, * parent = NULL, * temp;
	FindTree(root, num, leaf, parent);

	while (true)
	{
		if (leaf == NULL) return root;
		if (parent == NULL)
		{
			if (leaf->left == NULL && leaf->right == NULL)
			{
				delete leaf;
				return NULL;
			}
			else if (leaf->left == NULL)
			{
				temp = leaf->right;
				delete(leaf);
				return temp;
			}
			else if (leaf->right == NULL)
			{
				temp = leaf->left;
				delete(leaf);
				return temp;
			}
		}
		if (leaf->left == NULL && leaf->right == NULL)
		{
			if (parent->left == leaf) parent->left = NULL;
			else parent->right = NULL;
			delete leaf;
			return root;
		}
		else if (leaf->left == NULL)
		{
			if (parent->left == leaf) parent->left = leaf->right;
			else parent->right = leaf->right;
			delete leaf;
			return root;
		}
		else if (leaf->left == NULL)
		{
			if (parent->left == leaf) parent->left = leaf->left;
			else parent->right = leaf->left;
			delete leaf;
			return root;
		}
		else
		{
			temp = leaf;
			parent = leaf;
			leaf = leaf->right;

			while (leaf->left != NULL)
			{
				parent = leaf;
				leaf = leaf->left;
			}
			temp->data = leaf->data;
			delete temp;
		}
	}

	return root;
}

Node* DeleteTreeP(Node* root, int num, char p)
{
	Node* leaf = NULL, * parent = NULL, *temp
}