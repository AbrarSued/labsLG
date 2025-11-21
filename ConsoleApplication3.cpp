#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <queue>
#include <windows.h>

using namespace std;

struct Node {
    int vertex;
    Node* next;
};

struct QueueNode {
    int data;
    QueueNode* next;
};

struct Queue {
    QueueNode* front;
    QueueNode* rear;
};

Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

int isQueueEmpty(Queue* q) {
    return q->front == NULL;
}

void enqueue(Queue* q, int data) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    newNode->data = data;
    newNode->next = NULL;

    if (q->rear == NULL) {
        q->front = q->rear = newNode;
        return;
    }

    q->rear->next = newNode;
    q->rear = newNode;
}

int dequeue(Queue* q) {
    if (isQueueEmpty(q)) {
        return -1;
    }

    QueueNode* temp = q->front;
    int data = temp->data;

    q->front = q->front->next;

    if (q->front == NULL) {
        q->rear = NULL;
    }

    free(temp);
    return data;
}

void freeQueue(Queue* q) {
    while (!isQueueEmpty(q)) {
        dequeue(q);
    }
    free(q);
}

void BFS_Matrix_STL(int** G, int numG, int* visited, int s) {
    queue<int> q;
    int v;

    visited[s] = 1;
    q.push(s);
    while (!q.empty())
    {
        v = q.front();
        q.pop();

        printf("%3d", v);

        for (int i = 0; i < numG; i++) {
            if (G[v][i] == 1 && visited[i] == 0) {
                q.push(i);
                visited[i] = 1;
            }
        }
    }
}

void BFS_Matrix_CustomQueue(int** G, int numG, int* visited, int s) {
    Queue* q = createQueue();
    int v;

    visited[s] = 1;
    enqueue(q, s);

    while (!isQueueEmpty(q)) {
        v = dequeue(q);

        printf("%3d", v);

        for (int i = 0; i < numG; i++) {
            if (G[v][i] == 1 && visited[i] == 0) {
                enqueue(q, i);
                visited[i] = 1;
            }
        }
    }

    freeQueue(q);
}

void BFS_AdjList_STL(Node** adjList, int numG, int* visited, int s) {
    queue<int> q;
    int v;

    visited[s] = 1;
    q.push(s);

    while (!q.empty()) {
        v = q.front();
        q.pop();

        printf("%3d", v);

        Node* current = adjList[v];
        while (current != NULL) {
            int neighbor = current->vertex;
            if (visited[neighbor] == 0) {
                q.push(neighbor);
                visited[neighbor] = 1;
            }
            current = current->next;
        }
    }
}

void BFS_AdjList_CustomQueue(Node** adjList, int numG, int* visited, int s) {
    Queue* q = createQueue();
    int v;

    visited[s] = 1;
    enqueue(q, s);

    while (!isQueueEmpty(q)) {
        v = dequeue(q);

        printf("%3d", v);

        Node* current = adjList[v];
        while (current != NULL) {
            int neighbor = current->vertex;
            if (visited[neighbor] == 0) {
                enqueue(q, neighbor);
                visited[neighbor] = 1;
            }
            current = current->next;
        }
    }

    freeQueue(q);
}

Node** createAdjListFromMatrix(int** matrix, int numG, int directed) {
    Node** adjList = (Node**)malloc(numG * sizeof(Node*));

    for (int i = 0; i < numG; i++) {
        adjList[i] = NULL;
        for (int j = 0; j < numG; j++) {
            if (matrix[i][j] == 1 && i != j) {
                Node* newNode = (Node*)malloc(sizeof(Node));
                newNode->vertex = j;
                newNode->next = adjList[i];
                adjList[i] = newNode;
            }
        }
    }

    return adjList;
}

void printMatrix(int** G, int numG, int directed) {
    printf("Adjacency Matrix:\n");
    for (int i = 0; i < numG; i++) {
        for (int j = 0; j < numG; j++) {
            printf("%3d", G[i][j]);
        }
        printf("\n");
    }
}

