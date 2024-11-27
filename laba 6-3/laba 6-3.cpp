
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

// Структура для представления списка смежности
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct AdjacencyList {
    Node** list;
    int* list_sizes;
    int size;
} AdjacencyList;

void generate_adjacency_matrix(int** matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix[i][j] = rand() % 2;
        }
    }
}

void print_matrix(int** matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void adjacency_matrix_to_list(int** matrix, int size, AdjacencyList* adj_list) {
    adj_list->list = (Node**)calloc(size, sizeof(Node*));
    adj_list->list_sizes = (int*)calloc(size, sizeof(int));
    adj_list->size = size;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (matrix[i][j]) {
                Node* new_node = (Node*)malloc(sizeof(Node));
                new_node->vertex = j;
                new_node->next = adj_list->list[i];
                adj_list->list[i] = new_node;
                adj_list->list_sizes[i]++;
            }
        }
    }
}

void print_adjacency_list(AdjacencyList* adj_list) {
    for (int i = 0; i < adj_list->size; i++) {
        printf("%d: ", i);
        Node* current = adj_list->list[i];
        while (current) {
            printf("%d ", current->vertex);
            current = current->next;
        }
        printf("\n");
    }
}

void free_adjacency_list(AdjacencyList* adj_list) {
    for (int i = 0; i < adj_list->size; i++) {
        Node* current = adj_list->list[i];
        while (current) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(adj_list->list);
    free(adj_list->list_sizes);
}

int** union_graphs(int** M1, int** M2, int size1, int size2) {
    int** result = (int**)malloc(((size1 > size2) ? size1 : size2) * sizeof(int*));
    for (int i = 0; i < ((size1 > size2) ? size1 : size2); i++) {
        result[i] = (int*)calloc(((size1 > size2) ? size1 : size2), sizeof(int));
    }

    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size1; j++) {
            result[i][j] = M1[i][j];
        }
    }

    for (int i = 0; i < size2; i++) {
        for (int j = 0; j < size2; j++) {
            result[i][j] |= M2[i][j];
        }
    }

    return result;
}

int** intersection_graphs(int** M1, int** M2, int size1, int size2) {
    int** result = (int**)malloc(((size1 < size2) ? size1 : size2) * sizeof(int*));
    for (int i = 0; i < ((size1 < size2) ? size1 : size2); i++) {
        result[i] = (int*)calloc(((size1 < size2) ? size1 : size2), sizeof(int));
    }

    for (int i = 0; i < ((size1 < size2) ? size1 : size2); i++) {
        for (int j = 0; j < ((size1 < size2) ? size1 : size2); j++) {
            result[i][j] = M1[i][j] & M2[i][j];
        }
    }

    return result;
}

int** ring_sum_graphs(int** M1, int** M2, int size1, int size2) {
    int** result = (int**)malloc(((size1 > size2) ? size1 : size2) * sizeof(int*));
    for (int i = 0; i < ((size1 > size2) ? size1 : size2); i++) {
        result[i] = (int*)calloc(((size1 > size2) ? size1 : size2), sizeof(int));
    }

    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size1; j++) {
            result[i][j] = (M1[i][j] + M2[i][j]) % 2;
        }
    }

    return result;
}

void free_matrix(int** matrix, int size) {
    for (int i = 0; i < size; i++) {
        free(matrix[i]);
    }
    free(matrix);
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

    // Преобразуем матрицы смежности в списки смежности
    AdjacencyList adj_list1, adj_list2;
    adjacency_matrix_to_list(M1, size1, &adj_list1);
    adjacency_matrix_to_list(M2, size2, &adj_list2);

    // Выводим списки смежности
    printf("\nСписок смежности графа G1:\n");
    print_adjacency_list(&adj_list1);
    printf("\nСписок смежности графа G2:\n");
    print_adjacency_list(&adj_list2);

    // Выполняем операции над графами
    int** union_matrix = union_graphs(M1, M2, size1, size2);
    int** intersection_matrix = intersection_graphs(M1, M2, size1, size2);
    int** ring_sum_matrix = ring_sum_graphs(M1, M2, size1, size2);

    // Преобразуем результаты операций в списки смежности
    AdjacencyList union_list, intersection_list, ring_sum_list;
    adjacency_matrix_to_list(union_matrix, (size1 > size2) ? size1 : size2, &union_list);
    adjacency_matrix_to_list(intersection_matrix, (size1 < size2) ? size1 : size2, &intersection_list);
    adjacency_matrix_to_list(ring_sum_matrix, (size1 > size2) ? size1 : size2, &ring_sum_list);

    // Выводим результаты операций
    printf("\nМатрица объединения графов:\n");
    print_matrix(union_matrix, (size1 > size2) ? size1 : size2);
    printf("\nСписок смежности объединения графов:\n");
    print_adjacency_list(&union_list);

    printf("\nМатрица пересечения графов:\n");
    print_matrix(intersection_matrix, (size1 < size2) ? size1 : size2);
    printf("\nСписок смежности пересечения графов:\n");
    print_adjacency_list(&intersection_list);

    printf("\nМатрица кольцевой суммы графов:\n");
    print_matrix(ring_sum_matrix, (size1 > size2) ? size1 : size2);
    printf("\nСписок смежности кольцевой суммы графов:\n");
    print_adjacency_list(&ring_sum_list);

    // Освобождаем выделенную память
    free_matrix(M1, size1);
    free_matrix(M2, size2);
    free_matrix(union_matrix, (size1 > size2) ? size1 : size2);
    free_matrix(intersection_matrix, (size1 < size2) ? size1 : size2);
    free_matrix(ring_sum_matrix, (size1 > size2) ? size1 : size2);

    free_adjacency_list(&adj_list1);
    free_adjacency_list(&adj_list2);
    free_adjacency_list(&union_list);
    free_adjacency_list(&intersection_list);
    free_adjacency_list(&ring_sum_list);

    return 0;
}