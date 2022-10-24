// katya3laba.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include <stdio.h> // ���������
#include <stdlib.h>  // ���������
#include <string.h> // ���������
#include <locale.h>


struct node
{
	char inf[256];  // �������� ����������
    int priority;     // ���������
	struct node *next; // ������ �� ��������� ������� 
};

// ��������� � ������ � ��� ��������� �������������� ����������� ����������:

struct node *head = NULL, *last = NULL, *f = NULL; // ��������� �� ������ � ��������� �������� ������
int dlinna = 0;

// ��� ������ ����������� ������� ��������, ����������, �������� ��������, ��������� ������, ���������� ������� �������� ������:

// ������� ���������� ��������, ��������� ������
void spstore(void), review(void), del(char *name);

char find_el[256];
struct node *find(char *name); // ������� ���������� ��������
struct node *get_struct(void); // ������� �������� ��������


struct node *get_struct(void)
{
	struct node *p = NULL;
	char s[256];

	if ((p = (node*)malloc(sizeof(struct node))) == NULL)  // �������� ������ ��� ����� ������� ������
	{
		printf("������ ��� ������������� ������\n");
		exit(1);
	}

	printf("������� �������� �������: \n");   // ������ ������
	scanf("%s", s);
	if (*s == 0)
	{
		printf("������ �� ���� �����������\n");
		return NULL;
	}
	strcpy(p->inf, s);


	printf("������� ��� �������: \n");   // ������ ������
	scanf("%s", s);
	if (*s == 0)
	{
		printf("������ �� ���� �����������\n");
		return NULL;
	}
        p->priority = atoi(s);

	p->next = NULL;

	return p;		// ���������� ��������� �� ��������� �������
}

/* ���������������� ���������� � ������ �������� */
// ��������
void spstore(void)
{
	struct node *p = NULL;
	p = get_struct();
	if (head == NULL && p != NULL)	// ���� ������ ���, �� ������������� ������ ������
	{
		head = p;
		last = p;
	}
	else if (head != NULL && p != NULL) // ������ ��� ����, �� ���� ���� ��������
	{
        	node* current = head;
                node* prev = NULL;
                  
                while (current != NULL && current->priority >= p->priority) {
                   prev = current; 
                   current = current->next; // ��������� �� �������� ������ �������
		}

                if (prev == NULL) { // ����� ������� - � ����� ������� �����, ��������� � ������
		   // ���� ��������� ������ �������� ��������� � ������, �� ��������� ������� ����� ������ � ���������
                   if (p->priority == head->priority) {
 	                    p->next = head->next;
 	                    head->next = p;
                   } else { // ������ ��������� ������ - ����� �������, ��������� � ������
  			   p->next = head;
  	                   head = p;
                  }
                } else if (current == NULL) { // ����� ������� - � ����� ��������� �����, ��������� � �����
                    prev->next = p; // prev = last, last->next = p
                    last = p;	
                } else { // ��������� ������� ����� prev � current
                    p->next = prev->next;
		    prev->next = p;
                }
	}
	return;
}


/* �������� ����������� ������. */
void review(void)
{
	struct node *struc = head;
	if (head == NULL)
	{
		printf("������ ����\n");
	}
	while (struc)
	{
		printf("��� - %s, ��� = %i \n", struc->inf, struc->priority);
		struc = struc->next;
	}
	return;
}


/* ��������� �������� ������� �� ������ */
// ���������
node* dequeue() {
  node* struc = head;
  
  if (head != NULL) {
    struc = head;
    head = head->next;
  }

  return struc;
}


/* ����� �������� �� �����������. */
void find()
{
	char name[256];
	printf("������� ��� ��� ������: ");
	getchar();
	gets(name);
	struct node *struc = head;
	if (head == NULL)
	{
		printf("������ ����\n");
	}
	while (struc)
	{
		if (strcmp(name, struc->inf) == 0)
		{
			printf("������� �������: ��� - %s, ��� = %i \n", struc->inf, struc->priority);
			return;
		}
		struc = struc->next;
	}
	printf("������� �� ������\n");
}

/* �������� �������� �� �����������. */
void del(char *name)
{
	struct node *struc = head; // ���������, ���������� �� ������ ���������� �� ������ ������
	struct node *prev;// ��������� �� �������������� ���������� �������
	int flag = 0;      // ��������� ���������� ���������� �������� � ������

	if (head == NULL) // ���� ������ ������ ����� NULL, �� ������ ����
	{
		printf("������ ����\n");
		return;
	}

	if (strcmp(name, struc->inf) == 0) // ���� ��������� ������� - ������
	{
		flag = 1;
		head = struc->next; // ������������� ������ �� ��������� �������
		free(struc);  // ������� ������ �������
		struc = head; // ������������� ��������� ��� ����������� ������
	}
	else
	{
		prev = struc;
		struc = struc->next;
	}

	while (struc) // ������ �� ������ � ����� ���������� ��������
	{
		if (strcmp(name, struc->inf) == 0) // ���� �����, ��
		{
			flag = 1;         // ���������� ���������
			if (struc->next)  // ���� ��������� ������� �� ��������� � ������
			{
				prev->next = struc->next; // ������ ���������
				free(struc);		    // �������  �������
				struc = prev->next; // ������������� ��������� ��� ����������� ������
			}
			else			// ���� ��������� ������� ��������� � ������
			{
				prev->next = NULL; // �������� ��������� ��������������� ��������
				free(struc);	// �������  �������
				return;
			}
		}
		else	// ���� �� �����, ��
		{
			prev = struc; // ������������� ��������� ��� ����������� ������
			struc = struc->next;
		}
	}

	if (flag == 0)				// ���� ���� = 0, ������ ������ ������� �� ������
	{
		printf("������� �� ������\n");
		return;
	}


}

// ��������� - �������� ����� ������� ���������
int main() {
	setlocale(LC_ALL, "Russian");
	system("chcp 1251");
    // ���������� �������
    for (int cx=1; cx <= 3; cx++){
		spstore(); 
	}
	find();
    // ����� ������� �� �����
 	node* struc;
    while ((struc = dequeue()) != NULL) {
  	   printf("��� - %s, ��� - %i \n", struc->inf, struc->priority);
       free(struc);
    }

	system("pause");
	return 0;
}