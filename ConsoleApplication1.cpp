#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int** create_adjacency_matrix(int n, double edgeProbability, double loopProbability) {
    int** matrix = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int*)malloc(n * sizeof(int));
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            double randomValue = (double)rand() / RAND_MAX;
            if (i == j) {
                if (randomValue < loopProbability) {
                    matrix[i][j] = 1;
                }
                else {
                    matrix[i][j] = 0;
                }
            }
            else {
                if (randomValue < edgeProbability) {
                    matrix[i][j] = 1;
                    matrix[j][i] = 1;
                }
                else {
                    matrix[i][j] = 0;
                    matrix[j][i] = 0;
                }
            }
        }
    }

    return matrix;
}

int** create_directed_adjacency_matrix(int n, double edgeProbability, double loopProbability) {
    int** matrix = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int*)malloc(n * sizeof(int));
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = 0;
        }
    }

    for (int i = 0; i < n; i++) {
        double randomValue = (double)rand() / RAND_MAX;
        if (randomValue < loopProbability) {
            matrix[i][i] = 1;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) {
                double randomValue = (double)rand() / RAND_MAX;
                if (randomValue < edgeProbability) {
                    matrix[i][j] = 1;
                }
            }
        }
    }

    return matrix;
}

int** create_incidence_matrix(int** adj_matrix, int n, int* edge_count) {
    *edge_count = 0;

    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (adj_matrix[i][j] == 1) {
                (*edge_count)++;
            }
        }
    }

    int** inc_matrix = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        inc_matrix[i] = (int*)malloc(*edge_count * sizeof(int));
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < *edge_count; j++) {
            inc_matrix[i][j] = 0;
        }
    }

    int edge_index = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (adj_matrix[i][j] == 1) {
                if (i == j) {
                    inc_matrix[i][edge_index] = 2;
                }
                else {
                    inc_matrix[i][edge_index] = 1;
                    inc_matrix[j][edge_index] = 1;
                }
                edge_index++;
            }
        }
    }

    return inc_matrix;
}

int** create_directed_incidence_matrix(int** adj_matrix, int n, int* edge_count) {
    *edge_count = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (adj_matrix[i][j] == 1) {
                (*edge_count)++;
            }
        }
    }

    int** inc_matrix = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        inc_matrix[i] = (int*)malloc(*edge_count * sizeof(int));
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < *edge_count; j++) {
            inc_matrix[i][j] = 0;
        }
    }

    int edge_index = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (adj_matrix[i][j] == 1) {
                if (i == j) {
                    inc_matrix[i][edge_index] = 2;
                }
                else {
                    inc_matrix[i][edge_index] = -1;
                    inc_matrix[j][edge_index] = 1;
                }
                edge_index++;
            }
        }
    }

    return inc_matrix;
}

void print_incidence_matrix(int** inc_matrix, int n, int edge_count, int is_directed) {
    if (is_directed) {
        printf("\nМатрица инцидентности ориентированного графа (%d вершин x %d дуг):\n", n, edge_count);
    }
    else {
        printf("\nМатрица инцидентности неориентированного графа (%d вершин x %d ребер):\n", n, edge_count);
    }

    printf("   ");
    for (int j = 0; j < edge_count; j++) {
        printf("e%-2d", j + 1);
    }
    printf("\n");

    for (int i = 0; i < n; i++) {
        printf("v%-2d", i + 1);
        for (int j = 0; j < edge_count; j++) {
            printf("%2d ", inc_matrix[i][j]);
        }
        printf("\n");
    }

    if (is_directed) {
        printf("Обозначения: -1 - начало дуги, 1 - конец дуги, 2 - петля\n");
    }
    else {
        printf("Обозначения: 1 - инцидентная вершина, 2 - петля\n");
    }
}

int vertex_degree_from_incidence(int** inc_matrix, int n, int edge_count, int vertex) {
    int degree = 0;
    for (int j = 0; j < edge_count; j++) {
        if (inc_matrix[vertex][j] == 1) {
            degree++;
        }
        else if (inc_matrix[vertex][j] == 2) {
            degree += 2;
        }
    }
    return degree;
}

int vertex_out_degree_from_directed_incidence(int** inc_matrix, int n, int edge_count, int vertex) {
    int out_degree = 0;
    for (int j = 0; j < edge_count; j++) {
        if (inc_matrix[vertex][j] == -1) {
            out_degree++;
        }
        else if (inc_matrix[vertex][j] == 2) {
            out_degree++;
        }
    }
    return out_degree;
}

int vertex_in_degree_from_directed_incidence(int** inc_matrix, int n, int edge_count, int vertex) {
    int in_degree = 0;
    for (int j = 0; j < edge_count; j++) {
        if (inc_matrix[vertex][j] == 1) {
            in_degree++;
        }
        else if (inc_matrix[vertex][j] == 2) {
            in_degree++;
        }
    }
    return in_degree;
}

