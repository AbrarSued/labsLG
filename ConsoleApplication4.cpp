#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int** createMatrix(int rows, int cols) {
    int** matrix = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(cols * sizeof(int));
    }
    return matrix;
}

void freeMatrix(int** matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

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

void printMatrix(int** matrix, int rows, int cols, const char* name) {
    printf("\nМатрица %s (%dx%d):\n", name, rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int** cartesianProduct(int** G1, int n1, int** G2, int n2) {
    int resultSize = n1 * n2;
    int** result = createMatrix(resultSize, resultSize);

    for (int i = 0; i < resultSize; i++) {
        for (int j = 0; j < resultSize; j++) {
            result[i][j] = 0;
        }
    }

    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < n2; j++) {
            for (int k = 0; k < n1; k++) {
                for (int l = 0; l < n2; l++) {
                    int row = i * n2 + j;
                    int col = k * n2 + l;

                    if (i == k && G2[j][l] == 1) {
                        result[row][col] = 1;
                    }
                    else if (j == l && G1[i][k] == 1) {
                        result[row][col] = 1;
                    }
                }
            }
        }
    }
    return result;
}

void printCartesianVertices(int n1, int n2) {
    printf("\nВершины декартова произведения G1 X G2:\n");
    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < n2; j++) {
            printf("(%d,%d) ", i, j);
        }
    }
    printf("\n");
}

int main() {
    system("chcp 1251");
    srand(time(NULL)); 

    int n1, n2;

    printf("=== Декартово произведение графов G1 X G2 ===\n\n");

    printf("Введите количество вершин графа G1: ");
    scanf("%d", &n1);
    printf("Введите количество вершин графа G2: ");
    scanf("%d", &n2);

    int** G1 = createMatrix(n1, n1);
    int** G2 = createMatrix(n2, n2);

    generateRandomMatrix(G1, n1);
    generateRandomMatrix(G2, n2);

    printMatrix(G1, n1, n1, "G1");
    printMatrix(G2, n2, n2, "G2");

    int** result = cartesianProduct(G1, n1, G2, n2);
    int resultSize = n1 * n2;

    printCartesianVertices(n1, n2);

    printMatrix(result, resultSize, resultSize, "G1 X G2 (декартово произведение)");

    freeMatrix(G1, n1);
    freeMatrix(G2, n2);
    freeMatrix(result, resultSize);

    return 0;
}