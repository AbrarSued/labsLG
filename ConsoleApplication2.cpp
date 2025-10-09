#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* CreateTree(struct Node* root, int data) {
    if (root == NULL) {
        root = (struct Node*)malloc(sizeof(struct Node));
        if (root == NULL) {
            printf("Ошибка выделения памяти");
            exit(0);
        }
        root->left = NULL;
        root->right = NULL;
        root->data = data;
        return root;
    }

    if (data < root->data) {
        root->left = CreateTree(root->left, data);
    }
    else {
        root->right = CreateTree(root->right, data);
    }

    return root;
}

struct Node* SearchTree(struct Node* root, int value) {
    if (root == NULL) {
        return NULL;
    }

    if (root->data == value) {
        return root;
    }
    else if (value < root->data) {
        return SearchTree(root->left, value);
    }
    else {
        return SearchTree(root->right, value);
    }
}

int count_occurrences(struct Node* root, int value) {
    if (root == NULL) {
        return 0;
    }

    int count = 0;

    if (root->data == value) {
        count = 1;
    }

    if (value < root->data) {
        count += count_occurrences(root->left, value);
    }
    else {
        count += count_occurrences(root->right, value);
    }

    return count;
}

void print_tree_with_levels(struct Node* r, int l, int current_level) {
    if (r == NULL) {
        return;
    }
    print_tree_with_levels(r->right, l + 1, current_level + 1);
    for (int i = 0; i < l; i++) {
        printf("   ");
    }
    printf("%d (у %d)\n", r->data, current_level);
    print_tree_with_levels(r->left, l + 1, current_level + 1);
}

void print_tree(struct Node* r, int l) {
    print_tree_with_levels(r, l, 1);
}

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

struct Node* input_tree() {
    struct Node* root = NULL;
    int n, value;

    printf("Введите количество элементов в дереве: ");
    scanf("%d", &n);
    clear_input_buffer();

    printf("Введите %d элементов:\n", n);
    for (int i = 0; i < n; i++) {
        printf("Элемент %d: ", i + 1);
        if (scanf("%d", &value) == 1) {
            root = CreateTree(root, value);
            clear_input_buffer();
        }
        else {
            printf("Ошибка ввода! Пожалуйста, введите целое число.\n");
            clear_input_buffer();
            i--;
        }
    }

    printf("Дерево успешно создано!\n");
    return root;
}

void add_elements(struct Node** root) {
    int n, value;

    printf("Введите количество элементов для добавления: ");
    scanf("%d", &n);
    clear_input_buffer();

    printf("Введите %d элементов для добавления:\n", n);
    for (int i = 0; i < n; i++) {
        printf("Элемент %d: ", i + 1);
        if (scanf("%d", &value) == 1) {
            *root = CreateTree(*root, value);
            clear_input_buffer();
        }
        else {
            printf("Ошибка ввода! Пожалуйста, введите целое число.\n");
            clear_input_buffer();
            i--;
        }
    }

    printf("Элементы успешно добавлены!\n");
}

void free_tree(struct Node* root) {
    if (root == NULL) {
        return;
    }
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

void display_menu() {
    printf("\n=== МЕНЮ ===\n");
    printf("1 - Выполнить поиск\n");
    printf("2 - Добавить новые элементы\n");
    printf("3 - Выйти из программы\n");
    printf("Выберите действие: ");
}

int main() {
    system("chcp 1251");
    struct Node* root = NULL;
    int search_value;
    struct Node* result;
    char choice;

    printf("=== СОЗДАНИЕ ДЕРЕВА ===\n");
    root = input_tree();

    printf("\nДерево создано:\n");
    print_tree(root, 0);

    do {
        display_menu();
        scanf(" %c", &choice);
        clear_input_buffer();

        switch (choice) {
        case '1': {
            printf("\nВведите значение для поиска: ");
            if (scanf("%d", &search_value) == 1) {
                clear_input_buffer();
                result = SearchTree(root, search_value);

                if (result != NULL) {
                    printf("Значение %d найдено в дереве!\n", search_value);
                    int count = count_occurrences(root, search_value);
                    printf("Количество вхождений %d в дереве: %d\n", search_value, count);
                }
                else {
                    printf("Значение %d не найдено в дереве.\n", search_value);
                    printf("Количество вхождений %d в дереве: 0\n", search_value);
                }
            }
            else {
                printf("Ошибка ввода! Пожалуйста, введите целое число.\n");
                clear_input_buffer();
            }
            break;
        }
        case '2': {
            add_elements(&root);
            printf("\nОбновленное дерево:\n");
            print_tree(root, 0);
            break;
        }
        case '3': {
            printf("Программа завершена.\n");
            break;
        }
        default: {
            printf("Неверный выбор! Попробуйте снова.\n");
            break;
        }
        }

    } while (choice != '3');

    free_tree(root);

    return 0;
}