void printAdjList(Node** adjList, int numG) {
    printf("\nAdjacency Lists:\n");
    for (int i = 0; i < numG; i++) {
        printf("Vertex %d: ", i);
        Node* current = adjList[i];
        while (current != NULL) {
            printf("%d -> ", current->vertex);
            current = current->next;
        }
        printf("NULL\n");
    }
}

void initVisited(int* visited, int numG) {
    for (int i = 0; i < numG; i++) {
        visited[i] = 0;
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

double measureTime(void (*bfs_func)(int**, int, int*, int), int** graph, int numG, int* visited, int start) {
    LARGE_INTEGER frequency, start_time, end_time;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start_time);

    bfs_func(graph, numG, visited, start);

    QueryPerformanceCounter(&end_time);
    return (double)(end_time.QuadPart - start_time.QuadPart) / frequency.QuadPart;
}

double measureTimeAdjList(void (*bfs_func)(Node**, int, int*, int), Node** adjList, int numG, int* visited, int start) {
    LARGE_INTEGER frequency, start_time, end_time;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start_time);

    bfs_func(adjList, numG, visited, start);

    QueryPerformanceCounter(&end_time);
    return (double)(end_time.QuadPart - start_time.QuadPart) / frequency.QuadPart;
}

int main() {
    int** G;
    Node** adjList;
    int numG, current, directed;
    int* visited;

    printf("Graph type (0 - undirected, 1 - directed): ");
    scanf("%d", &directed);

    printf("Input number of vertices: ");
    scanf("%d", &numG);

    visited = (int*)malloc(numG * sizeof(int));
    G = (int**)malloc(numG * sizeof(int*));
    for (int i = 0; i < numG; i++)
        G[i] = (int*)malloc(numG * sizeof(int));

    srand(time(NULL));

    for (int i = 0; i < numG; i++) {
        visited[i] = 0;
        for (int j = 0; j < numG; j++) {
            if (i == j) {
                G[i][j] = 0;
            }
            else {
                if (directed) {
                    G[i][j] = rand() % 2;
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
    }

    printMatrix(G, numG, directed);

    adjList = createAdjListFromMatrix(G, numG, directed);
    printAdjList(adjList, numG);

    printf("\nInput the start vertex: ");
    scanf("%d", &current);

    double time_matrix_queue, time_matrix_custom, time_list_queue, time_list_custom;

    printf("\n=== BFS with Matrix (STL queue) ===\n");
    printf("Path: ");
    initVisited(visited, numG);
    time_matrix_queue = measureTime(BFS_Matrix_STL, G, numG, visited, current);
    printf("\n");

    printf("\n=== BFS with Matrix (Custom Queue) ===\n");
    printf("Path: ");
    initVisited(visited, numG);
    time_matrix_custom = measureTime(BFS_Matrix_CustomQueue, G, numG, visited, current);
    printf("\n");

    printf("\n=== BFS with Lists (STL queue) ===\n");
    printf("Path: ");
    initVisited(visited, numG);
    time_list_queue = measureTimeAdjList(BFS_AdjList_STL, adjList, numG, visited, current);
    printf("\n");

    printf("\n=== BFS with Lists (Custom Queue) ===\n");
    printf("Path: ");
    initVisited(visited, numG);
    time_list_custom = measureTimeAdjList(BFS_AdjList_CustomQueue, adjList, numG, visited, current);
    printf("\n");

    printf("\n+------------------------+------------------+\n");
    printf("| Algorithm              | Time (seconds)   |\n");
    printf("+------------------------+------------------+\n");
    printf("| Matrix (queue)         |  %14.6f  |\n", time_matrix_queue);
    printf("| Matrix (Custom)        |  %14.6f  |\n", time_matrix_custom);
    printf("| AdjList (queue)        |  %14.6f  |\n", time_list_queue);
    printf("| AdjList (Custom )      |  %14.6f  |\n", time_list_custom);
    printf("+------------------------+------------------+\n");

    printf("\nGraph type: %s\n", directed ? "DIRECTED" : "UNDIRECTED");

    free(visited);
    for (int i = 0; i < numG; i++)
        free(G[i]);
    free(G);
    freeAdjList(adjList, numG);

    printf("\nPress any key to exit...");
    _getch();
    return 0;
}