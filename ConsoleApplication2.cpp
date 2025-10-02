#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    char inf[256];
    struct node* next;
};

struct node* head = NULL;
struct node* last = NULL;
char find_el[256];

struct node* get_struct(void);
struct node* find(char* name);
void enqueue(void);  
void dequeue(void); 
void review(void);
void del(char* name);

struct node* get_struct(void)
{
    struct node* p = NULL;
    char s[256];

    if ((p = (struct node*)malloc(sizeof(struct node))) == NULL)
    {
        printf("Ошибка при распределении памяти\n");
        exit(1);
    }

    printf("Введите название объекта: \n");
    scanf("%s", s);
    if (*s == 0)
    {
        printf("Запись не была произведена\n");
        free(p);
        return NULL;
    }
    strcpy(p->inf, s);
    p->next = NULL;

    return p;
}

void enqueue(void)
{
    struct node* p = NULL;
    p = get_struct();

    if (p == NULL) {
        return;
    }

    if (head == NULL)  
    {
        head = p;
        last = p;
    }
    else  
    {
        last->next = p;
        last = p;
    }
    printf("Элемент '%s' добавлен в очередь\n", p->inf);
}

void dequeue(void)
{
    if (head == NULL)
    {
        printf("Очередь пуста\n");
        return;
    }

    struct node* temp = head;

    if (head == last) 
    {
        head = NULL;
        last = NULL;
    }
    else  
    {
        head = head->next;
    }

    printf("Элемент '%s' удален из очереди\n", temp->inf);
    free(temp);
}

void review(void)
{
    struct node* struc = head;
    if (head == NULL)
    {
        printf("Очередь пуста\n");
        return;
    }

    printf("Содержимое очереди (первый - будет удален следующим):\n");
    int position = 1;
    while (struc)
    {
        printf("%d. Имя - %s\n", position, struc->inf);
        struc = struc->next;
        position++;
    }
}

struct node* find(char* name)
{
    struct node* struc = head;
    if (head == NULL)
    {
        printf("Очередь пуста\n");
        return NULL;
    }

    int position = 1;
    while (struc)
    {
        if (strcmp(name, struc->inf) == 0)
        {
            printf("Элемент '%s' найден на позиции %d\n", name, position);
            return struc;
        }
        struc = struc->next;
        position++;
    }

    printf("Элемент '%s' не найден\n", name);
    return NULL;
}

void del(char* name)
{
    struct node* struc = head;
    struct node* prev = NULL;
    int flag = 0;

    if (head == NULL)
    {
        printf("Очередь пуста\n");
        return;
    }

    if (strcmp(name, struc->inf) == 0)
    {
        flag = 1;
        head = struc->next;
        if (head == NULL)
        {
            last = NULL;
        }
        printf("Элемент '%s' удален\n", struc->inf);
        free(struc);
        return;
    }

    prev = struc;
    struc = struc->next;

    while (struc)
    {
        if (strcmp(name, struc->inf) == 0)
        {
            flag = 1;
            prev->next = struc->next;

            if (struc == last) 
            {
                last = prev;
            }

            printf("Элемент '%s' удален\n", struc->inf);
            free(struc);
            return;
        }
        prev = struc;
        struc = struc->next;
    }

    if (flag == 0)
    {
        printf("Элемент '%s' не найден\n", name);
    }
}

void peek(void)
{
    if (head == NULL)
    {
        printf("Очередь пуста\n");
        return;
    }

    printf("Первый элемент в очереди: %s\n", head->inf);
}

void is_empty(void)
{
    if (head == NULL)
    {
        printf("Очередь пуста\n");
    }
    else
    {
        printf("Очередь не пуста\n");
    }
}

void clear_queue(void)
{
    struct node* current = head;
    struct node* next;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }

    head = NULL;
    last = NULL;
    printf("Очередь очищена\n");
}

int main()
{
    system("chcp 1251");
    int choice;
    char name[256];

    printf("Реализация очереди (FIFO)\n");

    while (1)
    {
        printf("\nМеню:\n");
        printf("1. Добавить элемент в очередь \n");
        printf("2. Удалить элемент из очереди \n");
        printf("3. Просмотреть очередь\n");
        printf("4. Найти элемент по имени\n");
        printf("5. Удалить элемент по имени\n");
        printf("6. Показать первый элемент\n");
        printf("7. Проверить пустоту очереди\n");
        printf("8. Очистить очередь\n");
        printf("9. Выход\n");
        printf("Выберите действие: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            enqueue();
            break;
        case 2:
            dequeue();
            break;
        case 3:
            review();
            break;
        case 4:
            printf("Введите имя для поиска: ");
            scanf("%s", name);
            find(name);
            break;
        case 5:
            printf("Введите имя для удаления: ");
            scanf("%s", name);
            del(name);
            break;
        case 6:
            peek();
            break;
        case 7:
            is_empty();
            break;
        case 8:
            clear_queue();
            break;
        case 9:
            clear_queue();
            printf("Выход из программы\n");
            return 0;
        default:
            printf("Неверный выбор\n");
        }
    }

    return 0;
}