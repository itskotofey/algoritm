#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> // ДОБАВЛЕНО
#include <stdlib.h>  // ДОБАВЛЕНО
#include <string.h> // ДОБАВЛЕНО

struct node
{
	char inf[256];  // полезная информация
	struct node *next; // ссылка на следующий элемент 
};

// Обращение к списку и его элементам осуществляется посредством указателей:

struct node *head = NULL, *last = NULL, *f = NULL; // указатели на первый и последний элементы списка
int dlinna = 0;

// Для списка реализованы функции создания, добавления, удаления элемента, просмотра списка, нахождения нужного элемента списка:

// Функции добавления элемента, просмотра списка
void spstore(void), review(void), del(char *name);

char find_el[256];
struct node *find(char *name); // функция нахождения элемента
struct node *get_struct(void); // функция создания элемента



struct node *get_struct(void)
{
	struct node *p = NULL;
	char s[256];

	if ((p = (node*)malloc(sizeof(struct node))) == NULL)  // выделяем память под новый элемент списка
	{
		printf("Ошибка при распределении памяти\n");
		exit(1);
	}

	printf("Введите название объекта: \n");   // вводим данные
	scanf("%s", s);
	if (*s == 0)
	{
		printf("Запись не была произведена\n");
		return NULL;
	}
	strcpy(p->inf, s);

	p->next = NULL;

	return p;		// возвращаем указатель на созданный элемент
}

/* Последовательное добавление в список элемента (в начало)*/
// ИЗМЕНЕНО
void spstore(void)
{
	struct node *p = NULL;
	p = get_struct();
	if (head == NULL && p != NULL)	// если списка нет, то устанавливаем голову списка
	{
		head = p;
		last = p;
	}
	else if (head != NULL && p != NULL) // список уже есть, то вставляем в начало
	{
                p->next = head;
		head = p;
	}
	return;
}

/* Удаляем элемент из головы списка (с вершины стека) */
// ДОБАВЛЕНО
node* del() {
  node* struc = head;
  
  if (struc != NULL) {
    head = struc->next;
  }

  return struc;
}

/* Просмотр содержимого списка. */
void review(void)
{
	struct node *struc = head;
	if (head == NULL)
	{
		printf("Список пуст\n");
	}
	while (struc)
	{
		printf("Имя - %s, \n", struc->inf);
		struc = struc->next;
	}
	return;
}




/* Поиск элемента по содержимому. */
struct node *find(char *name)
{
	struct node *struc = head;
	if (head == NULL)
	{
		printf("Список пуст\n");
	}
	while (struc)
	{
		if (strcmp(name, struc->inf) == 0)
		{
			return struc;
		}
		struc = struc->next;
	}
	printf("Элемент не найден\n");
	return NULL;
}

/* Удаление элемента по содержимому. */
void del(char *name)
{
	struct node *struc = head; // указатель, проходящий по списку установлен на начало списка
	struct node *prev;// указатель на предшествующий удаляемому элемент
	int flag = 0;      // индикатор отсутствия удаляемого элемента в списке

	if (head == NULL) // если голова списка равна NULL, то список пуст
	{
		printf("Список пуст\n");
		return;
	}

	if (strcmp(name, struc->inf) == 0) // если удаляемый элемент - первый
	{
		flag = 1;
		head = struc->next; // установливаем голову на следующий элемент
		free(struc);  // удаляем первый элемент
		struc = head; // устанавливаем указатель для продолжения поиска
	}
	else
	{
		prev = struc;
		struc = struc->next;
	}

	while (struc) // проход по списку и поиск удаляемого элемента
	{
		if (strcmp(name, struc->inf) == 0) // если нашли, то
		{
			flag = 1;         // выставляем индикатор
			if (struc->next)  // если найденный элемент не последний в списке
			{
				prev->next = struc->next; // меняем указатели
				free(struc);		    // удаляем  элемент
				struc = prev->next; // устанавливаем указатель для продолжения поиска
			}
			else			// если найденный элемент последний в списке
			{
				prev->next = NULL; // обнуляем указатель предшествующего элемента
				free(struc);	// удаляем  элемент
				return;
			}
		}
		else	// если не нашли, то
		{
			prev = struc; // устанавливаем указатели для продолжения поиска
			struc = struc->next;
		}
	}

	if (flag == 0)				// если флаг = 0, значит нужный элемент не найден
	{
		printf("Элемент не найден\n");
		return;
	}


}

// ДОБАВЛЕНО - основная точка запуска программы
int main() {
        // Заполнение стека
        for (int cx=1; cx <= 3; cx++) {
	     spstore(); 
	}
	
	// Вывод элементов стека на экран
	node *struc;
        while ((struc = del()) != NULL)  {
       		printf("Имя - %s, \n", struc->inf);
                free(struc);
        }

	return 0;
}
