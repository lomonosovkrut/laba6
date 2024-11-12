#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

void generate_adjacency_matrix(int** matrix, int vertices) {
    for (int i = 0; i < vertices; i++) {
        for (int j = i; j < vertices; j++) {
            if (i == j) {
                matrix[i][j] = 0; // Нет петель
            }
            else {
                matrix[i][j] = rand() % 2; // Случайное значение 0 или 1
                matrix[j][i] = matrix[i][j]; // Обеспечиваем симметричность для неориентированного графа
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

void cartesian_product(int** g1, int vertices1, int** g2, int vertices2, int*** result, int* result_vertices) {
    *result_vertices = vertices1 * vertices2; // Общее количество вершин в графе G
    *result = (int**)malloc(*result_vertices * sizeof(int*));
    for (int i = 0; i < *result_vertices; i++) {
        (*result)[i] = (int*)malloc(*result_vertices * sizeof(int));
        for (int j = 0; j < *result_vertices; j++) {
            (*result)[i][j] = 0; // Инициализация всех рёбер нулями
        }
    }

    for (int i = 0; i < vertices1; i++) {
        for (int j = 0; j < vertices2; j++) {
            for (int k = 0; k < vertices2; k++) {
                if (g2[j][k] == 1) {
                    (*result)[i * vertices2 + j][i * vertices2 + k] = 1; // vk и vl смежны в G2
                }
            }
            for (int k = 0; k < vertices1; k++) {
                if (g1[i][k] == 1) {
                    (*result)[i * vertices2 + k][j * vertices2 + j] = 1; // zi и zj смежны в G1
                }
            }
        }
    }
}

int main() {
    setlocale(LC_ALL, "RUS");
    srand(time(NULL));

    int vertices1, vertices2;
    printf("Введите количество вершин для графа G1: ");
    scanf("%d", &vertices1);
    printf("Введите количество вершин для графа G2: ");
    scanf("%d", &vertices2);

    // Выделение памяти для матриц смежности
    int** G1 = (int**)malloc(vertices1 * sizeof(int*));
    int** G2 = (int**)malloc(vertices2 * sizeof(int*));
    for (int i = 0; i < vertices1; i++) {
        G1[i] = (int*)malloc(vertices1 * sizeof(int));
    }
    for (int i = 0; i < vertices2; i++) {
        G2[i] = (int*)malloc(vertices2 * sizeof(int));
    }

    // Генерация матриц смежности
    generate_adjacency_matrix(G1, vertices1);
    generate_adjacency_matrix(G2, vertices2);

    // Вывод сгенерированных матриц
    printf("\nМатрица смежности графа G1:\n");
    print_adjacency_matrix(G1, vertices1);
    printf("\nМатрица смежности графа G2:\n");
    print_adjacency_matrix(G2, vertices2);

    // Выполнение декартова произведения графов
    int** result;
    int result_vertices;
    cartesian_product(G1, vertices1, G2, vertices2, &result, &result_vertices);

    // Вывод результата декартова произведения
    printf("\nМатрица смежности декартова произведения G = G1 X G2:\n");
    print_adjacency_matrix(result, result_vertices);

    // Освобождение выделенной памяти
    for (int i = 0; i < vertices1; i++) {
        free(G1[i]);
    }
    for (int i = 0; i < vertices2; i++) {
        free(G2[i]);
    }
    for (int i = 0; i < result_vertices; i++) {
        free(result[i]);
    }
    free(G1);
    free(G2);
    free(result);

    return 0;
}