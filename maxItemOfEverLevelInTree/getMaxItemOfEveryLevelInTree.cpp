#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "tree_lib.cpp"
#include "tree_lib.h"
#pragma warning(disable : 4996) 

struct dictData
{
	Node* key;
	int value;
};

struct dictNode
{
	dictData data;
	dictNode* next;
};

dictNode* newNode(Node* key, int value);
void push(dictNode** dict, Node* key, int value);
void push_end(dictNode** dict, Node* key, int value);
dictData pop(dictNode** dict);

int setBinTreeByFile(char* filename, Node** tree);
void getLevelOfEveryNode(Node* tree);

int main()
{
	setlocale(LC_ALL, "Rus");

	char filename[99];
	Node* tree = NULL;
	dictNode* dict = NULL;

	printf("Введите название файла:\n");
	scanf("%s", filename);

	setBinTreeByFile(filename, &tree);

	ViewTreeByLevel(tree);
	
	getLevelOfEveryNode(tree);
}

dictNode* newNode(Node* key, int value)
{
	dictNode* item = new dictNode;
	item->data.key = key;
	item->data.value = value;
	item->next = NULL;
	return item;
}

void push(dictNode** dict, Node* key, int value)
{
	dictNode* item = newNode(key, value);
	item->next = *dict;
	*dict = item;
}

void push_end(dictNode** dict, Node* key, int value)
{
	dictNode* item = newNode(key, value);

	if (*dict == NULL)
	{
		*dict = item;
		return;
	}

	dictNode* cur = *dict;
	while (cur->next != NULL)
		cur = cur->next;

	cur->next = item;
}

dictData pop(dictNode** dict)
{
	if (*dict == NULL)
		return {NULL, 0};

	dictNode* temp = NULL;
	dictData value = { NULL, 0 };

	value = (*dict)->data;

	temp = *dict;
	*dict = (*dict)->next;
	delete temp;

	return value;
}



int setBinTreeByFile(char* filename, Node** tree)
{
	FILE* fPtr = NULL;
	char buffer[99];
	int num;

	*tree = NULL;
	fPtr = fopen(filename, "r");

	if (fPtr == NULL)
	{
		printf("Ошибка: неверное имя файла.\n");
		return -1;
	}

	while (fscanf(fPtr, "%s", buffer) != EOF)
	{
		buffer[strlen(buffer)] = '\0';

		num = atoi(buffer);

		*tree = AddTree(*tree, num);
	}
}

void getLevelOfEveryNode(Node* tree)
{
	if (tree == NULL)
		return;
	dictNode* queue = NULL;
	Node* cur = NULL, * temp = NULL;
	dictData tempData = { NULL, 0 };
	int level = 1, max = INT_MIN, curLevel;
	dictNode* stack = NULL;

	push(&queue, tree, level);

	while (queue != NULL)
	{
		tempData = pop(&queue);
		cur = tempData.key;
		level = tempData.value;
		push(&stack, cur, level);
		curLevel = level;

		if (cur->left)
			push_end(&queue, cur->left, (level + 1));
		if (cur->right)
			push_end(&queue, cur->right, (level + 1));
	}

	while (stack != NULL)
	{	

		tempData = pop(&stack);
		temp = tempData.key;
		level = tempData.value;

		if (level != curLevel)
		{
			printf("Максимальный на %d уровне: %d\n", curLevel, max);
			max = INT_MIN;
			curLevel = level;
		}

		if (temp->data > max)
			max = temp->data;
	}
	
	printf("Максимальный на 1 уровне: %d\n", tree->data );

	printf("\n");
}