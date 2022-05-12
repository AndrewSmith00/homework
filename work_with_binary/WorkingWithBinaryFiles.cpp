#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#pragma warning(disable : 4996) 

using namespace std;

/*
Кузнецов Андрей, 15 группа
Вариант 21
Файл содержит информацию о студентах-задолженниках книг в библиотеке в виде:
	Номер группы | ФИО | Место жительства | Количество несданных книг | Стоимоть несданных книг
Задача:
a) Опрелить студента, не сдавшего наибольшее количество книг, и студента, обладающего
книгами максимальной стоимости
б) Выдать информацию по группам в виде:
	Номер группы | Количество книг, подлежащих возврату | Общая стоимость этих книг
Выходные данные упорядочить по номеру группы.
*/

struct Student
{
	char name[30];
	char surname[30];
	char secondname[30];
	char adressStreet[30];
	int adress, groupNumber, booksNumber, booksValue;
};

struct Group
{
	int groupNumber, booksNumber, booksValue;
};

int studenSize = sizeof(struct Student);
int groupSize = sizeof(struct Group);

int openFile(char* filename);
int insertAtStart(char* filename);
int insertAtMiddle(char* filename);
int insertAtEnd(char* filename);
int removeData(char* filename);
int changeData(char* filename);
int getInfoFromFile(char* fileName);
int printFile(char* fileName);

void getGroupsInfo(Student* arrOfStudents, Group* groupInfo, int n);
Student getMaxBooksNumber(Student* arrOfStudent, int n);
Student getMaxBooksValue(Student* arrOfStudent, int n);

int getMenuPointer();
int setDataToFile(FILE* fPtr, int amount);
int removeByNumber(char* filename);
int removeByData(char* filename);
int getStudentInfo(char* filename, Student* arrOfStudents, long& count);
void sortByGroups(char* filename);
void sortByName(char* filename);

void menu();

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	menu();

	return 0;
}

int openFile(char* filename)
{
	FILE* fPtr = NULL;
	int errorCode;

	printf("Введите название файла:\n");
	if (scanf("%s", filename) != 1)
	{
		printf("Ошибка: неправильно введено название файла\n");
		return -2;
	}

	fPtr = fopen(filename, "rb");

	if (fPtr == NULL) fPtr = fopen(filename, "wb");
	if (fPtr == NULL)
	{
		printf("Ошибка: файл не был открыт\n");
		return -1;
	}

	fclose(fPtr);
	return 0;
}

int insertAtStart(char* filename)
{
	Student student;
	FILE* fPtr1 = NULL;
	FILE* fPtr2 = NULL;
	int amount, errorCode;

	fPtr1 = fopen(filename, "rb");
	fPtr2 = fopen("temp.bin", "wb");

	if (fPtr1 == NULL) openFile(filename);
	if (fPtr2 == NULL)
	{
		printf("Ошибка: невозможно открыть файл\n");
		return -1;
	}

	printf("Введите количество записей:\n");

	errorCode = scanf("%d", &amount);

	if (errorCode != 1)
	{
		printf("Ошибка: неверно указано количество записей\n");
		return -2;
	}

	setDataToFile(fPtr2, amount);

	while (fread(&student, studenSize, 1, fPtr1) != NULL)
		fwrite(&student, studenSize, 1, fPtr2);

	fclose(fPtr1); fclose(fPtr2);
	remove(filename);
	rename("temp.bin", filename);
	return 0;
}

