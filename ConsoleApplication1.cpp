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

void print_tree(struct Node* r, int l) {
    if (r == NULL) {
        return;
    }
    print_tree(r->right, l + 1);
    for (int i = 0; i < l; i++) {
        printf("   ");
    }
    printf("%d\n", r->data);
    print_tree(r->left, l + 1);
}

struct Node* input_tree() {
    struct Node* root = NULL;
    int n, value;

    printf("Введите количество элементов в дереве: ");
    scanf("%d", &n);

    printf("Введите %d элементов:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &value);
        root = CreateTree(root, value);
    }

    return root;
}

void free_tree(struct Node* root) {
    if (root == NULL) {
        return;
    }
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

int main() {
    system("chcp 1251");
    struct Node* root = NULL;
    int search_value;
    struct Node* result;
    char choice;

    root = input_tree();

    printf("\nДерево:\n");
    print_tree(root, 0);

    do {
        printf("\nВведите значение для поиска: ");
        scanf("%d", &search_value);

        result = SearchTree(root, search_value);

        if (result != NULL) {
            printf("Значение %d найдено в дереве!\n", search_value);
        }
        else {
            printf("Значение %d не найдено в дереве.\n", search_value);
        }

        printf("Хотите выполнить еще один поиск? : \n");
        printf("1 - да\n");
        printf("2 - нет \n");
        scanf(" %c", &choice);

    } while (choice == '1');

    printf("Программа завершена.\n");

    free_tree(root);

    return 0;
}