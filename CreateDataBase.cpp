#include <iostream>
#include <stdio.h>
#include <windows.h>
#pragma warning(disable : 4996) 

using namespace std;

struct Student
{
	char name[30];
	char surname[30];
	char secondname[30];
	char adressStreet[30];
	int adress, groupNumber, booksNumber, booksValue;
};

int setStudentInfo(char* fileName);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	char fileName[100] = { "C:/Users/aokuznetsov/source/repos/BinaryFiles/BinaryFiles/source.bin" };

	setStudentInfo(fileName);
}

int setStudentInfo(char* fileName)
{
	FILE* fPtr = fopen(fileName, "wb");
	struct Student student;
	int count;

	if (!fPtr) {
		printf("Ошибка при создании файла");
		return -1;
	}
	else {
		printf("Вводите данные о студентах. Для завершения введите - - - - 0 0 0 0\n");
		scanf("%s%s%s%s%d%d%d%d", student.surname, student.name, student.secondname, student.adressStreet, &student.adress, &student.groupNumber, &student.booksNumber, &student.booksValue);

		while(strcmp(student.surname, "-") != 0)
		{
			fwrite(&student, sizeof(struct Student), 1, fPtr);
			scanf("%s%s%s%s%d%d%d%d", student.surname, student.name, student.secondname, student.adressStreet, &student.adress, &student.groupNumber, &student.booksNumber, &student.booksValue);
		}
		fclose(fPtr);
		return 0;
	}
}