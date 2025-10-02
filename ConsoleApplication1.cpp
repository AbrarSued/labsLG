#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    char inf[256];
    int priority;
    struct node* next;
};

struct node* head = NULL;
struct node* last = NULL;
char find_el[256];

struct node* get_struct(void);
struct node* find_by_name(char* name);
struct node* find_by_priority(int priority);
void find_menu(void);
void spstore(void);
void review(void);
void del_by_name(char* name);
void del_by_priority(int priority);
void del_menu(void);
struct node* dequeue(void);
void free_list(void);
int get_positive_priority(void);
void change_priority_by_name(char* name);

int get_positive_priority(void)
{
    int priority;
    while (1) {
        printf("Введите приоритет объекта : \n");
        if (scanf("%d", &priority) != 1) {
            printf("Ошибка ввода. Введите целое число.\n");
            while (getchar() != '\n');
            continue;
        }

        if (priority <= 0) {
            printf("Ошибка. Приоритет должен быть больше 0. Попробуйте снова.\n");
        }
        else {
            break;
        }
    }
    return priority;
}

struct node* get_struct(void)
{
    struct node* p = NULL;
    char s[256];
    int priority;

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

    priority = get_positive_priority();

    strcpy(p->inf, s);
    p->priority = priority;
    p->next = NULL;

    return p;
}

void spstore(void)
{
    struct node* p = NULL;
    struct node* current = NULL;
    struct node* prev = NULL;

    p = get_struct();
    if (p == NULL) {
        return;
    }

    if (head == NULL)
    {
        head = p;
        last = p;
        return;
    }

    current = head;
    prev = NULL;

    while (current != NULL && current->priority <= p->priority)
    {
        prev = current;
        current = current->next;
    }

    if (prev == NULL)
    {
        p->next = head;
        head = p;
    }
    else
    {
        prev->next = p;
        p->next = current;

        if (current == NULL)
        {
            last = p;
        }
    }
}

void review(void)
{
    struct node* struc = head;
    if (head == NULL)
    {
        printf("Список пуст\n");
        return;
    }

    printf("Содержимое списка:\n");
    while (struc)
    {
        printf("Имя - %s, Приоритет - %d\n", struc->inf, struc->priority);
        struc = struc->next;
    }
}

