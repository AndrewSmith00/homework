#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#pragma warning(disable : 4996)

//��������� "���������� � ����������"
struct StaffData
{
	char fullName[199];	//���
	char jobTitle[99];	//���������
	int birthYear;		//��� ��������
	int salary;			//��������
};

//��������� "���� ������"
struct Node
{
	StaffData data;		//���������� � ����������
	Node* next;			//������ �� ��������� ������� ������
};

StaffData maxName(Node* list);
StaffData maxJobTitle(Node* list);
StaffData maxBirthYear(Node* list);
StaffData maxSalary(Node* list);


Node* newNode(StaffData data);
void insertAtEnd(Node** list, StaffData data);
void insertAtStart(Node** list, StaffData data);
void insertInSorted(Node** list, StaffData data);
Node* search(Node* list, const char* key);
Node* search(Node* list, int key);
void deleteByKey(Node** list, const char* key);
void deleteByKey(Node** list, int key);
void printList(Node* list);


Node* setListFormFile(char* fileName);
void setFileFromList(char* fileName, Node* list);
template <class T>
Node* sortByField(Node* list, T max);
template <class T>
Node* sortByTwoField(Node* list, T max1, T max2);


int getMenuPointer();
void menu();

int main()
{
	setlocale(LC_ALL, "Rus");

	menu();		//����� ����

	return 0;
}



//����� �������� � ������������ ������ � ������
StaffData maxName(Node* list)
{
	StaffData res = { "\0", "\0", 0, 0 };
	char* max = new char[199];
	Node* cur = list;

	max[0] = '\0';

	if (list == NULL)
		return res;

	while (cur != NULL)
	{
		if (strcmp(cur->data.fullName, max) > 0)
		{
			res = cur->data;
			strcpy(max, cur->data.fullName);
		}

		cur = cur->next;
	}

	return res;
}

//����� �������� � ������������ ��������� � ������
StaffData maxJobTitle(Node* list)
{
	StaffData res = { "\0", "\0", 0, 0 };
	char* max = new char[199];
	Node* cur = list;

	max[0] = '\0';

	if (list == NULL)
		return res;

	while (cur != NULL)
	{
		if (strcmp(cur->data.jobTitle, max) > 0)
		{
			res = cur->data;
			strcpy(max, cur->data.jobTitle);
		}

		cur = cur->next;
	}

	return res;
}

//����� �������� � ������������ ����� �������� � ������
StaffData maxBirthYear(Node* list)
{
	StaffData res = { "\0", "\0", 0, 0 };
	int max = INT_MIN;
	Node* cur = list;

	if (list == NULL)
		return res;

	while (cur != NULL)
	{
		if (cur->data.birthYear > max)
		{
			res = cur->data;
			max = cur->data.birthYear;
		}

		cur = cur->next;
	}

	return res;
}

//����� �������� � ������������ ��������� � ������
StaffData maxSalary(Node* list)
{
	StaffData res = { "\0", "\0", 0, 0 };
	int max = INT_MIN;
	Node* cur = list;

	if (list == NULL)
		return res;

	while (cur != NULL)
	{
		if (cur->data.salary > max)
		{
			res = cur->data;
			max = cur->data.salary;
		}

		cur = cur->next;
	}

	return res;
}



//�������� ������ ���� ������
Node* newNode(StaffData data)
{
	Node* newItem = new Node;

	newItem->data = data;
	newItem->next = NULL;

	return newItem;
}

//������� ������ � ����� ������
void insertAtEnd(Node** list, StaffData data)
{
	Node* newItem = newNode(data);
	Node* cur = *list;

	if (*list == NULL)
	{
		*list = newItem;
		return;
	}

	while (cur->next != NULL)
		cur = cur->next;

	cur->next = newItem;
}

//������� ������ � ������ ������
void insertAtStart(Node** list, StaffData data)
{
	Node* newItem = newNode(data);

	newItem->next = *list;
	*list = newItem;
}

