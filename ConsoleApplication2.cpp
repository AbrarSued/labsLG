#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <string.h>

struct node {
    int inf;  
    struct node* next;
};

struct node* top = NULL;

struct node* get_struct(void) {
    struct node* p = NULL;
    int value;

    if ((p = (struct node*)malloc(sizeof(struct node))) == NULL) {
        printf("Ошибка при распределении памяти\n");
        exit(1);
    }

    printf("Введите значение: \n");
    scanf("%d", &value);

    p->inf = value;
    p->next = NULL;

    return p;
}

void push_stack(int item) {
    struct node* p = NULL;

    if ((p = (struct node*)malloc(sizeof(struct node))) == NULL) {
        printf("Ошибка при распределении памяти\n");
        exit(1);
    }

    p->inf = item;
    p->next = top;
    top = p;
}

int pop_stack(void) {
    if (top == NULL) {
        return -1;
    }

    struct node* temp = top;
    int item = temp->inf;
    top = top->next;
    free(temp);

    return item;
}

int is_stack_empty(void) {
    return top == NULL;
}

void clear_stack(void) {
    struct node* current = top;
    struct node* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    top = NULL;
}

struct Node {
    int vertex;
    struct Node* next;
};

void addEdge(struct Node** adjList, int src, int dest) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = dest;
    newNode->next = adjList[src];
    adjList[src] = newNode;
}

void DFS_adjacency(struct Node** adjList, int numG, int* visited, int start) {
    clear_stack(); 

    push_stack(start);
    visited[start] = 1;

    while (!is_stack_empty()) {
        int current = pop_stack();
        printf("%3d", current);

        struct Node* temp = adjList[current];
        while (temp != NULL) {
            int neighbor = temp->vertex;
            if (visited[neighbor] == 0) {
                visited[neighbor] = 1;
                push_stack(neighbor);
            }
            temp = temp->next;
        }
    }
}

struct Node** matrixToAdjacencyList(int** G, int numG) {
    struct Node** adjList = (struct Node**)malloc(numG * sizeof(struct Node*));

    for (int i = 0; i < numG; i++) {
        adjList[i] = NULL;
        for (int j = 0; j < numG; j++) {
            if (G[i][j] == 1 && i != j) {
                addEdge(adjList, i, j);
            }
        }
    }

    return adjList;
}

void printAdjacencyList(struct Node** adjList, int numG) {
    printf("\nСписки смежности:\n");
    for (int i = 0; i < numG; i++) {
        printf("Вершина %d: ", i);
        struct Node* temp = adjList[i];
        while (temp != NULL) {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("NULL\n");
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

void DFS_matrix(int** G, int numG, int* visited, int start) {
    clear_stack(); 

    push_stack(start);
    visited[start] = 1;

    while (!is_stack_empty()) {
        int current = pop_stack();
        printf("%3d", current);

        for (int i = numG - 1; i >= 0; i--) {
            if (G[current][i] == 1 && visited[i] == 0) {
                visited[i] = 1;
                push_stack(i);
            }
        }
    }
}

int main() {
    setlocale(LC_ALL, "Russian");

    int** G;
    int numG, current;
    int* visited;

    printf("Введите количество вершин: ");
    scanf("%d", &numG);

    visited = (int*)malloc(numG * sizeof(int));
    G = (int**)malloc(numG * sizeof(int*));
    for (int i = 0; i < numG; i++)
        G[i] = (int*)malloc(numG * sizeof(int));

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

    struct Node** adjList = matrixToAdjacencyList(G, numG);
    printAdjacencyList(adjList, numG);

    printf("\nВведите начальную вершину: ");
    scanf("%d", &current);

    printf("\n=== Обход в глубину (матрица смежности) ===\n");
    for (int i = 0; i < numG; i++) visited[i] = 0;
    printf("Путь обхода: ");
    DFS_matrix(G, numG, visited, current);
    printf("\n");

    printf("\n=== Обход в глубину (списки смежности) ===\n");
    for (int i = 0; i < numG; i++) visited[i] = 0;
    printf("Путь обхода: ");
    DFS_adjacency(adjList, numG, visited, current);
    printf("\n");

    clear_stack();

    free(visited);
    for (int i = 0; i < numG; i++)
        free(G[i]);
    free(G);
    freeAdjacencyList(adjList, numG);

    printf("\nПрограмма завершена.\n");
    return 0;
}