int insertAtMiddle(char* filename)
{
	Student student;
	FILE* fPtr1 = NULL;
	FILE* fPtr2 = NULL;
	int amount, pos, errorCode;

	fPtr1 = fopen(filename, "rb");
	fPtr2 = fopen("temp.bin", "wb");

	if (fPtr1 == NULL) openFile(filename);
	if (fPtr2 == NULL)
	{
		printf("Ошибка: невозможно открыть файл\n");
		return -1;
	}

	printf("Введите позицию, в которую необходимо записать данные\n");
	errorCode = scanf("%d", &pos);

	if (errorCode != 1)
	{
		printf("Ошибка: неверно указана позиция\n");
		return -2;
	}

	printf("Введите количество записей:\n");
	errorCode = scanf("%d", &amount);

	if (errorCode != 1)
	{
		printf("Ошибка: неверно указано количество записей\n");
		return -2;
	}

	for (int i = 0; i < pos - 1; i++)
	{
		if (fread(&student, studenSize, 1, fPtr1) == NULL) break;
		fwrite(&student, studenSize, 1, fPtr2);
	}

	setDataToFile(fPtr2, amount);

	while (fread(&student, studenSize, 1, fPtr1) != NULL)
		fwrite(&student, studenSize, 1, fPtr2);

	fclose(fPtr1); fclose(fPtr2);
	remove(filename);
	rename("temp.bin", filename);
	return 0;
}

int insertAtEnd(char* filename)
{
	Student student;
	FILE* fPtr1 = NULL;
	FILE* fPtr2 = NULL;
	int amount, errorCode;

	fPtr1 = fopen(filename, "rb");
	fPtr2 = fopen("temp.bin", "wb");

	if (fPtr1 == NULL) openFile(filename);
	if (fPtr2 == NULL)
	{
		printf("Ошибка: невозможно открыть файл\n");
		return -1;
	}

	printf("Введите количество записей:\n");
	errorCode = scanf("%d", &amount);

	if (errorCode != 1)
	{
		printf("Ошибка: неверно указано количество записей\n");
		return -2;
	}

	while (fread(&student, studenSize, 1, fPtr1) != NULL)
		fwrite(&student, studenSize, 1, fPtr2);

	setDataToFile(fPtr2, amount);

	fclose(fPtr1); fclose(fPtr2);
	remove(filename);
	rename("temp.bin", filename);
	return 0;
}

int removeData(char* filename)
{
	int removeType, errorCode;

	printf("Выберите действие:\n");
	printf("1. Удалить данные по номеру записи.\n");
	printf("2. Удалить данные по содержимому записи.\n");


	errorCode = scanf("%d", &removeType);

	if (errorCode != 1)
	{
		printf("Ошибка: некорректно выбран тип удаления\n");
		return -2;
	}

	switch (removeType)
	{
	case 1:
		removeByNumber(filename);
		break;

	case 2:
		removeByData(filename);
		break;

	default:
		printf("Ошибка: некорректно выбран тип удаления\n");
		break;
	}

	return 0;
}

int changeData(char* filename)
{
	Student student;
	FILE* fPtr1 = NULL;
	FILE* fPtr2 = NULL;
	int amount, pos, errorCode;

	fPtr1 = fopen(filename, "rb");
	fPtr2 = fopen("temp.bin", "wb");

	if (fPtr1 == NULL) openFile(filename);
	if (fPtr2 == NULL)
	{
		printf("Ошибка: невозможно открыть файл\n");
		return -1;
	}

	printf("Введите позицию, в которой необходимо исправить данные\n");
	errorCode = scanf("%d", &pos);

	if (errorCode != 1)
	{
		printf("Ошибка: неверно указана позиция\n");
		return -2;
	}

	for (int i = 0; i < pos; i++)
	{
		if (fread(&student, studenSize, 1, fPtr1) == NULL) break;
		fwrite(&student, studenSize, 1, fPtr2);
	}

	printf("Введите данные, которые необходимо записать на место имправленных\n");
	printf("№ группы | Фамилия | Имя | Отчество | Улица | Дом | Количество книг | Стоимость книг\n");
	errorCode = scanf("%d%s%s%s%s%d%d%d", &student.groupNumber, student.surname, student.name, student.secondname, student.adressStreet, &student.adress, &student.booksNumber, &student.booksValue);

	if (errorCode != 8)
	{
		printf("Ошибка: неверно введены данные о студенте\n");
		return -2;
	}

	fwrite(&student, studenSize, 1, fPtr2);

	while (fread(&student, studenSize, 1, fPtr1) != NULL)
		fwrite(&student, studenSize, 1, fPtr2);

	fclose(fPtr1); fclose(fPtr2);
	remove(filename);
	rename("temp.bin", filename);
	return 0;
}