//������� ������ � � ������ ����������������� ������
void insertInSorted(Node** list, StaffData data)
{
	Node* newItem = newNode(data);
	Node* cur = *list;
	Node* prev = NULL;

	if (*list == NULL)
	{
		*list = newItem;
		return;
	}

	while (strcmp(cur->data.fullName, data.fullName) < 0)
	{
		prev = cur;
		cur = cur->next;
	}

	if (prev == NULL)
	{
		prev = newItem;
		prev->next = cur;
		*list = prev;
		return;
	}

	prev->next = newItem;
	newItem->next = cur;
}

//����� �������� � ������ �� ���������� �����
Node* search(Node* list, const char* key)
{
	Node* res = list;

	if (list == NULL)
		return NULL;

	while (strcmp(res->data.fullName, key) != 0 && strcmp(res->data.jobTitle, key) != 0)
		res = res->next;

	return res;
}

//����� �������� � ������ �� �������������� �����
Node* search(Node* list, int key)
{
	Node* res = list;

	if (list == NULL)
		return NULL;

	while ((res->data.birthYear != key) && (res->data.salary != key))
		res = res->next;

	return res;
}

//�������� �������� �� ������ �� ���������� �����
void deleteByKey(Node** list, const char* key)
{
	Node* cur = *list;
	Node* prev = NULL;

	if (list == NULL)
		return;

	if (strcmp((*list)->data.fullName, key) == 0 || strcmp((*list)->data.jobTitle, key) == 0)
	{
		Node* temp = *list;
		*list = (*list)->next;
		delete temp;

		return;
	}

	while ((strcmp(cur->data.fullName, key) != 0) && (strcmp(cur->data.jobTitle, key) != 0))
	{
		prev = cur;
		cur = cur->next;
	}

	cur = cur->next;
	prev->next = cur;
}

//�������� �������� �� ������ �� �������������� �����
void deleteByKey(Node** list, int key)
{
	Node* cur = *list;
	Node* prev = NULL;

	if (list == NULL)
		return;

	if ((*list)->data.birthYear == key || (*list)->data.salary == key)
	{
		Node* temp = *list;
		*list = (*list)->next;
		delete temp;

		return;
	}

	while ((cur->data.birthYear != key) && (cur->data.salary != key))
	{
		prev = cur;
		cur = cur->next;
	}

	cur = cur->next;
	prev->next = cur;
}

//������ ������
void printList(Node* list)
{
	Node* cur = list;

	if (list == NULL)
		return;

	while (cur != NULL)
	{
		printf("%s %s %d %d\n", cur->data.fullName, cur->data.jobTitle, cur->data.birthYear, cur->data.salary);
		cur = cur->next;
	}
}



//���������� ������ �� ���������� �����
Node* setListFormFile(char* fileName)
{
	FILE* fPtr;
	char name[66], surname[66], secondName[66], jobTitle[99], birthYear[5], salary[15];
	char* fullName = new char[199];
	StaffData temp;
	Node* res;

	fPtr = NULL;
	temp = { "\0", "\0", 0, 0 };
	res = NULL;

	fPtr = fopen(fileName, "r");

	if (fPtr == NULL)
	{
		printf("������: ���������� ������� ����.");
		return NULL;
	}

	while (fscanf(fPtr, "%s%s%s%s%s%s", surname, name, secondName, jobTitle, birthYear, salary) != EOF)
	{
		fullName[0] = '\0';

		strcat(fullName, surname);
		strcat(fullName, " ");
		strcat(fullName, name);
		strcat(fullName, " ");
		strcat(fullName, secondName);

		fullName[strlen(fullName)] = '\0';
		jobTitle[strlen(jobTitle)] = '\0';

		strcpy(temp.fullName, fullName);
		strcpy(temp.jobTitle, jobTitle);
		temp.birthYear = atoi(birthYear);
		temp.salary = atoi(salary);

		insertAtEnd(&res, temp);
	}

	fclose(fPtr);

	return res;
}

