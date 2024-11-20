
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

void remove_vertex(int** matrix, int* vertices, int v) {
    for (int i = v; i < *vertices - 1; i++) {
        for (int j = 0; j < *vertices; j++) {
            matrix[i][j] = matrix[i + 1][j];
        }
    }
    for (int i = 0; i < *vertices - 1; i++) {
        for (int j = v; j < *vertices - 1; j++) {
            matrix[i][j] = matrix[i][j + 1];
        }
    }
    for (int i = 0; i < *vertices; i++) {
        int* temp = (int*)realloc(matrix[i], (*vertices - 1) * sizeof(int));
        if (temp == NULL) {
            printf("Ошибка перераспределения памяти!\n");
            exit(1);
        }
        matrix[i] = temp;
    }
    *vertices -= 1;
}

void merge_vertices(int** matrix, int* vertices, int v1, int v2) {
    if (v1 == v2) return; // Нельзя объединить вершину с собой
    for (int i = 0; i < *vertices; i++) {
        matrix[v1][i] = matrix[v1][i] | matrix[v2][i];
        matrix[i][v1] = matrix[i][v1] | matrix[i][v2];
    }
    remove_vertex(matrix, vertices, v2);
}

void collapse_edge(int** matrix, int* vertices, int v1, int v2) {

    for (int i = 0; i < *vertices; i++) {
        matrix[v1][i] = matrix[v1][i] | matrix[v2][i];
        matrix[i][v1] = matrix[i][v1] | matrix[i][v2];
    }
    remove_vertex(matrix, vertices, v2);
}

void split_vertex(int*** matrix, int* vertices, int v) {
    int new_size = *vertices + 1;
    int** temp_matrix = (int**)realloc(*matrix, new_size * sizeof(int*));
    if (temp_matrix == NULL) {
        printf("Ошибка перераспределения памяти!\n");
        exit(1);
    }
    *matrix = temp_matrix;

    for (int i = 0; i < new_size; i++) {
        int* temp_row = (int*)realloc((*matrix)[i], new_size * sizeof(int));
        if (temp_row == NULL) {
            printf("Ошибка перераспределения памяти!\n");
            exit(1);
        }
        (*matrix)[i] = temp_row;
    }

    for (int i = 0; i < new_size; i++) {
        (*matrix)[new_size - 1][i] = 0;
        (*matrix)[i][new_size - 1] = 0;
    }

    // Дублируем связи для новой вершины
    for (int i = 0; i < *vertices; i++) {
        (*matrix)[new_size - 1][i] = (*matrix)[v][i];
        (*matrix)[i][new_size - 1] = (*matrix)[i][v];
    }

    // Обнуляем петлю для новой вершины
    (*matrix)[new_size - 1][new_size - 1] = 0;
    *vertices = new_size;
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
    if (scanf("%d", &vertices) != 1 || vertices < 1) {
        printf("Ошибка: количество вершин должно быть больше 0.\n");
        return 1;
    }

    int** M = (int**)malloc(vertices * sizeof(int*));
    if (M == NULL) {
        printf("Ошибка выделения памяти!\n");
        return 1;
    }
    for (int i = 0; i < vertices; i++) {
        M[i] = (int*)malloc(vertices * sizeof(int));
        if (M[i] == NULL) {
            printf("Ошибка выделения памяти!\n");
            return 1;
        }
    }

    generate_adjacency_matrix(M, vertices);
    print_adjacency_matrix(M, vertices);
    AdjList* list = (AdjList*)malloc(vertices * sizeof(AdjList));
    convert_to_adjacency_list(M, list, vertices);
    print_adjacency_list(list, vertices);

    int operation, v1, v2;
    while (1) {
        printf("\nВыберите операцию:\n");
        printf("1. Отождествление вершин\n");
        printf("2. Стягивание ребра\n");
        printf("3. Расщепление вершины\n");
        printf("4. Выход\n");
        if (scanf("%d", &operation) != 1) {
            printf("Некорректный ввод!\n");
            break;
        }

        if (operation == 4) {
            break;
        }

        switch (operation) {
        case 1:
            printf("Введите номера вершин для отождествления (0-%d): ", vertices - 1);
            if (scanf("%d %d", &v1, &v2) != 2 || v1 >= vertices || v2 >= vertices || v1 < 0 || v2 < 0) {
                printf("Неверные номера вершин!\n");
            }
            else {
                merge_vertices(M, &vertices, v1, v2);
                printf("\nМатрица после отождествления вершин %d и %d:\n", v1, v2);
                print_adjacency_matrix(M, vertices);
                AdjList* list = (AdjList*)malloc(vertices * sizeof(AdjList));
                convert_to_adjacency_list(M, list, vertices);
                print_adjacency_list(list, vertices);

            }
            break;

        case 2:
            printf("Введите номера вершин для стягивания ребра (0-%d): ", vertices - 1);
            if (scanf("%d %d", &v1, &v2) != 2 || v1 >= vertices || v2 >= vertices || v1 < 0 || v2 < 0 || v1 == v2) {
                printf("Неверные номера вершин!\n");
            }
            if (M[v1][v2] == 0) {
                printf("Ребро между вершинами %d и %d отсутствует. Выберите другое ребро.\n", v1, v2);
                break;
            }
            else {
                collapse_edge(M, &vertices, v1, v2);
                printf("\nМатрица после стягивания ребра между вершинами %d и %d:\n", v1, v2);
                print_adjacency_matrix(M, vertices);
                AdjList* list = (AdjList*)malloc(vertices * sizeof(AdjList));
                convert_to_adjacency_list(M, list, vertices);
                print_adjacency_list(list, vertices);

            }
            break;

        case 3:
            printf("Введите номер вершины для расщепления (0-%d): ", vertices - 1);
            if (scanf("%d", &v1) != 1 || v1 >= vertices || v1 < 0) {
                printf("Неверный номер вершины!\n");
            }
            else {
                split_vertex(&M, &vertices, v1);
                printf("\nМатрица после расщепления вершины %d:\n", v1);
                print_adjacency_matrix(M, vertices);
                AdjList* list = (AdjList*)malloc(vertices * sizeof(AdjList));
                convert_to_adjacency_list(M, list, vertices);
                print_adjacency_list(list, vertices);

            }
            break;

        default:
            printf("Некорректный выбор операции!\n");
            break;
        }
    }

    free_matrix(M, vertices);
    return 0;
}
