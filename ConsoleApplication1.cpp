#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <queue>
#include <stack>
#include <windows.h>

using namespace std;

struct Node {
    int vertex;
    Node* next;
};

void BFSD_Matrix(int** G, int numG, int* DIST, int v) {
    queue<int> q;

    DIST[v] = 0;
    q.push(v);

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        for (int i = 0; i < numG; i++) {
            if (G[current][i] == 1 && DIST[i] == -1) {
                q.push(i);
                DIST[i] = DIST[current] + 1;
            }
        }
    }
}

void BFSD_AdjList(Node** adjList, int numG, int* DIST, int v) {
    queue<int> q;

    DIST[v] = 0;
    q.push(v);

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        Node* node = adjList[current];
        while (node != NULL) {
            if (DIST[node->vertex] == -1) {
                q.push(node->vertex);
                DIST[node->vertex] = DIST[current] + 1;
            }
            node = node->next;
        }
    }
}

void DFSD_Matrix(int** G, int numG, int* DIST, int v) {
    stack<int> s;
    s.push(v);
    DIST[v] = 0;

    while (!s.empty()) {
        int current = s.top();
        s.pop();

        for (int i = numG - 1; i >= 0; i--) {
            if (G[current][i] == 1 && DIST[i] == -1) {
                s.push(i);
                DIST[i] = DIST[current] + 1;
            }
        }
    }
}

void DFSD_AdjList(Node** adjList, int numG, int* DIST, int v) {
    stack<int> s;
    s.push(v);
    DIST[v] = 0;

    while (!s.empty()) {
        int current = s.top();
        s.pop();

        Node* node = adjList[current];
        stack<int> tempStack;
        while (node != NULL) {
            if (DIST[node->vertex] == -1) {
                tempStack.push(node->vertex);
            }
            node = node->next;
        }

        while (!tempStack.empty()) {
            int neighbor = tempStack.top();
            tempStack.pop();
            s.push(neighbor);
            DIST[neighbor] = DIST[current] + 1;
        }
    }
}

Node** createAdjListFromMatrix(int** matrix, int numG) {
    Node** adjList = (Node**)malloc(numG * sizeof(Node*));

    for (int i = 0; i < numG; i++) {
        adjList[i] = NULL;
        for (int j = 0; j < numG; j++) {
            if (matrix[i][j] == 1) {
                Node* newNode = (Node*)malloc(sizeof(Node));
                newNode->vertex = j;
                newNode->next = adjList[i];
                adjList[i] = newNode;
            }
        }
    }

    return adjList;
}

void printMatrix(int** G, int numG) {
    printf("\nМатрица смежности:\n");
    for (int i = 0; i < numG; i++) {
        for (int j = 0; j < numG; j++) {
            printf("%3d", G[i][j]);
        }
        printf("\n");
    }
}

void printAdjList(Node** adjList, int numG) {
    printf("\nСписки смежности:\n");
    for (int i = 0; i < numG; i++) {
        printf("Вершина %d: ", i);
        Node* current = adjList[i];
        while (current != NULL) {
            printf("%d -> ", current->vertex);
            current = current->next;
        }
        printf("NULL\n");
    }
}

void initDIST(int* DIST, int numG) {
    for (int i = 0; i < numG; i++) {
        DIST[i] = -1;
    }
}

void printDIST(int* DIST, int numG) {
    printf("Расстояния:\n");
    for (int i = 0; i < numG; i++) {
        printf("  до вершины %d: ", i);
        if (DIST[i] == -1) {
            printf("Недостижима\n");
        }
        else {
            printf("%d\n", DIST[i]);
        }
    }
}

void freeAdjList(Node** adjList, int numG) {
    for (int i = 0; i < numG; i++) {
        Node* current = adjList[i];
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(adjList);
}

double measureTime(void (*func)(int**, int, int*, int), int** graph, int numG, int* DIST, int start) {
    LARGE_INTEGER frequency, start_time, end_time;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start_time);

    func(graph, numG, DIST, start);

    QueryPerformanceCounter(&end_time);
    return (double)(end_time.QuadPart - start_time.QuadPart) / frequency.QuadPart;
}