//���������� ���������� ����� �� ������
void setFileFromList(char* fileName, Node* list)
{
	FILE* fPtr = NULL;
	char* buffer = new char[999];
	char* fullName = new char[199];
	char* jobTitle = new char[99];
	char birthYearStr[5];
	char salaryStr[15];
	Node* cur = list;

	fPtr = fopen(fileName, "w");

	if (fPtr == NULL)
	{
		printf("������: ���������� ������� ����.");
		return;
	}

	if (list == NULL)
		return;

	while (cur != NULL)
	{
		buffer[0] = '\0';

		sprintf(birthYearStr, "%d", cur->data.birthYear);
		sprintf(salaryStr, "%d", cur->data.salary);

		strcat(buffer, cur->data.fullName);
		strcat(buffer, " ");
		strcat(buffer, cur->data.jobTitle);
		strcat(buffer, " ");
		strcat(buffer, birthYearStr);
		strcat(buffer, " ");
		strcat(buffer, salaryStr);
		strcat(buffer, "\n");

		cur = cur->next;

		fputs(buffer, fPtr);
	}

	fputs("\0", fPtr);

	fclose(fPtr);
}

//���������� ������ �� ������ ����
template <class T>
Node* sortByField(Node* list, T max)
{
	Node* res = NULL;
	StaffData temp = { "\0", "\0", 0, 0 };

	temp = max(list);

	while (strcmp(temp.fullName, "\0") != 0)
	{
		insertAtStart(&res, temp);
		deleteByKey(&list, temp.fullName);
		temp = max(list);
	}

	return res;
}

/*
template <class T>
Node* sortByTwoField(Node* list, T max1, T max2)
{

}
*/



//�������� ����� ���� � �����
int getMenuPointer()
{
	int menuPointer;

	printf("\n\n�������� ��������:\n");
	printf("1. ��������� ������ �� ���������� �����.\n");
	printf("2. �������� ����� ������ � ������.\n");
	printf("3. ����� ������ � ������ �� �����.\n");
	printf("4. ������� ������ �� ������ �� �����.\n");
	printf("5. �������� ������ � ������, ��������������� �� ���� \"���%\".\n");
	printf("6. ���������� ������ �� ������ ����.\n");
	printf("7. ���������� ������ �� ���� �����.\n");
	printf("8. ����� ������ �� �����.\n");
	printf("9. ���������� ������ � ��������� ����.\n");
	printf("10. �����.\n");

	scanf("%d", &menuPointer);
	return menuPointer;
}