void find_isolated_vertices_from_incidence(int** inc_matrix, int n, int edge_count) {
    printf("Изолированные вершины: ");
    int has_isolated = 0;
    for (int i = 0; i < n; i++) {
        int is_isolated = 1;
        for (int j = 0; j < edge_count; j++) {
            if (inc_matrix[i][j] != 0) {
                is_isolated = 0;
                break;
            }
        }
        if (is_isolated) {
            printf("%d ", i + 1);
            has_isolated = 1;
        }
    }
    if (!has_isolated) printf("нет");
    printf("\n");
}

void find_end_vertices_from_incidence(int** inc_matrix, int n, int edge_count) {
    printf("Концевые вершины: ");
    int has_end = 0;
    for (int i = 0; i < n; i++) {
        int edge_count_for_vertex = 0;
        for (int j = 0; j < edge_count; j++) {
            if (inc_matrix[i][j] == 1) {
                edge_count_for_vertex++;
            }
            else if (inc_matrix[i][j] == 2) {
                edge_count_for_vertex += 2;
            }
        }
        if (edge_count_for_vertex == 1) {
            printf("%d ", i + 1);
            has_end = 1;
        }
    }
    if (!has_end) printf("нет");
    printf("\n");
}

void find_dominant_vertices_from_incidence(int** inc_matrix, int n, int edge_count) {
    printf("Доминирующие вершины: ");
    int has_dominant = 0;
    for (int i = 0; i < n; i++) {
        int connections = 0;
        for (int j = 0; j < n; j++) {
            if (i != j) {
                int has_connection = 0;
                for (int k = 0; k < edge_count; k++) {
                    if ((inc_matrix[i][k] == 1 && inc_matrix[j][k] == 1) ||
                        (inc_matrix[i][k] == 1 && inc_matrix[j][k] == 1)) {
                        has_connection = 1;
                        break;
                    }
                }
                if (has_connection) connections++;
            }
        }
        if (connections == n - 1) {
            printf("%d ", i + 1);
            has_dominant = 1;
        }
    }
    if (!has_dominant) printf("нет");
    printf("\n");
}

int graph_size(int** matrix, int n) {
    int edges = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (matrix[i][j] == 1) {
                edges++;
            }
        }
    }
    return edges;
}

int directed_graph_size(int** matrix, int n) {
    int edges = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == 1) {
                edges++;
            }
        }
    }
    return edges;
}

