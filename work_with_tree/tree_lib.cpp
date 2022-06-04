#include <stdio.h>
#include <stdlib.h>
#include "tree_lib.h"

stackNode* newNode(Node* uz)
{
	stackNode* newNode = new stackNode;
	newNode->info = uz;
	newNode->next = NULL;
	return newNode;
}

void push(stackNode** top, Node* uz)
{
	stackNode* item = newNode(uz);
	item->next = *top;
	*top = item;
}

Node* pop(stackNode** top)
{
	if (*top == NULL)
		return NULL;

	Node* value = NULL;
	value = (*top)->info;

	stackNode* temp = *top;
	*top = (*top)->next;
	delete temp;

	return value;
}



queueNode* newQNode(Node* uz)
{
	queueNode* item = new queueNode;
	item->info = uz;
	item->next = NULL;
	return item;
}

void enQueue(queueNode** start, Node* uz)
{
	queueNode* item = newQNode(uz);

	if (*start == NULL)
	{
		*start = item;
		return;
	}

	queueNode* cur = *start;
	while (cur->next != NULL)
		cur = cur->next;

	cur->next = item;
}

Node* deQueue(queueNode** start)
{
	if (*start == NULL)
		return NULL;

	queueNode* temp = NULL;
	Node* value = NULL;

	value = (*start)->info;

	temp = *start;
	*start = (*start)->next;
	delete temp;

	return value;
}



Node* newNode(int num)
{
	Node* new_node = new Node;
	new_node->data = num;
	new_node->left = NULL;
	new_node->right = NULL;
	return new_node;
}

void InitTree(Node** root, int num)
{
	*root = NULL;
	*root = newNode(num);
}

bool NullTree(Node* root)
{
	if (root == NULL)
		return true;

	return false;
}

void AddTree(Node** root, int num)
{
	if (*root == NULL)
	{
		*root = newNode(num);
		return;
	}

	Node* cur = *root;
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

Node* DelTreeUz(Node* root, int num)
{
	Node* cur = NULL, * curParent = NULL;
	Node* temp;
	FindTree(root, num, cur, curParent);

	while (true) {
		if (cur == NULL) { return root; }
		if (curParent == NULL) {
			if (cur->left == NULL && cur->right == NULL) {
				delete(cur);
				return(NULL);
			}
			else if (cur->left == NULL) {
				temp = cur->right;
				delete(cur);
				return(temp);
			}
			else if (cur->right == NULL) {
				temp = cur->left;
				delete(cur);
				return(temp);
			}
		}

		if (cur->left == NULL and cur->right == NULL) {//----------------leaf
			if (curParent->left == cur) curParent->left = NULL;
			else curParent->right = NULL;
			delete(cur);
			return(root);
		}
		else if (cur->left == NULL) {
			if (curParent->left == cur) curParent->left = cur->right;
			else curParent->right = cur->right;
			delete(cur);
			return(root);
		}
		else if (cur->right == NULL) {
			if (curParent->left == cur) curParent->left = cur->left;
			else curParent->right = cur->left;
			delete(cur);
			return(root);
		}
		else { //-------------------------------------------------------inner

			temp = cur;
			curParent = cur;
			cur = cur->right;
			while (cur->left != NULL) {
				curParent = cur;
				cur = cur->left;
			}
			temp->data = cur->data;

		}
	}
}

Node* DelTreeP(Node* root, int num, char p)
{

	Node* cur = NULL, * curParent = NULL;
	Node* temp, * tempParent;
	FindTree(root, num, cur, curParent);
	if (cur == NULL)
		return root;

	bool f = (p == 'L');

	curParent = cur;
	if (f) { cur = cur->left; }
	else { cur = cur->right; }

	tempParent = curParent;
	temp = cur;

	while ((f and tempParent->left != NULL) or (!f and tempParent->right != NULL)) {

		curParent = tempParent;
		cur = temp;

		while (cur->left != NULL or cur->right != NULL)
		{
			while (cur->left != NULL)
			{
				curParent = cur;
				cur = cur->left;
			}
			while (cur->right != NULL)
			{
				curParent = cur;
				cur = cur->right;
			}
		}
		if (curParent->left == cur) curParent->left = NULL;
		else curParent->right = NULL;
		delete(cur);
	}

	return root;
}

void ViewTree1(Node* root)
{
	printf("\nЁлементы дерева:\n");

	if (root == NULL) return;

	Node* cur = NULL;
	stackNode* stack = NULL;

	push(&stack, root);

	while (stack != NULL)
	{
		cur = pop(&stack);
		printf("%d ", cur->data);

		if (cur->right)
			push(&stack, cur->right);
		if (cur->left)
			push(&stack, cur->left);
	}

	printf("\n");
}

void ViewTree2(Node* root)
{
	printf("\nЁлементы дерева:\n");

	Node* cur, * temp;
	stackNode* stack;

	cur = root;
	stack = NULL;
	temp = NULL;

	while (cur != NULL || stack != NULL)
	{
		while (cur != NULL)
		{
			push(&stack, cur);
			cur = cur->left;
		}
		temp = pop(&stack);
		printf("%d ", temp->data);
		cur = temp->right;
	}

	printf("\n");
}

void ViewTree3(Node* root)
{
	printf("\nЁлементы дерева:\n");

	if (root == NULL) return;

	stackNode* stack, * stack2;
	Node* cur, * temp;

	stack = NULL;
	stack2 = NULL;
	cur = NULL;
	temp = NULL;

	push(&stack, root);

	while (stack != NULL)
	{
		cur = pop(&stack);
		push(&stack2, cur);

		if (cur->left)
			push(&stack, cur->left);
		if (cur->right)
			push(&stack, cur->right);
	}
	while (stack2 != NULL)
	{
		temp = pop(&stack2);
		printf("%d ", temp->data);
	}

	printf("\n");
}

void ViewTreeByLevel(Node* root)
{
	printf("\nЁлементы дерева:\n");

	if (root == NULL)
		return;

	Node* cur = NULL;
	queueNode* queue = NULL;

	enQueue(&queue, root);

	while (queue != NULL)
	{
		cur = deQueue(&queue);
		printf("%d ", cur->data);

		if (cur->left)
			enQueue(&queue, cur->left);
		if (cur->right)
			enQueue(&queue, cur->right);
	}

	printf("\n");
}

void ViewTreeByLevelReversed(Node* root)
{
	printf("\nЁлементы дерева:\n");

	if (root == NULL)
		return;

	Node* cur = NULL, * temp = NULL;
	queueNode* queue = NULL;
	stackNode* stack = NULL;

	enQueue(&queue, root);

	while (queue != NULL)
	{
		cur = deQueue(&queue);
		push(&stack, cur);

		if (cur->left)
			enQueue(&queue, cur->left);
		if (cur->right)
			enQueue(&queue, cur->right);
	}

	while (stack != NULL)
	{
		temp = pop(&stack);
		printf("%d ", temp->data);
	}

	printf("\n");
}