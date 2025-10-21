#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int** matrix;
    int vertices;
} GraphMatrix;

GraphMatrix* createGraphMatrix(int vertices) {
    GraphMatrix* graph = (GraphMatrix*)malloc(sizeof(GraphMatrix));
    graph->vertices = vertices;
    graph->matrix = (int**)malloc(vertices * sizeof(int*));

    for (int i = 0; i < vertices; i++) {
        graph->matrix[i] = (int*)calloc(vertices, sizeof(int));
    }
    return graph;
}

void printGraphMatrix(GraphMatrix* graph) {
    printf("Матрица смежности:\n");
    for (int i = 0; i < graph->vertices; i++) {
        for (int j = 0; j < graph->vertices; j++) {
            printf("%d ", graph->matrix[i][j]);
        }
        printf("\n");
    }
}

void addEdgeMatrix(GraphMatrix* graph, int src, int dest) {
    graph->matrix[src - 1][dest - 1] = 1;
    graph->matrix[dest - 1][src - 1] = 1;
}

void identifyVerticesMatrix(GraphMatrix* graph, int v1, int v2) {
    int idx1 = v1 - 1;
    int idx2 = v2 - 1;

    if (v1 == v2 || idx1 >= graph->vertices || idx2 >= graph->vertices || idx1 < 0 || idx2 < 0) {
        printf("Неверные вершины!\n");
        return;
    }

    int newVertices = graph->vertices - 1;
    int** newMatrix = (int**)malloc(newVertices * sizeof(int*));
    for (int i = 0; i < newVertices; i++) {
        newMatrix[i] = (int*)calloc(newVertices, sizeof(int));
    }

    for (int i = 0; i < graph->vertices; i++) {
        for (int j = 0; j < graph->vertices; j++) {
            if (i == idx2 || j == idx2) continue;

            int newI = i;
            int newJ = j;

            if (i > idx2) newI = i - 1;
            if (j > idx2) newJ = j - 1;

            newMatrix[newI][newJ] = graph->matrix[i][j];
        }
    }

    for (int i = 0; i < graph->vertices; i++) {
        if (i != idx1 && i != idx2) {
            int newI = i;
            if (i > idx2) newI = i - 1;

            if (graph->matrix[idx2][i]) {
                newMatrix[idx1][newI] = 1;
                newMatrix[newI][idx1] = 1;
            }
        }
    }

    for (int i = 0; i < graph->vertices; i++) {
        free(graph->matrix[i]);
    }
    free(graph->matrix);

    graph->matrix = newMatrix;
    graph->vertices = newVertices;
}

void contractEdgeMatrix(GraphMatrix* graph, int v1, int v2) {
    int idx1 = v1 - 1;
    int idx2 = v2 - 1;

    if (v1 == v2 || idx1 >= graph->vertices || idx2 >= graph->vertices || idx1 < 0 || idx2 < 0) {
        printf("Неверные вершины!\n");
        return;
    }

    if (graph->matrix[idx1][idx2] == 0) {
        printf("Ребро между вершинами %d и %d не существует!\n", v1, v2);
        return;
    }

    identifyVerticesMatrix(graph, v1, v2);
}

void splitVertexMatrix(GraphMatrix* graph, int v) {
    int idx = v - 1;

    if (idx >= graph->vertices || idx < 0) {
        printf("Неверная вершина!\n");
        return;
    }

    int newVertices = graph->vertices + 1;
    int** newMatrix = (int**)malloc(newVertices * sizeof(int*));
    for (int i = 0; i < newVertices; i++) {
        newMatrix[i] = (int*)calloc(newVertices, sizeof(int));
    }

    for (int i = 0; i < graph->vertices; i++) {
        for (int j = 0; j < graph->vertices; j++) {
            newMatrix[i][j] = graph->matrix[i][j];
        }
    }

    int newVertex = newVertices - 1;

    newMatrix[idx][newVertex] = 1;
    newMatrix[newVertex][idx] = 1;

    for (int i = 0; i < graph->vertices; i++) {
        if (graph->matrix[idx][i] && i != idx) {
            if (i % 2 == 0) {
                newMatrix[newVertex][i] = 1;
                newMatrix[i][newVertex] = 1;
                newMatrix[idx][i] = 0;
                newMatrix[i][idx] = 0;
            }
        }
    }

    for (int i = 0; i < graph->vertices; i++) {
        free(graph->matrix[i]);
    }
    free(graph->matrix);

    graph->matrix = newMatrix;
    graph->vertices = newVertices;
}