struct node* find_by_name(char* name)
{
    struct node* struc = head;
    if (head == NULL)
    {
        printf("Список пуст\n");
        return NULL;
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

struct node* find_by_priority(int priority)
{
    struct node* struc = head;
    struct node* found = NULL;
    int count = 0;

    if (head == NULL)
    {
        printf("Список пуст\n");
        return NULL;
    }

    printf("Найденные элементы с приоритетом %d:\n", priority);
    while (struc)
    {
        if (struc->priority == priority)
        {
            printf("Имя - %s, Приоритет - %d\n", struc->inf, struc->priority);
            found = struc;
            count++;
        }
        struc = struc->next;
    }

    if (count == 0)
    {
        printf("Элементы с приоритетом %d не найдены\n", priority);
        return NULL;
    }

    return found;
}

void find_menu(void)
{
    int choice;
    char name[256];
    int priority;

    printf("\nПоиск элементов:\n");
    printf("1. Поиск по имени\n");
    printf("2. Поиск по приоритету\n");
    printf("Выберите тип поиска: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
        printf("Введите имя для поиска: ");
        scanf("%s", name);
        find_by_name(name);
        break;
    case 2:
        printf("Введите приоритет для поиска: ");
        scanf("%d", &priority);
        find_by_priority(priority);
        break;
    default:
        printf("Неверный выбор\n");
    }
}

void del_by_name(char* name)
{
    struct node* struc = head;
    struct node* prev = NULL;
    int flag = 0;

    if (head == NULL)
    {
        printf("Список пуст\n");
        return;
    }

    while (struc != NULL)
    {
        if (strcmp(name, struc->inf) == 0)
        {
            flag = 1;

            if (prev == NULL)
            {
                head = struc->next;
                if (head == NULL)
                {
                    last = NULL;
                }
                printf("Удален: %s с приоритетом %d\n", struc->inf, struc->priority);
                free(struc);
                struc = head;
            }
            else
            {
                prev->next = struc->next;
                if (struc->next == NULL)
                {
                    last = prev;
                }
                printf("Удален: %s с приоритетом %d\n", struc->inf, struc->priority);
                free(struc);
                struc = prev->next;
            }
        }
        else
        {
            prev = struc;
            struc = struc->next;
        }
    }

    if (flag == 0)
    {
        printf("Элемент не найден\n");
    }
}

void del_by_priority(int priority)
{
    struct node* struc = head;
    struct node* prev = NULL;
    struct node* to_delete = NULL;
    int flag = 0;

    if (head == NULL)
    {
        printf("Список пуст\n");
        return;
    }

    while (struc != NULL)
    {
        if (struc->priority == priority)
        {
            flag = 1;

            if (prev == NULL)
            {
                head = struc->next;
                if (head == NULL)
                {
                    last = NULL;
                }
                printf("Удален: %s с приоритетом %d\n", struc->inf, struc->priority);
                free(struc);
                struc = head;
            }
            else
            {
                prev->next = struc->next;
                if (struc->next == NULL)
                {
                    last = prev;
                }
                printf("Удален: %s с приоритетом %d\n", struc->inf, struc->priority);
                free(struc);
                struc = prev->next;
            }
        }
        else
        {
            prev = struc;
            struc = struc->next;
        }
    }

    if (flag == 0)
    {
        printf("Элементы с приоритетом %d не найдены\n", priority);
    }
    else
    {
        printf("Удалены все элементы с приоритетом %d\n", priority);
    }
}

void del_menu(void)
{
    int choice;
    char name[256];
    int priority;

    printf("\nУдаление элементов:\n");
    printf("1. Удаление по имени\n");
    printf("2. Удаление по приоритету\n");
    printf("Выберите тип удаления: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
        printf("Введите имя для удаления: ");
        scanf("%s", name);
        del_by_name(name);
        break;
    case 2:
        printf("Введите приоритет для удаления: ");
        scanf("%d", &priority);
        del_by_priority(priority);
        break;
    default:
        printf("Неверный выбор\n");
    }
}

struct node* dequeue(void)
{
    if (head == NULL) {
        printf("Очередь пуста\n");
        return NULL;
    }

    struct node* temp = head;
    head = head->next;

    if (head == NULL) {
        last = NULL;
    }

    temp->next = NULL;
    return temp;
}

void free_list(void)
{
    struct node* current = head;
    struct node* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    head = NULL;
    last = NULL;
}

void change_priority(char* name)
{
    struct node* struc = head;
    int found = 0;
    int new_priority;

    if (head == NULL)
    {
        printf("Список пуст\n");
        return;
    }

    while (struc != NULL)
    {
        if (strcmp(name, struc->inf) == 0)
        {
            found = 1;
            printf("Найден элемент: %s с приоритетом %d\n", struc->inf, struc->priority);
            printf("Введите новый приоритет: ");
            new_priority = get_positive_priority();

            char temp_name[256];
            int old_priority = struc->priority;
            strcpy(temp_name, struc->inf);

            del_by_name(name);

            struct node* new_node = (struct node*)malloc(sizeof(struct node));
            if (new_node == NULL) {
                printf("Ошибка при распределении памяти\n");
                return;
            }

            strcpy(new_node->inf, temp_name);
            new_node->priority = new_priority;
            new_node->next = NULL;

            struct node* current = head;
            struct node* prev = NULL;

            while (current != NULL && current->priority <= new_priority)
            {
                prev = current;
                current = current->next;
            }

            if (prev == NULL)
            {
                new_node->next = head;
                head = new_node;
            }
            else
            {
                prev->next = new_node;
                new_node->next = current;

                if (current == NULL)
                {
                    last = new_node;
                }
            }

            printf("Приоритет элемента '%s' изменен с %d на %d\n", temp_name, old_priority, new_priority);
            break; 
        }
        struc = struc->next;
    }

    if (!found)
    {
        printf("Элемент с именем '%s' не найден\n", name);
    }
}

int main()
{
    system("chcp 1251");
    int choice;
    struct node* temp;
    char name[256];

    printf("Приоритетная очередь (чем МЕНЬШЕ число приоритета - тем ВЫШЕ приоритет)\n");

    while (1) {
        printf("\nМеню:\n");
        printf("1. Добавить элемент\n");
        printf("2. Просмотреть все элементы\n");
        printf("3. Найти элемент\n");
        printf("4. Удалить элемент\n");
        printf("5. Извлечь элемент с высшим приоритетом\n");
        printf("6. Изменить приоритет элемента\n");
        printf("7. Выход\n");
        printf("Выберите действие: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            spstore();
            break;
        case 2:
            review();
            break;
        case 3:
            find_menu();
            break;
        case 4:
            del_menu();
            break;
        case 5:
            temp = dequeue();
            if (temp != NULL) {
                printf("Извлечен: %s с приоритетом %d\n", temp->inf, temp->priority);
                free(temp);
            }
            break;
        case 6:
            printf("Введите имя элемента для изменения приоритета: ");
            scanf("%s", name);
            change_priority(name);
            break;
        case 7:
            free_list();
            printf("Выход...\n");
            return 0;
        default:
            printf("Неверный выбор\n");
        }
    }

    return 0;
}