int getInfoFromFile(char* fileName)
{
	Student* arrOfStudents = new Student[999];
	Group* groupsInfo = new Group[10];
	long count = 0;
	Student maxBooksNumber, maxBooksValue;

	FILE* fPtr = fopen(fileName, "rb");

	if (fPtr == NULL) {
		printf("Ошибка при открытии файла");
		return -1;
	}
	else {
		while (fread(&arrOfStudents[count], sizeof(struct Student), 1, fPtr) != NULL)
		{
			count++;
			fseek(fPtr, count * sizeof(struct Student), 0);
		}

		getGroupsInfo(arrOfStudents, groupsInfo, count);

		printf("Группа | Количество книг | Стоимость книг\n");
		for (int i = 0; i < 11; i++)
		{
			if (groupsInfo[i].groupNumber > 0)
				printf("%6d %15d %15d\n", groupsInfo[i].groupNumber, groupsInfo[i].booksNumber, groupsInfo[i].booksValue);
		}

		maxBooksNumber = getMaxBooksNumber(arrOfStudents, count);
		maxBooksValue = getMaxBooksValue(arrOfStudents, count);

		printf("Студент с максимальным количеством книг:\n");
		printf("%2d %-10s %-10s %-10s %-10s %3d %2d %5d\n", maxBooksNumber.groupNumber, maxBooksNumber.surname, maxBooksNumber.name, maxBooksNumber.secondname, maxBooksNumber.adressStreet, maxBooksNumber.adress, maxBooksNumber.booksNumber, maxBooksNumber.booksValue);
		printf("Студент с максимальной стоимостью книг:\n");
		printf("%2d %-10s %-10s %-10s %-10s %3d %2d %5d\n", maxBooksNumber.groupNumber, maxBooksNumber.surname, maxBooksNumber.name, maxBooksNumber.secondname, maxBooksNumber.adressStreet, maxBooksNumber.adress, maxBooksNumber.booksNumber, maxBooksNumber.booksValue);

		return 0;
	}
}

int printFile(char* fileName)
{
	FILE* fPtr = fopen(fileName, "rb");
	Student student;

	//sortByName(fileName);
	//sortByGroups(fileName);

	if (!fPtr)
	{
		printf("Файл не был открыт");
		return -1;
	}
	else
	{
		while (fread(&student, sizeof(struct Student), 1, fPtr) != 0)
			printf("%2d %-20s %-20s %-20s %-20s %3d %2d %5d\n", student.groupNumber, student.surname, student.name, student.secondname, student.adressStreet, student.adress, student.booksNumber, student.booksValue);

		fclose(fPtr);
		return 0;
	}
}



Student getMaxBooksNumber(Student* arrOfStudent, int n)
{
	Student max;
	max.booksNumber = 0;

	for (int i = 0; i < n; i++)
		if (arrOfStudent[i].booksNumber > max.booksNumber)
			max = arrOfStudent[i];

	return max;
}

Student getMaxBooksValue(Student* arrOfStudent, int n)
{
	Student max;
	max.booksValue = 0;

	for (int i = 0; i < n; i++)
		if (arrOfStudent[i].booksValue > max.booksValue)
			max = arrOfStudent[i];

	return max;
}

void getGroupsInfo(Student* student, Group* groupInfo, int n)
{
	int num;

	for (int i = 0; i < 10; i++)
	{
		groupInfo[i].groupNumber = 0;
		groupInfo[i].booksNumber = 0;
		groupInfo[i].booksValue = 0;
	}

	for (int i = 0; i < n; i++)
	{
		num = student[i].groupNumber;
		groupInfo[num].groupNumber = num;
		groupInfo[num].booksNumber += student[i].booksNumber;
		groupInfo[num].booksValue += student[i].booksValue;
	}
}



