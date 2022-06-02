#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Data
{
	int key;
	int value;
};

struct Node
{
	int data;
	Node* next;
};

struct DictionaryNode
{
	Data dictData;

	DictionaryNode* next;
};

Node* newNode(int new_data);
DictionaryNode* newNode(Data new_data);

void push_back(Node** head, int new_data);
void push_back(DictionaryNode** head, Data new_data);

void push(DictionaryNode** head, Data new_data);

void deleteNode(struct DictionaryNode** head, int key);

template <class T>
int listSize(T* head);

void printList(Node* node);

DictionaryNode* getAmountOfItemsInList(Node* head);

void increaseOrPush(DictionaryNode** head, int item);

DictionaryNode* sortDictionary(DictionaryNode* head);

DictionaryNode* getMaxValue(DictionaryNode* head, int max);

void printDictionary(DictionaryNode* head);

int main()
{
	Node* list = NULL;
	DictionaryNode* res = NULL;

	push_back(&list, 12);
	push_back(&list, 12);
	push_back(&list, 12);
	push_back(&list, 11);
	push_back(&list, 10);

	res = getAmountOfItemsInList(list);
	printDictionary(res);
	printf("\n");
	res = sortDictionary(res);
	printDictionary(res);

}


Node* newNode(int new_data)
{
	Node* new_node = new Node;
	new_node->data = new_data;
	new_node->next = NULL;
	return new_node;
}

DictionaryNode* newNode(Data new_data)
{
	DictionaryNode* new_node = new DictionaryNode;
	new_node->dictData= new_data;
	new_node->next = NULL;
	return new_node;
}


void push_back(Node** head, int new_data)
{
	Node* new_node = newNode(new_data);
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

void push_back(DictionaryNode** head, Data new_data)
{
	DictionaryNode* new_node = newNode(new_data);
	if (*head == NULL)
	{
		*head = new_node;
		return;
	}

	DictionaryNode* current = *head;
	while (current->next != NULL)
		current = current->next;

	current->next = new_node;
}

void push(DictionaryNode** head, Data new_data)
{
	DictionaryNode* new_node = newNode(new_data);
	new_node->next = *head;
	*head = new_node;
}

void deleteNode(struct DictionaryNode** head, int key)
{
	DictionaryNode* temp;

	if ((*head)->dictData.value == key)
	{
		temp = *head; 
		*head = (*head)->next;
		free(temp);
	}

	else
	{
		DictionaryNode* current = *head;
		while (current->next != NULL)
		{
			if (current->next->dictData.value == key)
			{
				temp = current->next;
				current->next = current->next->next;
				free(temp);
				break;
			}
			else
				current = current->next;
		}
	}
}

template <class T>
int listSize(T* head)
{
	T* cur = head;
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

	while (cur != NULL) {
		printf("%d", cur->data);
		cur = cur->next;
	}
}

DictionaryNode* getAmountOfItemsInList(Node* head)
{
	DictionaryNode* res = NULL;
	DictionaryNode* temp = NULL;
	Node* cur = head;
	int listItem;
	Data data;

	while (cur)
	{
		listItem = cur->data;
		increaseOrPush(&res, listItem);
		cur = cur->next;
	}

	return res;
}

void increaseOrPush(DictionaryNode** head, int key)
{
	DictionaryNode* cur = *head;
	Data tempData;

	if (cur == NULL)
	{
		tempData = { key, 1 };
		push_back(head, tempData);
		return;
	}

	while (cur)
	{
		if (cur->dictData.key == key)
		{
			cur->dictData.value++;
			return;
		}
		cur = cur->next;
	}
	
	if (!cur)
	{
		tempData = { key, 1 };
		push_back(head, tempData);
	}
}

DictionaryNode* sortDictionary(DictionaryNode* head)
{
	DictionaryNode* temp, * res = NULL;
	Data tempData;
	int key;

	temp = getMaxValue(head, INT_MIN);

	while (temp)
	{
		tempData = { temp->dictData.key, temp->dictData.value };
		push(&res, tempData);
		key = temp->dictData.value;
		deleteNode(&head, key);
		temp = getMaxValue(head, INT_MIN);
	}

	return res;
}

DictionaryNode* getMaxValue(DictionaryNode* head, int max)
{
	DictionaryNode* cur = head;
	DictionaryNode* res = NULL;

	if (head == NULL)
		return NULL;

	while (cur != NULL)
	{
		if (cur->dictData.value > max)
		{
			max = cur->dictData.value;
			res = cur;
		}
		cur = cur->next;
	}

	return res;
}

void printDictionary(DictionaryNode* head)
{
	DictionaryNode* cur = head;

	while (cur != NULL)
	{
		printf("Key: %d; Value: %d\n", cur->dictData.key, cur->dictData.value);
		cur = cur->next;
	}
}