double measureTimeAdjList(void (*func)(Node**, int, int*, int), Node** adjList, int numG, int* DIST, int start) {
    LARGE_INTEGER frequency, start_time, end_time;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start_time);

    func(adjList, numG, DIST, start);

    QueryPerformanceCounter(&end_time);
    return (double)(end_time.QuadPart - start_time.QuadPart) / frequency.QuadPart;
}

int main() {
    system("chcp 1251");
    int** G;
    Node** adjList;
    int numG, start;
    int* DIST;

    printf("=== Поиск расстояний в графе ===\n\n");

    printf("Введите количество вершин: ");
    scanf("%d", &numG);

    DIST = (int*)malloc(numG * sizeof(int));
    G = (int**)malloc(numG * sizeof(int*));
    for (int i = 0; i < numG; i++)
        G[i] = (int*)malloc(numG * sizeof(int));

    srand(time(NULL));

    for (int i = 0; i < numG; i++) {
        for (int j = 0; j < numG; j++) {
            if (i == j) {
                G[i][j] = 0;
            }
            else {
                if (i > j) {
                    G[i][j] = G[j][i];
                }
                else {
                    G[i][j] = rand() % 2;
                }
            }
        }
    }

    printMatrix(G, numG);

    adjList = createAdjListFromMatrix(G, numG);
    printAdjList(adjList, numG);

    printf("\nВведите стартовую вершину: ");
    scanf("%d", &start);

    double time_bfs_matrix, time_bfs_list, time_dfs_matrix, time_dfs_list;

    printf("\n=== BFSD с матрицей смежности  ===\n");
    initDIST(DIST, numG);
    time_bfs_matrix = measureTime(BFSD_Matrix, G, numG, DIST, start);
    printDIST(DIST, numG);
    printf("Время: %.6f секунд\n", time_bfs_matrix);

    printf("\n=== BFSD со списками смежности ===\n");
    initDIST(DIST, numG);
    time_bfs_list = measureTimeAdjList(BFSD_AdjList, adjList, numG, DIST, start);
    printDIST(DIST, numG);
    printf("Время: %.6f секунд\n", time_bfs_list);

    printf("\n=== DFSD с матрицей смежности ===\n");
    initDIST(DIST, numG);
    time_dfs_matrix = measureTime(DFSD_Matrix, G, numG, DIST, start);
    printDIST(DIST, numG);
    printf("Время: %.6f секунд\n", time_dfs_matrix);

    printf("\n=== DFSD со списками смежности ===\n");
    initDIST(DIST, numG);
    time_dfs_list = measureTimeAdjList(DFSD_AdjList, adjList, numG, DIST, start);
    printDIST(DIST, numG);
    printf("Время: %.6f секунд\n", time_dfs_list);

    printf("\n=== СРАВНЕНИЕ ВРЕМЕНИ ВЫПОЛНЕНИЯ ===\n");
    printf("+---------------------------------+------------------+\n");
    printf("| Алгоритм                        | Время (секунды)  |\n");
    printf("+---------------------------------+------------------+\n");
    printf("| BFSD с матрицей смежности       |  %14.6f  |\n", time_bfs_matrix);
    printf("| BFSD со списками смежности      |  %14.6f  |\n", time_bfs_list);
    printf("| DFSD с матрицей смежности       |  %14.6f  |\n", time_dfs_matrix);
    printf("| DFSD со списками смежности      |  %14.6f  |\n", time_dfs_list);
    printf("+---------------------------------+------------------+\n");

    free(DIST);
    for (int i = 0; i < numG; i++)
        free(G[i]);
    free(G);
    freeAdjList(adjList, numG);

    _getch();
    return 0;
}