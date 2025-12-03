#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <queue>
#include <limits.h>
#include <windows.h>
#include <vector>

using namespace std;

void Dijkstra_Matrix(int** G, int** W, int numG, int* DIST, int start) {
    for (int i = 0; i < numG; i++) {
        DIST[i] = INT_MAX;
    }
    DIST[start] = 0;

    vector<bool> visited(numG, false);

    for (int count = 0; count < numG; count++) {
        int min_dist = INT_MAX;
        int u = -1;

        for (int i = 0; i < numG; i++) {
            if (!visited[i] && DIST[i] < min_dist) {
                min_dist = DIST[i];
                u = i;
            }
        }

        if (u == -1 || DIST[u] == INT_MAX) break;

        visited[u] = true;

        for (int v = 0; v < numG; v++) {
            if (G[u][v] > 0 && !visited[v] && DIST[u] != INT_MAX) {
                int new_dist = DIST[u] + W[u][v];
                if (new_dist < DIST[v]) {
                    DIST[v] = new_dist;
                }
            }
        }
    }
}

int calculateEccentricity(int** distances, int numG, int vertex) {
    int max_dist = 0;
    bool all_reachable = true;

    for (int i = 0; i < numG; i++) {
        if (vertex == i) continue;

        if (distances[vertex][i] == INT_MAX) {
            all_reachable = false;
            continue;
        }

        if (distances[vertex][i] > max_dist) {
            max_dist = distances[vertex][i];
        }
    }

    if (!all_reachable) {
        return -1;
    }

    return max_dist;
}

void calculateGraphMetrics(int** distances, int numG, int* radius, int* diameter,
    int* central_vertices, int* peripheral_vertices, int* central_count,
    int* peripheral_count, int** eccentricities_array) {

    int* eccentricities = (int*)malloc(numG * sizeof(int));

    for (int i = 0; i < numG; i++) {
        eccentricities[i] = calculateEccentricity(distances, numG, i);
    }

    if (eccentricities_array != NULL) {
        *eccentricities_array = eccentricities;
    }

    bool connected = true;
    for (int i = 0; i < numG; i++) {
        if (eccentricities[i] == -1) {
            connected = false;
            break;
        }
    }

    if (!connected) {
        printf("Граф не является связным! Метрики не определены.\n");
        *radius = -1;
        *diameter = -1;
        *central_count = 0;
        *peripheral_count = 0;
        if (eccentricities_array == NULL) {
            free(eccentricities);
        }
        return;
    }

    *radius = INT_MAX;
    *diameter = 0;

    for (int i = 0; i < numG; i++) {
        if (eccentricities[i] < *radius) {
            *radius = eccentricities[i];
        }
        if (eccentricities[i] > *diameter) {
            *diameter = eccentricities[i];
        }
    }

    *central_count = 0;
    *peripheral_count = 0;

    for (int i = 0; i < numG; i++) {
        if (eccentricities[i] == *radius) {
            central_vertices[(*central_count)++] = i;
        }
        if (eccentricities[i] == *diameter) {
            peripheral_vertices[(*peripheral_count)++] = i;
        }
    }

    if (eccentricities_array == NULL) {
        free(eccentricities);
    }
}

void printMatrix(int** G, int numG) {
    printf("\nМатрица смежности:\n");
    for (int i =


        0; i < numG; i++) {
        for (int j = 0; j < numG; j++) {
            printf("%3d", G[i][j]);
        }
        printf("\n");
    }
}

void printWeightMatrix(int** W, int numG) {
    printf("\nМатрица весов:\n");
    for (int i = 0; i < numG; i++) {
        for (int j = 0; j < numG; j++) {
            printf("%3d", W[i][j]);
        }
        printf("\n");
    }
}

void initDIST(int* DIST, int numG) {
    for (int i = 0; i < numG; i++) {
        DIST[i] = INT_MAX;
    }
}

void printDIST(int* DIST, int numG, int start) {
    printf("Кратчайшие расстояния от вершины %d:\n", start);
    for (int i = 0; i < numG; i++) {
        printf("  до вершины %d: ", i);
        if (DIST[i] == INT_MAX) {
            printf("Недостижима\n");
        }
        else {
            printf("%d\n", DIST[i]);
        }
    }
}

