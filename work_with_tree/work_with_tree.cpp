#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "tree_lib.cpp"
#pragma warning(disable : 4996) 

int getMenuPointer();
void menu();

int main()
{
	setlocale(LC_ALL, "Rus");

	menu();
	return 0;
}

int getMenuPointer()
{
	int menuPointer;
	
	printf("Выберите действие:\n");
	printf("1. Создание дерева.\n");
	printf("2. Проверка дерева на пустоту.\n");
	printf("3. Добавление узла в дерево.\n");
	printf("4. Поиск заданного узла в дереве.\n");
	printf("5. Удаление из дерева заданного узла.\n");
	printf("6. Удаление из дерева заданного поддерева.\n");
	printf("7. Обход дерева.\n");
	printf("8. Выход.\n");

	scanf("%d", &menuPointer);

	return menuPointer;
}

void menu()
{
	Node* tree = NULL, * ad = NULL, * adr = NULL;
	int menuPointer, num, chooseTraversal;
	char subrtree = NULL;

	menuPointer = getMenuPointer();

	while (true)
	{
		system("cls");

		switch (menuPointer)
		{
		case 1:
			printf("Введите значение корня:\n");
			scanf("%d", &num);
			InitTree(&tree, num);
			break;

		case 2:
			if (NullTree(tree) == true)
				printf("Дерево пустое.\n");
			else
				printf("Дерево не пустое.\n");
			break;

		case 3:
			printf("Введите значение узла:\n");
			scanf("%d", &num);
			AddTree(&tree, num);
			break;

		case 4:
			printf("Укажите узел, который необходимо найти:\n");
			scanf("%d", &num);
			FindTree(tree, num, ad, adr);
			if (ad != NULL)
				if (adr != NULL)
					printf("Узел %d присутствует в дереве.\nРодитель узла %d - узел %d.\n", ad->data, ad->data, adr->data);
				else
					printf("Узел %d присутствует в дереве.\nУзел %d является корнем.\n", ad->data, ad->data);
			else
				printf("Узла %d нет в дереве.\n", num);
			break;

		case 5:
			printf("Укажите узел, который необходимо удалить:\n");
			scanf("%d", &num);
			DelTreeUz(tree, num);
			printf("Узел удалён.\n");
			break;

		case 6:
			printf("Укажите узел, поддерево которого необходимо удалить:\n");
			scanf("%d", &num);
			printf("Укажите, какое поддерево данного узла необходимо удалить:\n L - левое;\n R - правое.\n");
			scanf("%c", &subrtree);
			DelTreeP(tree, num, subrtree);
			printf("Поддерево удалено.\n");
			break;

		case 7:
			printf("Выберите способ обхода:\n");
			printf("1. Префиксный (сверху вниз).\n");
			printf("2. Инфиксный (слева направо).\n");
			printf("3. Постфиксный (снизу вверх).\n");
			printf("4. Сверху вних по уровням.\n");
			printf("5. Снизу вверх по уровням.\n");
			scanf("%d", &chooseTraversal);

			switch (chooseTraversal)
			{
			case 1: 
				ViewTree1(tree);
				break;

			case 2:
				ViewTree2(tree);
				break;

			case 3:
				ViewTree3(tree);
				break;

			case 4:
				ViewTreeByLevel(tree);
				break;
			
			case 5:
				ViewTreeByLevelReversed(tree);
				break;

			default:
				printf("Выбран неизвестный обход.\n");
				break;
			}
			break;

		case 8:
			exit(0);
			break;

		default:
			printf("Выбран неизвестный пункт меню.\n");
			break;
		}

		menuPointer = getMenuPointer();
	}
}