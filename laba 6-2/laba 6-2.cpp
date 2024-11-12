#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
} AdjList;

void generate_adjacency_matrix(int** matrix, int vertices) {
    for (int i = 0; i < vertices; i++) {
        for (int j = i; j < vertices; j++) {
            if (i == j) {
                matrix[i][j] = 0;
            }
            else {
                matrix[i][j] = rand() % 2;
                matrix[j][i] = matrix[i][j];
            }
        }
    }
}

void print_adjacency_matrix(int** matrix, int vertices) {
    printf("Матрица смежности:\n");
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void merge_vertices(int** matrix, int vertices, int v1, int v2) {
    for (int i = 0; i < vertices; i++) {
        matrix[v1][i] = matrix[v1][i] | matrix[v2][i];
        matrix[i][v1] = matrix[i][v1] | matrix[i][v2];
    }
    for (int i = 0; i < vertices; i++) {
        matrix[v2][i] = 0;
        matrix[i][v2] = 0;
    }
}

void collapse_edge(int** matrix, int v1, int v2) {
    matrix[v1][v2] = 0;
    matrix[v2][v1] = 0;
}

void split_vertex(int*** matrix, int* vertices, int v) {
    int new_size = *vertices + 1;
    *matrix = (int**)realloc(*matrix, new_size * sizeof(int*));
    for (int i = 0; i < new_size; i++) {
        (*matrix)[i] = (int*)realloc((*matrix)[i], new_size * sizeof(int));
    }

    for (int i = 0; i < *vertices; i++) {
        (*matrix)[*vertices][i] = (*matrix)[v][i];
        (*matrix)[i][*vertices] = (*matrix)[i][v];
    }

    (*vertices)++;
}

void free_matrix(int** matrix, int vertices) {
    for (int i = 0; i < vertices; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int main() {
    setlocale(LC_ALL, "RUS");
    srand(time(NULL));
    int vertices;
    printf("Введите количество вершин: ");
    scanf("%d", &vertices);

    if (vertices < 1) {
        printf("Ошибка: количество вершин должно быть больше 0.\n");
        return 1;
    }

    int** M = (int**)malloc(vertices * sizeof(int*));
    for (int i = 0; i < vertices; i++) {
        M[i] = (int*)malloc(vertices * sizeof(int));
    }

    generate_adjacency_matrix(M, vertices);
    print_adjacency_matrix(M, vertices);

    int operation, v1, v2;
    while (1) {
        printf("\nВыберите операцию:\n");
        printf("1. Отождествление вершин\n");
        printf("2. Стягивание ребра\n");
        printf("3. Расщепление вершины\n");
        printf("4. Выход\n");
        scanf("%d", &operation);

        if (operation == 4) {
            break;
        }

        switch (operation) {
        case 1:
            printf("Введите номера вершин для отождествления (0-%d): ", vertices - 1);
            scanf("%d %d", &v1, &v2);
            if (v1 < vertices && v2 < vertices) {
                merge_vertices(M, vertices, v1, v2);
                printf("\nМатрица после отождествления вершин %d и %d:\n", v1, v2);
                print_adjacency_matrix(M, vertices);
            }
            else {
                printf("Неверные номера вершин!\n");
            }
            break;

        case 2:
            printf("Введите номера вершин для стягивания ребра (0-%d): ", vertices - 1);
            scanf("%d %d", &v1, &v2);
            if (v1 < vertices && v2 < vertices) {
                collapse_edge(M, v1, v2);
                printf("\nМатрица после стягивания ребра между вершинами %d и %d:\n", v1, v2);
                print_adjacency_matrix(M, vertices);
            }
            else {
                printf("Неверные номера вершин!\n");
            }
            break;

        case 3:
            printf("Введите номер вершины для расщепления (0-%d): ", vertices - 1);
            scanf("%d", &v1);
            if (v1 < vertices) {
                split_vertex(&M, &vertices, v1);
                printf("\nМатрица после расщепления вершины %d:\n", v1);
                print_adjacency_matrix(M, vertices);
            }
            else {
                printf("Неверный номер вершины!\n");
            }
            break;

        default:
            printf("Некорректный выбор операции!\n");
        }
    }

    free_matrix(M, vertices);

    return 0;
}