void print_matrix(int** matrix, int n, const char* title) {
    printf("%s (%dx%d):\n", title, n, n);
    printf("   ");
    for (int i = 0; i < n; i++) {
        printf("%2d ", i + 1);
    }
    printf("\n");

    for (int i = 0; i < n; i++) {
        printf("%2d ", i + 1);
        for (int j = 0; j < n; j++) {
            printf("%2d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int vertex_degree(int** matrix, int n, int vertex) {
    int degree = 0;
    for (int i = 0; i < n; i++) {
        if (matrix[vertex][i] == 1) {
            degree++;
            if (vertex == i) {
                degree++;
            }
        }
    }
    return degree;
}

void print_vertex_degrees_from_incidence(int** inc_matrix, int n, int edge_count) {
    printf("\nСтепени вершин:\n");
    for (int i = 0; i < n; i++) {
        int degree = vertex_degree_from_incidence(inc_matrix, n, edge_count, i);
        printf("Вершина %d: степень %d\n", i + 1, degree);
    }
}

void print_directed_vertex_degrees_from_incidence(int** inc_matrix, int n, int edge_count) {
    printf("\nПолустепени вершин ориентированного графа:\n");
    for (int i = 0; i < n; i++) {
        int out_degree = vertex_out_degree_from_directed_incidence(inc_matrix, n, edge_count, i);
        int in_degree = vertex_in_degree_from_directed_incidence(inc_matrix, n, edge_count, i);
        printf("Вершина %d: исходящая степень = %d, входящая степень = %d\n",
            i + 1, out_degree, in_degree);
    }
}

void find_special_vertices(int** matrix, int n) {
    printf("\nСпециальные вершины (через матрицу смежности):\n");

    printf("Изолированные вершины (степень 0): ");
    int has_isolated = 0;
    for (int i = 0; i < n; i++) {
        if (vertex_degree(matrix, n, i) == 0) {
            printf("%d ", i + 1);
            has_isolated = 1;
        }
    }
    if (!has_isolated) printf("нет");
    printf("\n");

    printf("Концевые вершины (степень 1): ");
    int has_end = 0;
    for (int i = 0; i < n; i++) {
        if (vertex_degree(matrix, n, i) == 1) {
            printf("%d ", i + 1);
            has_end = 1;
        }
    }
    if (!has_end) printf("нет");
    printf("\n");

    printf("Доминирующие вершины (степень %d): ", n - 1);
    int has_dominant = 0;
    for (int i = 0; i < n; i++) {
        if (vertex_degree(matrix, n, i) == n - 1) {
            printf("%d ", i + 1);
            has_dominant = 1;
        }
    }
    if (!has_dominant) printf("нет");
    printf("\n");
}

void print_vertex_degrees(int** matrix, int n) {
    printf("\nСтепени вершин (через матрицу смежности):\n");
    for (int i = 0; i < n; i++) {
        int degree = vertex_degree(matrix, n, i);
        printf("Вершина %d: степень %d\n", i + 1, degree);
    }
}

void free_matrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void free_incidence_matrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void show_menu() {
    printf("\n=== МЕНЮ ===\n");
    printf("1 - Показать матрицу смежности (неориентированный граф)\n");
    printf("2 - Вывести размер графа G, изолированные, концевые и доминирующие вершины (через матрицу смежности)\n");
    printf("3 - Показать матрицу инцидентности (неориентированный граф)\n");
    printf("4 - Вывести размер графа G, изолированные, концевые и доминирующие вершины (через матрицу инцидентности)\n");
    printf("5 - Показать матрицу смежности (ориентированный граф)\n");
    printf("6 - Показать матрицу инцидентности (ориентированный граф)\n");
    printf("7 - Ввести новое количество вершин\n");
    printf("8 - Закрыть программу\n");
    printf("Выберите опцию: ");
}

int main() {
    system("chcp 1251");
    srand(time(NULL));

    int n = 0;
    int** adj_matrix = NULL;
    int** directed_adj_matrix = NULL;
    int** inc_matrix = NULL;
    int** directed_inc_matrix = NULL;
    int edge_count = 0;
    int directed_edge_count = 0;
    double edgeProbability = 0.0;
    double loopProbability = 0.1;

    printf("\n=== Генератор графов с петлями ===\n\n");

    printf("Введите количество вершин: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Ошибка: количество вершин должно быть положительным числом.\n");
        return 1;
    }

    edgeProbability = 0.1 + (double)rand() / RAND_MAX * 0.8;

    adj_matrix = create_adjacency_matrix(n, edgeProbability, loopProbability);
    directed_adj_matrix = create_directed_adjacency_matrix(n, edgeProbability, loopProbability);
    inc_matrix = create_incidence_matrix(adj_matrix, n, &edge_count);
    directed_inc_matrix = create_directed_incidence_matrix(directed_adj_matrix, n, &directed_edge_count);

    int choice;
    do {
        show_menu();
        scanf("%d", &choice);

        switch (choice) {
        case 1: {
            printf("\n");
            print_matrix(adj_matrix, n, "Матрица смежности неориентированного графа");
            break;
        }

        case 2: {
            printf("\n");
            int graph_edges = graph_size(adj_matrix, n);
            printf("\nРазмер графа G: |E(G)| = %d ребер\n", graph_edges);
            print_vertex_degrees(adj_matrix, n);
            find_special_vertices(adj_matrix, n);
            break;
        }

        case 3: {
            printf("\n");
            print_incidence_matrix(inc_matrix, n, edge_count, 0);
            break;
        }

        case 4: {
            printf("\n");
            printf("\nРазмер графа G через матрицу инцидентности: |E(G)| = %d ребер\n", edge_count);
            print_vertex_degrees_from_incidence(inc_matrix, n, edge_count);
            printf("\nСпециальные вершины (через матрицу инцидентности):\n");
            find_isolated_vertices_from_incidence(inc_matrix, n, edge_count);
            find_end_vertices_from_incidence(inc_matrix, n, edge_count);
            find_dominant_vertices_from_incidence(inc_matrix, n, edge_count);
            break;
        }

        case 5: {
            printf("\n");
            print_matrix(directed_adj_matrix, n, "Матрица смежности ориентированного графа");
            break;
        }

        case 6: {
            printf("\n");
            print_incidence_matrix(directed_inc_matrix, n, directed_edge_count, 1);
            break;
        }

        case 7: {
            if (adj_matrix != NULL) free_matrix(adj_matrix, n);
            if (directed_adj_matrix != NULL) free_matrix(directed_adj_matrix, n);
            if (inc_matrix != NULL) free_incidence_matrix(inc_matrix, n);
            if (directed_inc_matrix != NULL) free_incidence_matrix(directed_inc_matrix, n);

            printf("\nВведите новое количество вершин: ");
            scanf("%d", &n);

            if (n <= 0) {
                printf("Ошибка: количество вершин должно быть положительным числом.\n");
                return 1;
            }

            edgeProbability = 0.1 + (double)rand() / RAND_MAX * 0.8;

            adj_matrix = create_adjacency_matrix(n, edgeProbability, loopProbability);
            directed_adj_matrix = create_directed_adjacency_matrix(n, edgeProbability, loopProbability);
            inc_matrix = create_incidence_matrix(adj_matrix, n, &edge_count);
            directed_inc_matrix = create_directed_incidence_matrix(directed_adj_matrix, n, &directed_edge_count);
            printf("Новый граф создан успешно!\n");
            break;
        }

        case 8: {
            printf("\nПрограмма завершена.....\n");
            break;
        }

        default: {
            printf("Неверный выбор!\n");
            break;
        }
        }
    } while (choice != 8);

    if (adj_matrix != NULL) free_matrix(adj_matrix, n);
    if (directed_adj_matrix != NULL) free_matrix(directed_adj_matrix, n);
    if (inc_matrix != NULL) free_incidence_matrix(inc_matrix, n);
    if (directed_inc_matrix != NULL) free_incidence_matrix(directed_inc_matrix, n);

    return 0;
}