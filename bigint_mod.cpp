#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#pragma warning(disable : 4996)

struct Node
{
	char data[3];
	Node* next;
};

Node* newNode(char a, char b);
void push(Node** head, char a, char b);
void push_back(Node** head, char a, char b);
void reverse(Node** head);
int listSize(Node* head);
void printList(Node* node);
void parseString(Node** head, char* str);

Node* bigint_substruct(Node** first, Node** second);
Node* bigint_mod(Node** first, Node** second);
int bigint_compare(Node** first, Node** second);
int bigint_countPlaces(Node* head);
Node* difference(Node** first, Node** second);

int main()
{
	Node* first = NULL;
	Node* second = NULL;
	Node* res = NULL;
	char num[500];

	printf("Enter first number:\n");
	scanf("%s", num);
	parseString(&first, num);

	printf("Enter second number:\n");
	scanf("%s", num);
	parseString(&second, num);

	res = bigint_mod(&first, &second);
	printf("First number: "); printList(first);
	printf("\nSecond number: "); printList(second);
	printf("\n");
	printList(first); printf(" %% "); printList(second); printf(" = "); printList(res);
	//printf("%d ", bigint_compare(&second, &first));
	//printf("%d ", listSize(second));
}

Node* newNode(char a, char b)
{
	Node* new_node = new Node;
	new_node->data[0] = a;
	new_node->data[1] = b;
	new_node->data[2] = '\0';
	new_node->next = NULL;
	return new_node;
}

void push(Node** head, char a, char b)
{
	Node* new_node = newNode(a, b);
	new_node->next = *head;
	*head = new_node;
}

void push_back(Node** head, char a, char b)
{
	Node* new_node = newNode(a, b);
	if (*head == NULL)
	{
		*head = new_node;
		return;
	}

	Node* current = *head;
	while (current->next != NULL)
		current = current->next;

	current->next = new_node;
}

void reverse(Node** head)
{
	Node* current = *head;
	Node* prev = NULL, * after = NULL;
	while (current != NULL) {
		after = current->next;
		current->next = prev;
		prev = current;
		current = after;
	}
	*head = prev;
}

int listSize(Node* head)
{
	Node* cur = head;
	int size = 0;

	while (cur)
	{
		size++;
		cur = cur->next;
	}

	return size;
}

void printList(Node* head)
{
	Node* cur = head;
	/*
	if (cur->data[1] == '-')
	{
		printf("%c", cur->data[1]);
		cur = cur->next;

		while (atoi(cur->data) == 0)
			cur = cur->next;
	}

	if (cur->data[0] == '0')
	{
		printf("%c", cur->data[1]);
		cur = cur->next;
	}
	*/
	while (cur != NULL) {
		printf("%s", cur->data);
		cur = cur->next;
	}
}

void parseString(Node** head, char* str)
{
	int len;

	len = strlen(str);

	if (len % 2 == 0)
		for (int i = 0; i < len; i += 2)
			push_back(head, str[i], str[i + 1]);
	else
	{
		push_back(head, '0', str[0]);
		for (int i = 1; i < len; i += 2)
			push_back(head, str[i], str[i + 1]);
	}
}

Node* bigint_substruct(Node** first, Node** second)
{
	Node* res = NULL;


	if (bigint_compare(first, second) == 1)
		res = difference(first, second);
	else if (bigint_compare(first, second) == -1)
	{
		res = difference(second, first);
		push_back(&res, '0', '-');
	}
	else
		push_back(&res, '0', '0');

	reverse(&res);

	return res;
}

Node* bigint_mod(Node** first, Node** second)
{
	Node* res = NULL;

	Node* temp = *first;
	Node* temp1;

	while (temp->data[1] != '-')
	{
		res = temp;
		temp1 = bigint_substruct(&temp, second);
		temp = temp1;
		printList(res);
		printf("\n");
	}
	printList(temp);


	return res;
}

int bigint_compare(Node** first, Node** second)
{
	int firstSize, secondSize;
	Node* cur1, * cur2;

	firstSize = bigint_countPlaces(*first);
	secondSize = bigint_countPlaces(*second);

	cur1 = *first;
	cur2 = *second;

	if (firstSize > secondSize)
		return 1;
	else if (firstSize < secondSize)
		return -1;
	else
	{
		while (atoi(cur1->data) == 0)
			cur1 = cur1->next;
		while (atoi(cur2->data) == 0)
			cur2 = cur2->next;

		while (cur1 && cur2)
		{
			if (atoi(cur1->data) > atoi(cur2->data))
				return 1;
			else if (atoi(cur1->data) < atoi(cur2->data))
				return -1;
			else
			{
				cur1 = cur1->next;
				cur2 = cur2->next;
			}
		}
	}
	
	if (cur1)
		return 1;
	if (cur2)
		return -1;
	if (!cur1 && !cur2)
		return 0;

}

int bigint_countPlaces(Node* head)
{
	Node* cur = head;
	int size = 0;

	while (cur && atoi(cur->data) == 0)
		cur = cur->next;

	while (cur)
	{
		size++;
		cur = cur->next;
	}

	return size;
}

Node* difference(Node** first, Node** second)
{
	Node* res = NULL;
	Node* cur1 = NULL, * cur2 = NULL;
	int carry = 0, substract;
	char firstDigit, secondDigit;

	reverse(first);
	reverse(second);

	cur1 = *first, cur2 = *second;

	while (cur1 != NULL || cur2 != NULL) {

		substract = carry + (cur1 ? atoi(cur1->data) : 0) - (cur2 ? atoi(cur2->data) : 0);
		if (substract < 0)
		{
			carry = -1;
			substract = substract + 100;
		}
		else
		{
			carry = 0;
		}

		firstDigit = substract / 10 + 48;
		secondDigit = substract % 10 + 48;

		push_back(&res, firstDigit, secondDigit);

		if (cur1)
			cur1 = cur1->next;
		if (cur2)
			cur2 = cur2->next;
	}

	reverse(first);
	reverse(second);

	return res;
}