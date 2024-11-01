#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#define MAX_SIZE 10  // Максимальный размер графа

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

// Функция для отождествления вершин
void merge_vertices(int matrix[MAX_SIZE][MAX_SIZE], int size, int v1, int v2) {
    for (int i = 0; i < size; i++) {
        matrix[v1][i] = matrix[v1][i] | matrix[v2][i]; // Объединяем рёбра
        matrix[i][v1] = matrix[i][v1] | matrix[i][v2]; // Объединяем рёбра
    }
    // Удаляем вершину v2
    for (int i = 0; i < size; i++) {
        matrix[v2][i] = 0;
        matrix[i][v2] = 0;
    }
}

// Функция для стягивания ребра
void collapse_edge(int matrix[MAX_SIZE][MAX_SIZE], int v1, int v2) {
    matrix[v1][v2] = 0;
    matrix[v2][v1] = 0;
}

// Функция для расщепления вершины
void split_vertex(int matrix[MAX_SIZE][MAX_SIZE], int* size, int v) {
    setlocale(LC_ALL, "RUS");
    if (*size >= MAX_SIZE) {
        printf("Достигнуто максимальное количество вершин!\n");
        return;
    }

    for (int i = 0; i < *size; i++) {
        if (matrix[v][i] == 1) {
            matrix[*size][i] = 1; // Новая вершина соединяется с соседями
            matrix[i][*size] = 1; // Обеспечиваем симметричность
        }
    }
    (*size)++; // Увеличиваем размер графа
}

// Функция для вывода списка смежности
void print_adjacency_list(int matrix[MAX_SIZE][MAX_SIZE], int size) {
    setlocale(LC_ALL, "RUS");
    printf("\nСписок смежности:\n");
    for (int i = 0; i < size; i++) {
        printf("%d: ", i);
        for (int j = 0; j < size; j++) {
            if (matrix[i][j] == 1) {
                printf("%d ", j);
            }
        }
        printf("\n");
    }
}

int main() {
    setlocale(LC_ALL, "RUS");
    srand(time(NULL)); // Инициализация генератора случайных чисел

    int size;
    int M[MAX_SIZE][MAX_SIZE] = { 0 };

    // Запрос количества вершин у пользователя
    printf("Введите количество вершин в графе (макс. %d): ", MAX_SIZE);
    scanf("%d", &size);
    if (size > MAX_SIZE) {
        printf("Количество вершин превышает максимальное значение. Установлено на %d.\n", MAX_SIZE);
        size = MAX_SIZE;
    }

    // Генерация матрицы смежности
    generate_adjacency_matrix(M, size);

    // Вывод сгенерированной матрицы
    printf("Матрица смежности:\n");
    print_adjacency_matrix(M, size);

    int operation, v1, v2;
    while (1) {
        // Выбор операции
        printf("\nВыберите операцию:\n");
        printf("1. Отождествление вершин\n");
        printf("2. Стягивание ребра\n");
        printf("3. Расщепление вершины\n");
        printf("4. Выход\n");
        scanf("%d", &operation);

        if (operation == 4) {
            break; // Выход из программы
        }

        switch (operation) {
        case 1:
            printf("Введите номера вершин для отождествления (0-%d): ", size - 1);
            scanf("%d %d", &v1, &v2);
            if (v1 < size && v2 < size) {
                merge_vertices(M, size, v1, v2);
                printf("\nМатрица после отождествления вершин %d и %d:\n", v1, v2);
                print_adjacency_matrix(M, size);
            }
            else {
                printf("Неверные номера вершин!\n");
            }
            break;

        case 2:
            printf("Введите номера вершин для стягивания ребра (0-%d): ", size - 1);
            scanf("%d %d", &v1, &v2);
            if (v1 < size && v2 < size) {
                collapse_edge(M, v1, v2);
                printf("\nМатрица после стягивания ребра между вершинами %d и %d:\n", v1, v2);
                print_adjacency_matrix(M, size);
            }
            else {
                printf("Неверные номера вершин!\n");
            }
            break;

        case 3:
            printf("Введите номер вершины для расщепления (0-%d): ", size - 1);
            scanf("%d", &v1);
            if (v1 < size) {
                split_vertex(M, &size, v1);
                printf("\nМатрица после расщепления вершины %d:\n", v1);
                print_adjacency_matrix(M, size);
            }
            else {
                printf("Неверный номер вершины!\n");
            }
            break;

        default:
            printf("Некорректный выбор операции!\n");
        }

        // Вывод списка смежности
        print_adjacency_list(M, size);
    }

    return 0;
}