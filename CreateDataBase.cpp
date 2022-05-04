#include <stdio.h>
#include <iostream>
#include <cstring>

struct Student
{
	char name[30];
	char surname[30];
	char secondname[30];
	char adressStreet[30];
	int adress, groupNumber, booksNumber, booksValue;
};

int setStudentInfo(char* filename);
int getStudentInfo(char* filename, Student* arrOfStudents, long &count);
void sortByGroups(char* filename);

int main()
{
	char filename[100] = "source.bin";

	setStudentInfo(filename);
}

int setStudentInfo(char* filename)
{
	FILE* fPtr = fopen(filename, "wb");
	struct Student student;

	if (!fPtr) {
		printf("Ошибка при создании файла");
		return -1;
	}
	else {
		printf("Вводите данные о студентах. Для завершения введите 0 - - - - 0 0 0\n");
		printf("№ группы | Фамилия | Имя | Отчество | Улица | Дом | Количество книг | Стоимость книг\n");
		scanf("%d%s%s%s%s%d%d%d", &student.groupNumber, student.surname, student.name, student.secondname, student.adressStreet, &student.adress, &student.booksNumber, &student.booksValue);

		while(strcmp(student.surname, "-") != 0)
		{
			fwrite(&student, sizeof(struct Student), 1, fPtr);
			scanf("%d%s%s%s%s%d%d%d", &student.groupNumber, student.surname, student.name, student.secondname, student.adressStreet, &student.adress, &student.booksNumber, &student.booksValue);
		}
		
		sortByGroups(filename);
		return 0;
	}
}

int getStudentInfo(char* filename, Student* arrOfStudents, long &count)
{
	FILE* fPtr = fopen(filename, "rb");
	count = 0;

	if(!fPtr)
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

void sortByGroups(char* filename)
{
	FILE* fPtr;
	Student* arrOfStudents = new Student[999];
	Student temp;
	long count;

	getStudentInfo(filename, arrOfStudents, count);

	for (int i = 0; i < count - 1; i++)
		for (int j = 0; j < count - i - 1; j++)
			if (arrOfStudents[j].groupNumber > arrOfStudents[j+1].groupNumber)
			{
				temp = arrOfStudents[j];
				arrOfStudents[j] = arrOfStudents[j+1];
				arrOfStudents[j+1] = temp;
			}

	fPtr = fopen(filename, "wb");

	for(int i = 0; i < count; i++)
	{
		fseek(fPtr, i * sizeof(struct Student), 0);
		fwrite(&arrOfStudents[i], sizeof(struct Student), 1, fPtr);
	}

	delete arrOfStudents;
}
