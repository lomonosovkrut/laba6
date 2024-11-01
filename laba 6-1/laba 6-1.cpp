#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#define MAX_VERTICES 10  // Максимальное количество вершин в графе

// Структура для представления списка смежности
typedef struct Node {
    int vertex;          // Номер вершины
    struct Node* next;   // Указатель на следующий элемент списка
} Node;

typedef struct {
    Node* head; // Указатель на голову списка
} AdjList;

void generate_adjacency_matrix(int matrix[MAX_VERTICES][MAX_VERTICES], int vertices) {
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

void print_adjacency_matrix(int matrix[MAX_VERTICES][MAX_VERTICES], int vertices) {
    setlocale(LC_ALL, "RUS");
    printf("Матрица смежности:\n");
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void convert_to_adjacency_list(int matrix[MAX_VERTICES][MAX_VERTICES], AdjList list[MAX_VERTICES], int vertices) {
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

void print_adjacency_list(AdjList list[MAX_VERTICES], int vertices) {
    setlocale(LC_ALL, "RUS");
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

void free_adjacency_list(AdjList list[MAX_VERTICES], int vertices) {
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
    srand(time(NULL));

    int vertices = 5; // Количество вершин в графах
    int M1[MAX_VERTICES][MAX_VERTICES], M2[MAX_VERTICES][MAX_VERTICES];

    // Генерация первой матрицы смежности
    generate_adjacency_matrix(M1, vertices);
    print_adjacency_matrix(M1, vertices);

    // Генерация второй матрицы смежности
    generate_adjacency_matrix(M2, vertices);
    print_adjacency_matrix(M2, vertices);

    // Преобразование первой матрицы в список смежности
    AdjList list1[MAX_VERTICES];
    convert_to_adjacency_list(M1, list1, vertices);
    print_adjacency_list(list1, vertices);

    // Преобразование второй матрицы в список смежности
    AdjList list2[MAX_VERTICES];
    convert_to_adjacency_list(M2, list2, vertices);
    print_adjacency_list(list2, vertices);

    // Освобождение памяти
    free_adjacency_list(list1, vertices);
    free_adjacency_list(list2, vertices);

    return 0;
}