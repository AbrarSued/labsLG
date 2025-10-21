#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Node {
    int vertex;
    struct Node* next;
};

struct Node* createNode(int v) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

void generateAdjacencyMatrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (i == j) {
                matrix[i][j] = 0;
            }
            else {
                int value = rand() % 2;
                matrix[i][j] = value;
                matrix[j][i] = value;
            }
        }
    }
}

void printMatrix(int** matrix, int n) {
    printf("    ");
    for (int i = 0; i < n; i++) {
        printf("%2d ", i + 1); 
    }
    printf("\n");

    for (int i = 0; i < n; i++) {
        printf("%2d: ", i + 1); 
        for (int j = 0; j < n; j++) {
            printf("%2d ", matrix[i][j]);
        }
        printf("\n");
    }
}


struct Node** matrixToList(int** matrix, int n) {
    struct Node** adjList = (struct Node**)malloc(n * sizeof(struct Node*));

    for (int i = 0; i < n; i++) {
        adjList[i] = NULL;
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == 1 && i != j) { 
                struct Node* newNode = createNode(j + 1); 
                newNode->next = adjList[i];
                adjList[i] = newNode;
            }
        }
    }

    return adjList;
}


void printAdjacencyList(struct Node** adjList, int n) {
    for (int i = 0; i < n; i++) {
        printf(" %d: ", i + 1);
        struct Node* temp = adjList[i];
        while (temp != NULL) {
            printf("%d ", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

void freeMatrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void freeAdjacencyList(struct Node** adjList, int n) {
    for (int i = 0; i < n; i++) {
        struct Node* temp = adjList[i];
        while (temp != NULL) {
            struct Node* toDelete = temp;
            temp = temp->next;
            free(toDelete);
        }
    }
    free(adjList);
}

int main() {
    system("chcp 1251");
    srand(time(NULL));

    int n;
    printf("Введите количество вершин в графах: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Количество вершин должно быть положительным числом.\n");
        return 1;
    }

    int** M1 = (int**)malloc(n * sizeof(int*));
    int** M2 = (int**)malloc(n * sizeof(int*));

    for (int i = 0; i < n; i++) {
        M1[i] = (int*)malloc(n * sizeof(int));
        M2[i] = (int*)malloc(n * sizeof(int));
    }

    printf("\n=== ГЕНЕРАЦИЯ МАТРИЦ СМЕЖНОСТИ ===\n");

    printf("\nМатрица смежности M1 (граф G1):\n");
    generateAdjacencyMatrix(M1, n);
    printMatrix(M1, n);

    printf("\nМатрица смежности M2 (граф G2):\n");
    generateAdjacencyMatrix(M2, n);
    printMatrix(M2, n);

    printf("\n=== ПРЕОБРАЗОВАНИЕ В СПИСКИ СМЕЖНОСТИ ===\n");

    struct Node** adjList1 = matrixToList(M1, n);
    struct Node** adjList2 = matrixToList(M2, n);

    printf("\nСписок смежности для графа G1:\n");
    printAdjacencyList(adjList1, n);

    printf("\nСписок смежности для графа G2:\n");
    printAdjacencyList(adjList2, n);

    freeMatrix(M1, n);
    freeMatrix(M2, n);
    freeAdjacencyList(adjList1, n);
    freeAdjacencyList(adjList2, n);

    return 0;
}