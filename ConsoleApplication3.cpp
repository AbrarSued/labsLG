#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    char inf[256];
    struct node* next;
};

struct node* top = NULL;  
char find_el[256];

struct node* get_struct(void);
struct node* find(char* name);
void push(void);      
void pop(void);       
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

void push(void)
{
    struct node* p = NULL;
    p = get_struct();

    if (p == NULL) {
        return;
    }

    if (top == NULL)  
    {
        top = p;
    }
    else  
    {
        p->next = top;
        top = p;
    }
    printf("Элемент '%s' добавлен в стек\n", p->inf);
}

void pop(void)
{
    if (top == NULL)
    {
        printf("Стек пуст\n");
        return;
    }

    struct node* temp = top;
    top = top->next;

    printf("Элемент '%s' удален из стека\n", temp->inf);
    free(temp);
}

void review(void)
{
    struct node* struc = top;
    if (top == NULL)
    {
        printf("Стек пуст\n");
        return;
    }

    printf("Содержимое стека (вершина - будет удалена следующей):\n");
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
    struct node* struc = top;
    if (top == NULL)
    {
        printf("Стек пуст\n");
        return NULL;
    }

    int position = 1;
    while (struc)
    {
        if (strcmp(name, struc->inf) == 0)
        {
            printf("Элемент '%s' найден на позиции %d от вершины\n", name, position);
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
    struct node* struc = top;
    struct node* prev = NULL;
    int flag = 0;

    if (top == NULL)
    {
        printf("Стек пуст\n");
        return;
    }

    if (strcmp(name, struc->inf) == 0)
    {
        flag = 1;
        top = struc->next;
        printf("Элемент '%s' удален из стека\n", struc->inf);
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

            printf("Элемент '%s' удален из стека\n", struc->inf);
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
    if (top == NULL)
    {
        printf("Стек пуст\n");
        return;
    }

    printf("Вершина стека: %s\n", top->inf);
}

void is_empty(void)
{
    if (top == NULL)
    {
        printf("Стек пуст\n");
    }
    else
    {
        printf("Стек не пуст\n");
    }
}

void clear_stack(void)
{
    struct node* current = top;
    struct node* next;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }

    top = NULL;
    printf("Стек очищен\n");
}

void stack_size(void)
{
    struct node* struc = top;
    int count = 0;

    while (struc)
    {
        count++;
        struc = struc->next;
    }

    printf("Количество элементов в стеке: %d\n", count);
}

int main()
{
    system("chcp 1251");
    int choice;
    char name[256];

    printf("Реализация стека (LIFO)\n");

    while (1)
    {
        printf("\nМеню:\n");
        printf("1. Добавить элемент в стек\n");
        printf("2. Удалить элемент из стека\n");
        printf("3. Просмотреть стек\n");
        printf("4. Найти элемент по имени\n");
        printf("5. Удалить элемент по имени\n");
        printf("6. Показать вершину стека\n");
        printf("7. Проверить пустоту стека\n");
        printf("8. Размер стека\n");
        printf("9. Очистить стек\n");
        printf("10. Выход\n");
        printf("Выберите действие: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            push();
            break;
        case 2:
            pop();
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
            stack_size();
            break;
        case 9:
            clear_stack();
            break;
        case 10:
            clear_stack();
            printf("Выход из программы\n");
            return 0;
        default:
            printf("Неверный выбор\n");
        }
    }

    return 0;
}