//���������� ����
void menu()
{
	Node* list = NULL, * tempNode = NULL;
	StaffData temp;
	char fileName[99], surname[99], name[99], secondName[99], jobTitle[99], birthYearStr[5], salaryStr[15];
	char* fullName = new char[199];
	int menuPointer = getMenuPointer(), choose;

	while (true)
	{
		system("cls");

		switch (menuPointer)
		{
		case 1:
			printf("������� �������� �����:\n");
			scanf("%s", fileName);
			list = setListFormFile(fileName);
			break;

		case 2:
			printf("������� ������: �������, ���, ��������, ���������, ��� ��������, ��������.\n");
			scanf("%s%s%s%s%s%s", surname, name, secondName, jobTitle, birthYearStr, salaryStr);

			fullName[0] = '\0';

			strcat(fullName, surname);
			strcat(fullName, " ");
			strcat(fullName, name);
			strcat(fullName, " ");
			strcat(fullName, secondName);

			fullName[strlen(fullName)] = '\0';
			jobTitle[strlen(jobTitle)] = '\0';

			strcpy(temp.fullName, fullName);
			strcpy(temp.jobTitle, jobTitle);
			temp.birthYear = atoi(birthYearStr);
			temp.salary = atoi(salaryStr);

			insertAtEnd(&list, temp);
			break;

		case 3:
			printf("��������, ����� ������ ������ ������:\n");
			printf("1. ���/���������.\n");
			printf("2. ��� ��������/��������.\n");
			scanf("%d", &choose);
			
			switch (choose)
			{
			
			case 1:
				char searchDataStr[199];
				printf("������� ������, �� ������� ���������� ������������ �����:\n");
				scanf("%s", searchDataStr);
				tempNode = search(list, searchDataStr);

				if (tempNode != NULL)
					printf("%s %s %d %d\n", tempNode->data.fullName, tempNode->data.jobTitle, tempNode->data.birthYear, tempNode->data.salary);
				else
					printf("�������� � �������� ���������������� ��� � ������.\n");
				break;

			case 2:
				int searchDataInt;
				printf("������� ������, �� ������� ���������� ������������ �����:\n");
				scanf("%d", &searchDataInt);
				tempNode = search(list, searchDataInt);

				if (tempNode != NULL)
					printf("%s %s %d %d\n", tempNode->data.fullName, tempNode->data.jobTitle, tempNode->data.birthYear, tempNode->data.salary);
				else
					printf("�������� � �������� ���������������� ��� � ������.\n");
				break;

			default:
				printf("���������� ����� ����.");
				break;
			}

			break;

		case 4:
			printf("��������, ����� ������ ������ �������:\n");
			printf("1. ���/���������.\n");
			printf("2. ��� ��������/��������.\n");
			scanf("%d", &choose);

			switch (choose)
			{

			case 1:
				char searchDataStr[199];
				printf("������� ������, ������� ������ �������:\n");
				scanf("%s", searchDataStr);
				deleteByKey(&list, searchDataStr);

				break;

			case 2:
				int searchDataInt;
				printf("������� ������, ������� ������ �������:\n");
				scanf("%d", &searchDataInt);
				deleteByKey(&list, searchDataInt);

				break;

			default:
				printf("���������� ����� ����.");
				break;
			}

			break;

		case 5:
			printf("������� ������: �������, ���, ��������, ���������, ��� ��������, ��������.\n");
			scanf("%s%s%s%s%s%s", surname, name, secondName, jobTitle, birthYearStr, salaryStr);

			fullName[0] = '\0';

			strcat(fullName, surname);
			strcat(fullName, " ");
			strcat(fullName, name);
			strcat(fullName, " ");
			strcat(fullName, secondName);

			fullName[strlen(fullName)] = '\0';
			jobTitle[strlen(jobTitle)] = '\0';

			strcpy(temp.fullName, fullName);
			strcpy(temp.jobTitle, jobTitle);
			temp.birthYear = atoi(birthYearStr);
			temp.salary = atoi(salaryStr);

			insertInSorted(&list, temp);
			break;

		case 6:
			printf("�������� ����, �� �������� ������ ������������� ������:\n");
			printf("1. ���.\n");
			printf("2. ���������.\n");
			printf("3. ��� ��������.\n");
			printf("4. ��������.\n");

			scanf("%d", &choose);

			switch (choose)
			{
			case 1:
				list = sortByField(list, maxName);
				break;

			case 2:
				list = sortByField(list, maxJobTitle);
				break;

			case 3:
				list = sortByField(list, maxBirthYear);
				break;

			case 4:
				list = sortByField(list, maxSalary);
				break;

			default:
				printf("����������� ����� ����.\n");
				break;
			}

			break;

		case 7:
			break;

		case 8:
			printList(list);
			break;

		case 9:
			printf("������� �������� �����:\n");
			scanf("%s", fileName);

			setFileFromList(fileName, list);
			break;

		case 10:
			exit(0);
			break;

		default:
			printf("����������� ����� ����");
			return;
			break;
		}

		menuPointer = getMenuPointer();
	}
}