
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>


// Структура для представления списка смежности
typedef struct Node {
    int vertex;          // Номер вершины
    struct Node* next;   // Указатель на следующий элемент списка
} Node;

typedef struct {
    Node* head; // Указатель на голову списка
} AdjList;

void generate_adjacency_matrix(int** matrix, int vertices) {
    for (int i = 0; i < vertices; i++) {
        for (int j = i; j < vertices; j++) {
            if (i == j) {
                matrix[i][j] = 0; // Нет петель
            }
            else {
                matrix[i][j] = rand() % 2; // Генерация наличия ребра (0 или 1)
                matrix[j][i] = matrix[i][j]; // Симметричность для неориентированного графа
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

void convert_to_adjacency_list(int** matrix, AdjList* list, int vertices) {
    for (int i = 0; i < vertices; i++) {
        list[i].head = NULL; // Инициализация списка
        for (int j = 0; j < vertices; j++) {
            if (matrix[i][j] == 1) {
                // Создание нового узла для списка
                Node* new_node = (Node*)malloc(sizeof(Node));
                new_node->vertex = j; // Установка номера вершины
                new_node->next = list[i].head; // Указатель на предыдущую голову списка
                list[i].head = new_node; // Обновление головы списка
            }
        }
    }
}

void print_adjacency_list(AdjList* list, int vertices) {
    printf("Список смежности:\n");
    for (int i = 0; i < vertices; i++) {
        printf("Вершина %d: ", i);
        Node* current = list[i].head;
        while (current != NULL) {
            printf("%d -> ", current->vertex);
            current = current->next;
        }
        printf("NULL\n");
    }
}

void free_adjacency_list(AdjList* list, int vertices) {
    for (int i = 0; i < vertices; i++) {
        Node* current = list[i].head;
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
}

int main() {
    setlocale(LC_ALL, "RUS");
    srand(time(NULL));
    int vertices1, vertices2;

    printf("Введите количество вершин для матрицы M1: ");
    scanf("%d", &vertices1);

    printf("Введите количество вершин для матрицы M2: ");
    scanf("%d", &vertices2);

    // Проверка на допустимое количество вершин
    if (vertices1 < 1 || vertices2 < 1) {
        printf("Ошибка: количество вершин должно быть больше 0.\n");
        return 1;
    }

    // Динамическое выделение памяти для матриц смежности
    int** M1 = (int**)malloc(vertices1 * sizeof(int*));
    int** M2 = (int**)malloc(vertices2 * sizeof(int*));
    for (int i = 0; i < vertices1; i++) {
        M1[i] = (int*)malloc(vertices1 * sizeof(int));
    }
    for (int i = 0; i < vertices2; i++) {
        M2[i] = (int*)malloc(vertices2 * sizeof(int));
    }

    // Генерация первой матрицы смежности
    generate_adjacency_matrix(M1, vertices1);
    print_adjacency_matrix(M1, vertices1);

    // Генерация второй матрицы смежности
    generate_adjacency_matrix(M2, vertices2);
    print_adjacency_matrix(M2, vertices2);

    // Преобразование первой матрицы в список смежности
    AdjList* list1 = (AdjList*)malloc(vertices1 * sizeof(AdjList));
    convert_to_adjacency_list(M1, list1, vertices1);
    print_adjacency_list(list1, vertices1);

    // Преобразование второй матрицы в список смежности
    AdjList* list2 = (AdjList*)malloc(vertices2 * sizeof(AdjList));
    convert_to_adjacency_list(M2, list2, vertices2);
    print_adjacency_list(list2, vertices2);

    // Освобождение памяти
    free_adjacency_list(list1, vertices1);
    free_adjacency_list(list2, vertices2);
    free(list1);
    free(list2);

    for (int i = 0; i < vertices1; i++) {
        free(M1[i]);
    }
    for (int i = 0; i < vertices2; i++) {
        free(M2[i]);
    }
    free(M1);
    free(M2);

    return 0;
}