int setDataToFile(FILE* fPtr, int amount)
{
	Student student;
	int errorCode;

	printf("Вводите данные о студентах\n");
	printf("№ группы | Фамилия | Имя | Отчество | Улица | Дом | Количество книг | Стоимость книг\n");
	for (int i = 0; i < amount; i++)
	{
		errorCode = scanf("%d%s%s%s%s%d%d%d", &student.groupNumber, student.surname, student.name, student.secondname, student.adressStreet, &student.adress, &student.booksNumber, &student.booksValue);

		if (errorCode != 8)
		{
			printf("Ошибка: неверно введены данные о студенте\n");
			return -2;
		}

		fwrite(&student, studenSize, 1, fPtr);
	}
	return 0;
}

int removeByNumber(char* filename)
{
	Student student;
	FILE* fPtr1 = NULL;
	FILE* fPtr2 = NULL;
	int amount, pos, errorCode;

	fPtr1 = fopen(filename, "rb");
	fPtr2 = fopen("temp.bin", "wb");

	if (fPtr1 == NULL) openFile(filename);
	if (fPtr2 == NULL)
	{
		printf("Ошибка: невозможно открыть файл\n");
		return -1;
	}

	printf("Введите позицию, с которой необходимо начать удаление\n");
	errorCode = scanf("%d", &pos);

	if (errorCode != 1)
	{
		printf("Ошибка: неверно указана позиция\n");
		return -2;
	}

	printf("Введите количество записей:\n");
	errorCode = scanf("%d", &amount);

	if (errorCode != 1)
	{
		printf("Ошибка: неверно указано количество записей\n");
		return -2;
	}

	for (int i = 0; i < pos - 1; i++)
	{
		if (fread(&student, studenSize, 1, fPtr1) == NULL) break;
		fwrite(&student, studenSize, 1, fPtr2);
	}

	fseek(fPtr1, studenSize * amount, SEEK_CUR);

	while (fread(&student, studenSize, 1, fPtr1) != NULL)
		fwrite(&student, studenSize, 1, fPtr2);

	fclose(fPtr1); fclose(fPtr2);
	remove(filename);
	rename("temp.bin", filename);
	return 0;
}

