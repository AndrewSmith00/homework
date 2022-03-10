#include <iostream>
#include <stdio.h>
#include "stringLib.h"

using namespace std;

void UseMenu();
char* setString();
int setMenuPoint();
void printIsEven(char* str1, char* str2);
void checkIsEmpty(char* str);

int main()
{
	setlocale(LC_ALL, "Rus");
	char str[98] = "hello";
	char str2[98] = "";
	UseMenu();
}

void UseMenu()
{
	int menuPoint;
	char* str1 = new char[98]{ "" };
	char* str2 = new char[98]{ "" };

	printf("1. Ввести строку.\n2. Длина строки.\n3. Сложение строк.\n4. Сравнение строк.\n5. Копирование строк.\n6. Выход.\n");

	while (true)
	{
		menuPoint = setMenuPoint();

		if (menuPoint)

		switch (menuPoint)
		{
		case 1:
			str1 = setString();
			break;
		case 2:
			checkIsEmpty(str1);
			printf("Длина строки - %d.\n", strlen(str1));
			break;
		case 3:
			checkIsEmpty(str1);
			str2 = setString();
			printf("Полученная строка: %s.\n", my_strcat(str1, str2));
			break;
		case 4:
			checkIsEmpty(str1);
			str2 = setString();
			printIsEven(str1, str2);
			break;
		case 5:
			checkIsEmpty(str1);
			str2 = my_strcpy(str2, str1);
			printf("Строка скопирована.\n");
			break;
		case 6:
			exit(0);
			break;
		default:
			printf("Неизвестное значение.\nВыберите действие:\n");
			scanf_s("%d", &menuPoint);
			break;
		}
	}
}

char* setString() {
	char* str = new char[98];
	printf("Введите строку:\n");
	scanf_s("%s", str, 99);
	return str;
}

int setMenuPoint() {
	int menuPoint;
	printf("Выберите действие:\n");
	scanf_s("%d", &menuPoint);
	return menuPoint;
}

void printIsEven(char* str1, char* str2)
{
	int isEven = my_strcmp(str1, str2);
	if (isEven == 1)
		printf("Первая строка больше второй.\n");
	else if (isEven == -1)
		printf("Первая строка меньше второй.\n");
	else
		printf("Строки равны.\n");
}

void checkIsEmpty(char* str) {
	if (*str == '\0')
	{
		printf("Для начала введите строку, с которой вы хотите работать:\nВведите строку:\n");
		scanf_s("%s", str, 98);
	}
}