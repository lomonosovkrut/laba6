#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

// Функция для генерации матрицы смежности случайного графа
void generate_adjacency_matrix(int** matrix, int size) {
    // Инициализируем матрицу нулями
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix[i][j] = 0;
        }
    }

    // Случайно заполняем верхний треугольник матрицы для создания неориентированных рёбер
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (rand() % 2) { // С вероятностью 0.5 создаём ребро
                matrix[i][j] = 1;
                matrix[j][i] = 1; // Граф неориентированный
            }
        }
    }
}

// Функция для вывода матрицы смежности
void print_matrix(int** matrix, int size) {
    printf("Матрица смежности:\n");
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Функция для освобождения памяти матрицы
void free_matrix(int** matrix, int size) {
    for (int i = 0; i < size; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// Функция для объединения двух графов
int** union_graphs(int** m1, int** m2, int size1, int size2) {
    int max_size = (size1 > size2) ? size1 : size2;
    int** union_matrix = (int**)malloc(max_size * sizeof(int*));

    for (int i = 0; i < max_size; i++) {
        union_matrix[i] = (int*)calloc(max_size, sizeof(int));
        for (int j = 0; j < max_size; j++) {
            int edge1 = (i < size1 && j < size1) ? m1[i][j] : 0;
            int edge2 = (i < size2 && j < size2) ? m2[i][j] : 0;
            union_matrix[i][j] = edge1 | edge2; // Операция объединения (OR)
        }
    }

    return union_matrix;
}

// Функция для пересечения двух графов
int** intersection_graphs(int** m1, int** m2, int size1, int size2) {
    int min_size = (size1 < size2) ? size1 : size2;
    int** intersection_matrix = (int**)malloc(min_size * sizeof(int*));

    for (int i = 0; i < min_size; i++) {
        intersection_matrix[i] = (int*)calloc(min_size, sizeof(int));
        for (int j = 0; j < min_size; j++) {
            int edge1 = (i < size1 && j < size1) ? m1[i][j] : 0;
            int edge2 = (i < size2 && j < size2) ? m2[i][j] : 0;
            intersection_matrix[i][j] = edge1 & edge2; // Операция пересечения (AND)
        }
    }

    return intersection_matrix;
}

// Функция для кольцевой суммы двух графов
int** ring_sum_graphs(int** m1, int** m2, int size1, int size2) {
    int max_size = (size1 > size2) ? size1 : size2;
    int** ring_sum_matrix = (int**)malloc(max_size * sizeof(int*));

    for (int i = 0; i < max_size; i++) {
        ring_sum_matrix[i] = (int*)calloc(max_size, sizeof(int));
        for (int j = 0; j < max_size; j++) {
            int edge1 = (i < size1 && j < size1) ? m1[i][j] : 0;
            int edge2 = (i < size2 && j < size2) ? m2[i][j] : 0;
            ring_sum_matrix[i][j] = edge1 ^ edge2; // Операция кольцевой суммы (XOR)
        }
    }

    return ring_sum_matrix;
}

int main() {
    setlocale(LC_ALL, "RUS");
    srand(time(NULL));
    int size1, size2;

    printf("Введите размер первого графа: ");
    scanf("%d", &size1);
    printf("Введите размер второго графа: ");
    scanf("%d", &size2);

    // Выделяем память для матриц смежности
    int** M1 = (int**)malloc(size1 * sizeof(int*));
    int** M2 = (int**)malloc(size2 * sizeof(int*));

    for (int i = 0; i < size1; i++) {
        M1[i] = (int*)malloc(size1 * sizeof(int));
    }

    for (int i = 0; i < size2; i++) {
        M2[i] = (int*)malloc(size2 * sizeof(int));
    }

    // Генерируем матрицы смежности
    generate_adjacency_matrix(M1, size1);
    generate_adjacency_matrix(M2, size2);

    // Выводим сгенерированные матрицы
    printf("\nМатрица смежности графа G1:\n");
    print_matrix(M1, size1);
    printf("\nМатрица смежности графа G2:\n");
    print_matrix(M2, size2);

    // Выполняем операции над графами
    int** union_matrix = union_graphs(M1, M2, size1, size2);
    int** intersection_matrix = intersection_graphs(M1, M2, size1, size2);
    int** ring_sum_matrix = ring_sum_graphs(M1, M2, size1, size2);

    // Выводим результаты операций
    printf("\nМатрица объединения графов:\n");
    print_matrix(union_matrix, (size1 > size2) ? size1 : size2);
    printf("\nМатрица пересечения графов:\n");
    print_matrix(intersection_matrix, (size1 < size2) ? size1 : size2);
    printf("\nМатрица кольцевой суммы графов:\n");
    print_matrix(ring_sum_matrix, (size1 > size2) ? size1 : size2);

    // Освобождаем выделенную память
    free_matrix(M1, size1);
    free_matrix(M2, size2);
    free_matrix(union_matrix, (size1 > size2) ? size1 : size2);
    free_matrix(intersection_matrix, (size1 < size2) ? size1 : size2);
    free_matrix(ring_sum_matrix, (size1 > size2) ? size1 : size2);

    return 0;
}