int removeByData(char* filename)
{
	Student student;
	FILE* fPtr1 = NULL;
	FILE* fPtr2 = NULL;
	char fullName[99] = "", adress[3] = "", fullAdress[99] = "", strData[99] = "";
	int amount, dataType, errorCode, intData, c;

	fPtr1 = fopen(filename, "rb");
	fPtr2 = fopen("temp.bin", "wb");

	if (fPtr1 == NULL) openFile(filename);
	if (fPtr2 == NULL)
	{
		printf("Ошибка: невозможно открыть файл\n");
		return -1;
	}

	printf("Выберите, по какому критерию искать позицию для начала удаления:\n");
	printf("1. Номер группы\n");
	printf("2. ФИО\n");
	printf("3. Адрес\n");
	printf("4. Количество книг\n");
	printf("5. Стоимость книг\n");

	errorCode = scanf("%d", &dataType);

	if (errorCode != 1)
	{
		printf("Ошибка: неверно указан критерий\n");
		return -2;
	}

	printf("Введите количество записей:\n");

	errorCode = scanf("%d", &amount);

	if (errorCode != 1)
	{
		printf("Ошибка: неверно указано количество записей\n");
		return -2;
	}

	switch (dataType)
	{
	case 1:
		printf("Введите номеру группы:\n");
		errorCode = scanf("%d", &intData);
		if (errorCode != 1)
		{
			printf("Ошибка: неверно выбран номер группы\n");
			return -2;
		}

		while (fread(&student, studenSize, 1, fPtr1) != NULL)
		{
			if (student.groupNumber == intData) break;
			fwrite(&student, studenSize, 1, fPtr2);
		}

		fseek(fPtr1, studenSize * amount, SEEK_CUR);

		while (fread(&student, studenSize, 1, fPtr1) != NULL)
			fwrite(&student, studenSize, 1, fPtr2);

		fclose(fPtr1); fclose(fPtr2);
		remove(filename);
		rename("temp.bin", filename);
		break;

	case 2:
		printf("Введите ФИО студента:\n");
		while ((c = getchar()) != '\n' && c != EOF) {}
		fgets(strData, 98, stdin);

		while (fread(&student, studenSize, 1, fPtr1) != NULL)
		{
			strcat(fullName, student.surname);
			strcat(fullName, " ");
			strcat(fullName, student.name);
			strcat(fullName, " ");
			strcat(fullName, student.secondname);
			strcat(fullName, "\n");

			if (strcmp(fullName, strData) == 0) break;
			fwrite(&student, studenSize, 1, fPtr2);

			fullName[0] = '\0';
		}

		fseek(fPtr1, studenSize * (amount - 1), SEEK_CUR);

		while (fread(&student, studenSize, 1, fPtr1) != NULL)
			fwrite(&student, studenSize, 1, fPtr2);

		fclose(fPtr1); fclose(fPtr2);
		remove(filename);
		rename("temp.bin", filename);
		break;

	case 3:
		printf("Введите адрес проживания студента:\n");
		fflush(stdin);
		fgets(strData, 98, stdin);

		while (fread(&student, studenSize, 1, fPtr1) != NULL)
		{
			strcat(fullAdress, student.adressStreet);
			strcat(fullAdress, " ");
			sprintf(adress, "%d", student.adress);
			strcat(fullAdress, adress);

			if (strcmp(fullAdress, strData) == 0) break;
			fwrite(&student, studenSize, 1, fPtr2);
		}

		//fseek(fPtr1, studenSize * amount, SEEK_CUR);

		while (fread(&student, studenSize, 1, fPtr1) != NULL)
			fwrite(&student, studenSize, 1, fPtr2);

		fclose(fPtr1); fclose(fPtr2);
		remove(filename);
		rename("temp.bin", filename);
		break;

	case 4:
		printf("Введите количество книг:\n");
		errorCode = scanf("%d", &intData);

		if (errorCode != 1)
		{
			printf("Ошибка: неверно введено количество книг\n");
			return -2;
		}

		while (fread(&student, studenSize, 1, fPtr1) != NULL)
		{
			if (student.booksNumber == intData) break;
			fwrite(&student, studenSize, 1, fPtr2);
		}

		fseek(fPtr1, studenSize * amount, SEEK_CUR);

		while (fread(&student, studenSize, 1, fPtr1) != NULL)
			fwrite(&student, studenSize, 1, fPtr2);

		fclose(fPtr1); fclose(fPtr2);
		remove(filename);
		rename("temp.bin", filename);
		break;

	case 5:
		printf("Введите стоимость книг:\n");
		errorCode = scanf("%d", &intData);

		if (errorCode != 1)
		{
			printf("Ошибка: неверно введена стоимость книг\n");
			return -2;
		}

		while (fread(&student, studenSize, 1, fPtr1) != NULL)
		{
			if (student.booksValue == intData) break;
			fwrite(&student, studenSize, 1, fPtr2);
		}

		fseek(fPtr1, studenSize * amount, SEEK_CUR);

		while (fread(&student, studenSize, 1, fPtr1) != NULL)
			fwrite(&student, studenSize, 1, fPtr2);

		fclose(fPtr1); fclose(fPtr2);
		remove(filename);
		rename("temp.bin", filename);
		break;

	default:
		printf("Выбран неизвестный тип данных\n");
		break;
	}

	return 0;
}

int getMenuPointer()
{
	int menuPointer, errorCode;

	printf("Выберите действие:\n");
	printf("1. Открыть/создать файл\n");
	printf("2. Добавить запись в начало\n");
	printf("3. Добавить запись в середину\n");
	printf("4. Добавить запись в конец\n");
	printf("5. Удалить запись\n");
	printf("6. Изменить запись\n");
	printf("7. Выдать информацию о задолженностях по группам и о студентах с наибольшим долгом\n");
	printf("8. Распечатать файл\n");
	printf("9. Выход\n");

	errorCode = scanf("%d", &menuPointer);

	if (errorCode != 1)
	{
		printf("Ошибка: некорректно введён пункт меню\n");
		return -2;
	}

	return menuPointer;
}

