#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#define MAX_VERTICES 10

// Функция для инициализации матрицы смежности
void init_adjacency_matrix(int matrix[MAX_VERTICES][MAX_VERTICES], int vertices) {
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            matrix[i][j] = 0;
        }
    }
}

// Функция для генерации матрицы смежности
void generate_adjacency_matrix(int matrix[MAX_VERTICES][MAX_VERTICES], int vertices) {
    for (int i = 0; i < vertices; i++) {
        for (int j = i + 1; j < vertices; j++) {
            // Генерируем случайное значение (0 или 1) для рёбер
            matrix[i][j] = rand() % 2;
            matrix[j][i] = matrix[i][j]; // Симметричная матрица
        }
    }
}

// Функция для вывода матрицы смежности
void print_adjacency_matrix(int matrix[MAX_VERTICES][MAX_VERTICES], int vertices) {
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Объединение графов G1 и G2
void union_graphs(int G1[MAX_VERTICES][MAX_VERTICES], int G2[MAX_VERTICES][MAX_VERTICES], int result[MAX_VERTICES][MAX_VERTICES], int vertices) {
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            result[i][j] = G1[i][j] | G2[i][j]; // Логическое ИЛИ для объединения
        }
    }
}

// Пересечение графов G1 и G2
void intersection_graphs(int G1[MAX_VERTICES][MAX_VERTICES], int G2[MAX_VERTICES][MAX_VERTICES], int result[MAX_VERTICES][MAX_VERTICES], int vertices) {
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            result[i][j] = G1[i][j] & G2[i][j]; // Логическое И для пересечения
        }
    }
}

// Кольцевая сумма графов G1 и G2
void ring_sum_graphs(int G1[MAX_VERTICES][MAX_VERTICES], int G2[MAX_VERTICES][MAX_VERTICES], int result[MAX_VERTICES][MAX_VERTICES], int vertices) {
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            // Кольцевая сумма: (G1 XOR G2) + (G1 AND G2)
            result[i][j] = (G1[i][j] ^ G2[i][j]) | (G1[i][j] && G2[i][j]);
        }
    }
}

int main() {
    setlocale(LC_ALL, "RUS");
    srand(time(NULL)); // Инициализация генератора случайных чисел
    int vertices;

    printf("Введите количество вершин (максимум %d): ", MAX_VERTICES);
    scanf("%d", &vertices);

    if (vertices > MAX_VERTICES) {
        printf("Количество вершин превышает максимальное значение.\n");
        return 1;
    }

    int G1[MAX_VERTICES][MAX_VERTICES], G2[MAX_VERTICES][MAX_VERTICES], result[MAX_VERTICES][MAX_VERTICES];

    // Инициализация матриц смежности
    init_adjacency_matrix(G1, vertices);
    init_adjacency_matrix(G2, vertices);
    init_adjacency_matrix(result, vertices);

    // Генерация матрицы смежности для первого графа
    generate_adjacency_matrix(G1, vertices);
    printf("Сгенерированная матрица смежности для графа G1:\n");
    print_adjacency_matrix(G1, vertices);

    // Генерация матрицы смежности для второго графа
    generate_adjacency_matrix(G2, vertices);
    printf("Сгенерированная матрица смежности для графа G2:\n");
    print_adjacency_matrix(G2, vertices);

    // Объединение графов
    union_graphs(G1, G2, result, vertices);
    printf("Результат объединения G1 и G2:\n");
    print_adjacency_matrix(result, vertices);

    // Пересечение графов
    intersection_graphs(G1, G2, result, vertices);
    printf("Результат пересечения G1 и G2:\n");
    print_adjacency_matrix(result, vertices);

    // Кольцевая сумма графов
    ring_sum_graphs(G1, G2, result, vertices);
    printf("Результат кольцевой суммы G1 и G2:\n");
    print_adjacency_matrix(result, vertices);

    return 0;
}