void printAllDistances(int** distances, int numG) {
    printf("\nМатрица кратчайших расстояний между всеми вершинами:\n");
    for (int i = 0; i < numG; i++) {
        for (int j = 0; j < numG; j++) {
            if (distances[i][j] == INT_MAX) {
                printf("   ∞");
            }
            else {
                printf("%4d", distances[i][j]);
            }
        }
        printf("\n");
    }
}

void printEccentricities(int* eccentricities, int numG) {
    printf("\nЭксцентриситеты вершин:\n");
    for (int i = 0; i < numG; i++) {
        if (eccentricities[i] == -1) {
            printf("  Вершина %d: не определена (граф несвязный)\n", i);
        }
        else {
            printf("  Вершина %d: %d\n", i, eccentricities[i]);
        }
    }
}

int main() {
    system("chcp 1251");
    int** G;
    int** W;
    int numG, start;
    int* DIST;
    int directed;

    printf("Введите количество вершин: ");
    scanf("%d", &numG);

    printf("Тип графа (0 - неориентированный, 1 - ориентированный): ");
    scanf("%d", &directed);

    DIST = (int*)malloc(numG * sizeof(int));
    G = (int**)malloc(numG * sizeof(int*));
    W = (int**)malloc(numG * sizeof(int*));
    for (int i = 0; i < numG; i++) {
        G[i] = (int*)malloc(numG * sizeof(int));
        W[i] = (int*)malloc(numG * sizeof(int));
    }

    srand(time(NULL));

    for (int i = 0; i < numG; i++) {
        for (int j = 0; j < numG; j++) {
            if (i == j) {
                G[i][j] = 0;
                W[i][j] = 0;
            }
            else {
                if (directed) {
                    G[i][j] = rand() % 2;
                    if (G[i][j] == 1) {
                        W[i][j] = rand() % 10 + 1;
                    }
                    else {
                        W[i][j] = 0;
                    }
                }
                else {
                    if (i > j) {
                        G[i][j] = G[j][i];
                        W[i][j] = W[j][i];
                    }
                    else {
                        G[i][j] = rand() % 2;
                        if (G[i][j] == 1) {
                            W[i][j] = rand() % 10 + 1;
                        }
                        else {
                            W[i][j] = 0;
                        }
                    }
                }
            }
        }
    }

    printMatrix(G, numG);
    printWeightMatrix(W, numG);

    printf("\nВведите стартовую вершину: ");
    scanf("%d", &start);

    printf("\n=== Алгоритм Дейкстры для взвешенного графа ===\n");
    initDIST(DIST, numG);
    Dijkstra_Matrix(G, W, numG, DIST, start);
    printDIST(DIST, numG, start);

    int** all_distances = (int**)malloc(numG * sizeof(int*));
    for (int i = 0; i < numG; i++) {
        all_distances[i] = (int*)malloc(numG * sizeof(int));
        initDIST(all_distances[i], numG);
        Dijkstra_Matrix(G, W, numG, all_distances[i], i);
    }

    printAllDistances(all_distances, numG);

    int radius, diameter;
    int* central_vertices = (int*)malloc(numG * sizeof(int));
    int* peripheral_vertices = (int*)malloc(numG * sizeof(int));
    int central_count, peripheral_count;
    int*


        eccentricities = NULL;

    calculateGraphMetrics(all_distances, numG, &radius, &diameter,
        central_vertices, peripheral_vertices, &central_count,
        &peripheral_count, &eccentricities);

    printf("\n=== МЕТРИКИ ГРАФА ===\n");
    if (radius == -1) {
        printf("Граф не является связным. Метрики не определены.\n");
    }
    else {
        printEccentricities(eccentricities, numG);

        printf("\nРадиус графа: %d\n", radius);
        printf("Диаметр графа: %d\n", diameter);

        printf("Центральные вершины (%d): ", central_count);
        for (int i = 0; i < central_count; i++) {
            printf("%d ", central_vertices[i]);
        }
        printf("\n");

        printf("Периферийные вершины (%d): ", peripheral_count);
        for (int i = 0; i < peripheral_count; i++) {
            printf("%d ", peripheral_vertices[i]);
        }
        printf("\n");
    }

    free(DIST);
    for (int i = 0; i < numG; i++) {
        free(G[i]);
        free(W[i]);
        free(all_distances[i]);
    }
    free(G);
    free(W);
    free(all_distances);
    free(central_vertices);
    free(peripheral_vertices);
    if (eccentricities != NULL) {
        free(eccentricities);
    }

    printf("\nНажмите любую клавишу для выхода...");
    _getch();
    return 0;
}