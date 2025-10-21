#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generateRandomMatrix(int** matrix, int vertices) {
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            if (i == j) {
                matrix[i][j] = 0;
            }
            else if (i < j) {
                matrix[i][j] = rand() % 2;
            }
            else {
                matrix[i][j] = matrix[j][i];
            }
        }
    }
}

void printMatrix(int** matrix, int vertices, const char* title) {
    printf("\n%s:\n", title);
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void unionGraphs(int** G1, int n1, int** G2, int n2, int** result, int max_vertices) {
    for (int i = 0; i < max_vertices; i++) {
        for (int j = 0; j < max_vertices; j++) {
            int val1 = (i < n1 && j < n1) ? G1[i][j] : 0;
            int val2 = (i < n2 && j < n2) ? G2[i][j] : 0;
            result[i][j] = val1 || val2;
        }
    }
}

void intersectionGraphs(int** G1, int n1, int** G2, int n2, int** result, int max_vertices) {
    for (int i = 0; i < max_vertices; i++) {
        for (int j = 0; j < max_vertices; j++) {
            int val1 = (i < n1 && j < n1) ? G1[i][j] : 0;
            int val2 = (i < n2 && j < n2) ? G2[i][j] : 0;
            result[i][j] = val1 && val2;
        }
    }
}

void ringSumGraphs(int** G1, int n1, int** G2, int n2, int** result, int max_vertices) {
    for (int i = 0; i < max_vertices; i++) {
        for (int j = 0; j < max_vertices; j++) {
            int val1 = (i < n1 && j < n1) ? G1[i][j] : 0;
            int val2 = (i < n2 && j < n2) ? G2[i][j] : 0;
            result[i][j] = val1 ^ val2;
        }
    }
}

int** allocateMatrix(int vertices) {
    int** matrix = (int**)malloc(vertices * sizeof(int*));
    for (int i = 0; i < vertices; i++) {
        matrix[i] = (int*)calloc(vertices, sizeof(int));
    }
    return matrix;
}

void freeMatrix(int** matrix, int vertices) {
    for (int i = 0; i < vertices; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int main() {
    system("chcp 1251");
    int n1, n2;

    printf("Введите количество вершин графа G1: ");
    scanf("%d", &n1);
    printf("Введите количество вершин графа G2: ");
    scanf("%d", &n2);

    if (n1 <= 0) {
        printf("Ошибка: количество вершин должно быть положительным числом.\n");
        return 1;
    }
    if (n2 <= 0) {
        printf("Ошибка: количество вершин должно быть положительным числом.\n");
        return 1;
    }

    srand(time(NULL));

    int max_vertices = (n1 > n2) ? n1 : n2;

    int** G1 = allocateMatrix(n1);
    int** G2 = allocateMatrix(n2);
    int** result = allocateMatrix(max_vertices);

    generateRandomMatrix(G1, n1);
    generateRandomMatrix(G2, n2);

    printMatrix(G1, n1, "Граф G1");
    printMatrix(G2, n2, "Граф G2");

    unionGraphs(G1, n1, G2, n2, result, max_vertices);
    printMatrix(result, max_vertices, "Объединение G1 и G2");

    intersectionGraphs(G1, n1, G2, n2, result, max_vertices);
    printMatrix(result, max_vertices, "Пересечение G1 и G2");

    ringSumGraphs(G1, n1, G2, n2, result, max_vertices);
    printMatrix(result, max_vertices, "Кольцевая сумма G1 и G2");

    freeMatrix(G1, n1);
    freeMatrix(G2, n2);
    freeMatrix(result, max_vertices);

    return 0;
}