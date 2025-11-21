#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

struct Node {
    int vertex;
    struct Node* next;
};

void addEdgeSorted(struct Node** adjList, int src, int dest) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = dest;
    newNode->next = NULL;

    if (adjList[src] == NULL || dest < adjList[src]->vertex) {
        newNode->next = adjList[src];
        adjList[src] = newNode;
    }
    else {
        struct Node* current = adjList[src];
        while (current->next != NULL && current->next->vertex < dest) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }

    newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = src;
    newNode->next = NULL;

    if (adjList[dest] == NULL || src < adjList[dest]->vertex) {
        newNode->next = adjList[dest];
        adjList[dest] = newNode;
    }
    else {
        struct Node* current = adjList[dest];
        while (current->next != NULL && current->next->vertex < src) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

void DFS_matrix(int** G, int numG, int* visited, int s) {
    visited[s] = 1;
    printf("%3d", s);

    for (int i = 0; i < numG; i++) {
        if (G[s][i] == 1 && visited[i] == 0)
            DFS_matrix(G, numG, visited, i);
    }
}

void DFS_list(struct Node** adjList, int numG, int* visited, int s) {
    visited[s] = 1;
    printf("%3d", s);

    struct Node* temp = adjList[s];
    while (temp != NULL) {
        int adjacentVertex = temp->vertex;
        if (visited[adjacentVertex] == 0) {
            DFS_list(adjList, numG, visited, adjacentVertex);
        }
        temp = temp->next;
    }
}

void printAdjacencyList(struct Node** adjList, int numG) {
    printf("\nСписки смежности:\n");
    for (int i = 0; i < numG; i++) {
        printf("Вершина %d: ", i);
        struct Node* temp = adjList[i];
        while (temp != NULL) {
            printf("%d", temp->vertex);
            temp = temp->next;
            if (temp != NULL) {
                printf(" -> ");
            }
        }
        printf("\n");
    }
}

void freeAdjacencyList(struct Node** adjList, int numG) {
    for (int i = 0; i < numG; i++) {
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
    setlocale(LC_ALL, "Russian");

    int** G;
    int numG, current;
    int* visited;
    struct Node** adjList;

    printf("Введите количество вершин: ");
    scanf("%d", &numG);

    visited = (int*)malloc(numG * sizeof(int));
    G = (int**)malloc(numG * sizeof(int*));
    for (int i = 0; i < numG; i++)
        G[i] = (int*)malloc(numG * sizeof(int));

    adjList = (struct Node**)malloc(numG * sizeof(struct Node*));
    for (int i = 0; i < numG; i++) {
        adjList[i] = NULL;
    }

    srand(time(NULL));

    for (int i = 0; i < numG; i++) {
        visited[i] = 0;
        for (int j = i; j < numG; j++) {
            if (i == j) {
                G[i][j] = 0;
            }
            else {
                int value = rand() % 2;
                G[i][j] = value;
                G[j][i] = value;

                if (value == 1) {
                    addEdgeSorted(adjList, i, j);
                }
            }
        }
    }

    printf("\nМатрица смежности:\n");
    for (int i = 0; i < numG; i++) {
        for (int j = 0; j < numG; j++) {
            printf("%3d", G[i][j]);
        }
        printf("\n");
    }

    printAdjacencyList(adjList, numG);

    printf("\nВведите начальную вершину: ");
    scanf("%d", &current);

    printf("\n Обход в глубину (матрица смежности) \n");
    for (int i = 0; i < numG; i++) visited[i] = 0;
    printf("Путь обхода: ");
    DFS_matrix(G, numG, visited, current);
    printf("\n");

    printf("\n Обход в глубину (списки смежности) \n");
    for (int i = 0; i < numG; i++) visited[i] = 0;
    printf("Путь обхода: ");
    DFS_list(adjList, numG, visited, current);
    printf("\n");

    free(visited);
    for (int i = 0; i < numG; i++)
        free(G[i]);
    free(G);
    freeAdjacencyList(adjList, numG);

    printf("\nПрограмма завершена.\n");
    return 0;
}