int getStudentInfo(char* filename, Student* arrOfStudents, long& count)
{
	FILE* fPtr = fopen(filename, "rb");
	count = 0;

	if (!fPtr)
	{
		printf("Ошибка при открытии файла");
		return -1;
	}
	else
	{
		while (fread(&arrOfStudents[count], sizeof(struct Student), 1, fPtr) != 0)
		{
			count++;
			fseek(fPtr, count * sizeof(struct Student), 0);
		}

		fclose(fPtr);
		return 0;
	}
}

void sortByName(char* filename)
{
	FILE* fPtr;
	Student* arrOfStudents = new Student[999];
	Student temp;
	long count;

	getStudentInfo(filename, arrOfStudents, count);

	for (int i = 0; i < count - 1; i++)
		for (int j = 0; j < count - i - 1; j++)
			if (strcmp(arrOfStudents[j].surname, arrOfStudents[j + 1].surname) > 0)
			{
				temp = arrOfStudents[j];
				arrOfStudents[j] = arrOfStudents[j + 1];
				arrOfStudents[j + 1] = temp;
			}

	fPtr = fopen(filename, "wb");

	for (int i = 0; i < count; i++)
	{
		fseek(fPtr, i * sizeof(struct Student), 0);
		fwrite(&arrOfStudents[i], sizeof(struct Student), 1, fPtr);
	}

	fclose(fPtr);
	delete[] arrOfStudents;
}

void sortByGroups(char* filename)
{
	FILE* fPtr;
	Student* arrOfStudents = new Student[999];
	Student temp;
	long count;

	getStudentInfo(filename, arrOfStudents, count);

	for (int i = 0; i < count - 1; i++)
		for (int j = 0; j < count - i - 1; j++)
			if (arrOfStudents[j].groupNumber > arrOfStudents[j + 1].groupNumber)
			{
				temp = arrOfStudents[j];
				arrOfStudents[j] = arrOfStudents[j + 1];
				arrOfStudents[j + 1] = temp;
			}

	fPtr = fopen(filename, "wb");

	for (int i = 0; i < count; i++)
	{
		fseek(fPtr, i * sizeof(struct Student), 0);
		fwrite(&arrOfStudents[i], sizeof(struct Student), 1, fPtr);
	}

	fclose(fPtr);
	delete[] arrOfStudents;
}



void menu()
{
	char filename[50];
	int menuPointer;

	printf("Введите название файла:\n");
	scanf("%s", filename);
	menuPointer = getMenuPointer();

	while (true)
	{
		switch (menuPointer)
		{
		case 1:
			system("cls");
			openFile(filename);
			printf("\n\n");

			menuPointer = getMenuPointer();
			break;

		case 2:
			system("cls");
			insertAtStart(filename);
			printf("\n\n");

			menuPointer = getMenuPointer();
			break;

		case 3:
			system("cls");
			insertAtMiddle(filename);
			printf("\n\n");

			menuPointer = getMenuPointer();
			break;

		case 4:
			system("cls");
			insertAtEnd(filename);
			printf("\n\n");

			menuPointer = getMenuPointer();
			break;

		case 5:
			system("cls");
			removeData(filename);
			printf("\n\n");

			menuPointer = getMenuPointer();
			break;

		case 6:
			system("cls");
			changeData(filename);
			printf("\n\n");

			menuPointer = getMenuPointer();
			break;

		case 7:
			system("cls");
			getInfoFromFile(filename);
			printf("\n\n");

			menuPointer = getMenuPointer();
			break;

		case 8:
			system("cls");
			printFile(filename);
			printf("\n\n");

			menuPointer = getMenuPointer();
			break;

		case 9:
			system("cls");
			exit(0);
			break;

		default:
			system("cls");
			printf("Ошибка: некорректно выбран пункт меню.\n");
			menuPointer = getMenuPointer();
			break;
		}
	}
}