void createExampleGraph(GraphMatrix* graph) {
    for (int i = 1; i < graph->vertices; i++) {
        addEdgeMatrix(graph, i, i + 1);
    }
    if (graph->vertices > 1) {
        addEdgeMatrix(graph, 1, graph->vertices);
    }

    if (graph->vertices > 3) {
        addEdgeMatrix(graph, 1, 3);
        addEdgeMatrix(graph, 2, 4);
    }
}

void freeGraphMatrix(GraphMatrix* graph) {
    for (int i = 0; i < graph->vertices; i++) {
        free(graph->matrix[i]);
    }
    free(graph->matrix);
    free(graph);
}

int main() {
    system("chcp 1251");
    int v1, v2, operation;

    printf("=== ОПЕРАЦИИ С ГРАФАМИ (МАТРИЧНАЯ ФОРМА) ===\n");

    printf("Введите количество вершин в графе: ");
    int vertices;
    scanf("%d", &vertices);

    if (vertices <= 0) {
        printf("Количество вершин должно быть положительным!\n");
        return 1;
    }

    GraphMatrix* graph = createGraphMatrix(vertices);
    createExampleGraph(graph);

    printf("\nИсходный граф:\n");
    printGraphMatrix(graph);

    while (1) {
        printf("\nВыберите операцию:\n");
        printf("1 - Отождествление вершин\n");
        printf("2 - Стягивание ребра\n");
        printf("3 - Расщепление вершины\n");
        printf("0 - Выход\n");
        printf("Ваш выбор: ");
        scanf("%d", &operation);

        if (operation == 0) break;

        switch (operation) {
        case 1:
            printf("Введите две вершины для отождествления: ");
            scanf("%d %d", &v1, &v2);
            if (v1 < 1 || v1 > graph->vertices || v2 < 1 || v2 > graph->vertices) {
                printf("Неверные номера вершин! Допустимы от 1 до %d\n", graph->vertices);
            }
            else {
                printf("Отождествление вершин %d и %d \n", v1, v2);
                identifyVerticesMatrix(graph, v1, v2);
                printf("Результат отождествления:\n");
                printGraphMatrix(graph);
            }
            break;

        case 2:
            printf("Введите две вершины для стягивания ребра: ");
            scanf("%d %d", &v1, &v2);
            if (v1 < 1 || v1 > graph->vertices || v2 < 1 || v2 > graph->vertices) {
                printf("Неверные номера вершин! Допустимы от 1 до %d\n", graph->vertices);
            }
            else {
                contractEdgeMatrix(graph, v1, v2);
                printf("Результат стягивания ребра между вершинами %d и %d:\n", v1, v2);
                printGraphMatrix(graph);
            }
            break;

        case 3:
            printf("Введите вершину для расщепления: ");
            scanf("%d", &v1);
            if (v1 < 1 || v1 > graph->vertices) {
                printf("Неверный номер вершины! Допустимы от 1 до %d\n", graph->vertices);
            }
            else {
                splitVertexMatrix(graph, v1);
                printf("Результат расщепления вершины %d:\n", v1);
                printGraphMatrix(graph);
            }
            break;

        default:
            printf("Неверный выбор! Попробуйте снова.\n");
        }
    }

    freeGraphMatrix(graph);
    printf("Программа завершена.\n");

    return 0;
}