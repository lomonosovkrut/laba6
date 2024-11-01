#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#define MAX_SIZE 5  // Максимальный размер графа

// Функция для генерации матрицы смежности
void generate_adjacency_matrix(int matrix[MAX_SIZE][MAX_SIZE], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i == j) {
                matrix[i][j] = 0; // Нет петель
            }
            else {
                matrix[i][j] = rand() % 2; // Случайное значение 0 или 1
            }
        }
    }

    // Обеспечиваем симметричность для неориентированного графа
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            matrix[j][i] = matrix[i][j]; // Копируем значения
        }
    }
}

// Функция для вывода матрицы смежности
void print_adjacency_matrix(int matrix[MAX_SIZE][MAX_SIZE], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Функция для выполнения декартова произведения графов
void cartesian_product(int M1[MAX_SIZE][MAX_SIZE], int size1, int M2[MAX_SIZE][MAX_SIZE], int size2, int result[MAX_SIZE * MAX_SIZE][MAX_SIZE * MAX_SIZE]) {
    int new_size = size1 * size2;

    // Инициализация матрицы результата
    for (int i = 0; i < new_size; i++) {
        for (int j = 0; j < new_size; j++) {
            result[i][j] = 0;
        }
    }

    // Заполнение матрицы результата
    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size2; j++) {
            for (int k = 0; k < size2; k++) {
                if (M1[i][j] == 1) {
                    result[i * size2 + j][i * size2 + k] = 1; // Связи в первой вершине
                }
            }
            for (int k = 0; k < size1; k++) {
                if (M2[j][k] == 1) {
                    result[i * size2 + j][k * size2 + j] = 1; // Связи во второй вершине
                }
            }
        }
    }
}

// Перегруженная функция для вывода матрицы смежности декартова произведения
void print_adjacency_matrix_large(int matrix[MAX_SIZE * MAX_SIZE][MAX_SIZE * MAX_SIZE], int size1, int size2) {
    int new_size = size1 * size2;
    for (int i = 0; i < new_size; i++) {
        for (int j = 0; j < new_size; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    setlocale(LC_ALL, "RUS");
    srand(time(NULL)); // Инициализация генератора случайных чисел

    int size1, size2;
    int M1[MAX_SIZE][MAX_SIZE] = { 0 };
    int M2[MAX_SIZE][MAX_SIZE] = { 0 };
    int result[MAX_SIZE * MAX_SIZE][MAX_SIZE * MAX_SIZE] = { 0 };

    // Запрос количества вершин у пользователя для графа G1
    printf("Введите количество вершин в графе G1 (макс. %d): ", MAX_SIZE);
    scanf("%d", &size1);
    if (size1 > MAX_SIZE) {
        printf("Количество вершин превышает максимальное значение. Установлено на %d.\n", MAX_SIZE);
        size1 = MAX_SIZE;
    }

    // Генерация матрицы смежности для графа G1
    generate_adjacency_matrix(M1, size1);
    printf("\nМатрица смежности G1:\n");
    print_adjacency_matrix(M1, size1);

    // Запрос количества вершин у пользователя для графа G2
    printf("Введите количество вершин в графе G2 (макс. %d): ", MAX_SIZE);
    scanf("%d", &size2);
    if (size2 > MAX_SIZE) {
        printf("Количество вершин превышает максимальное значение. Установлено на %d.\n", MAX_SIZE);
        size2 = MAX_SIZE;
    }

    // Генерация матрицы смежности для графа G2
    generate_adjacency_matrix(M2, size2);
    printf("\nМатрица смежности G2:\n");
    print_adjacency_matrix(M2, size2);

    // Выполнение декартова произведения графов
    cartesian_product(M1, size1, M2, size2, result);
    printf("\nМатрица смежности декартова произведения G = G1 X G2:\n");
    print_adjacency_matrix_large(result, size1, size2);

    return 0;
}