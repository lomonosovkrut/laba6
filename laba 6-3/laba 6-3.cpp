
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

void generate_adjacency_matrix(int** matrix, int vertices) {
    for (int i = 0; i < vertices; i++) {
        for (int j = i; j < vertices; j++) {
            if (i == j) {
                matrix[i][j] = 0; // No self-loops
            }
            else {
                matrix[i][j] = rand() % 2; // Randomly create edges
                matrix[j][i] = matrix[i][j]; // Ensure the graph is undirected
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

void union_graphs(int** g1, int vertices1, int** g2, int vertices2, int** result) {
    int max_vertices = (vertices1 > vertices2) ? vertices1 : vertices2;
    for (int i = 0; i < max_vertices; i++) {
        for (int j = 0; j < max_vertices; j++) {
            int edge1 = (i < vertices1 && j < vertices1) ? g1[i][j] : 0;
            int edge2 = (i < vertices2 && j < vertices2) ? g2[i][j] : 0;
            result[i][j] = edge1 | edge2; // Union operation
        }
    }
}

void intersection_graphs(int** g1, int vertices1, int** g2, int vertices2, int** result) {
    int max_vertices = (vertices1 > vertices2) ? vertices1 : vertices2;
    for (int i = 0; i < max_vertices; i++) {
        for (int j = 0; j < max_vertices; j++) {
            int edge1 = (i < vertices1 && j < vertices1) ? g1[i][j] : 0;
            int edge2 = (i < vertices2 && j < vertices2) ? g2[i][j] : 0;
            result[i][j] = edge1 & edge2; // Intersection operation
        }
    }
}

void ring_sum_graphs(int** g1, int vertices1, int** g2, int vertices2, int** result) {
    int max_vertices = (vertices1 > vertices2) ? vertices1 : vertices2;
    for (int i = 0; i < max_vertices; i++) {
        for (int j = 0; j < max_vertices; j++) {
            int edge1 = (i < vertices1 && j < vertices1) ? g1[i][j] : 0;
            int edge2 = (i < vertices2 && j < vertices2) ? g2[i][j] : 0;
            result[i][j] = edge1 ^ edge2; // Ring sum operation
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

    // Allocate memory for two adjacency matrices
    int** G1 = (int**)malloc(vertices1 * sizeof(int*));
    int** G2 = (int**)malloc(vertices2 * sizeof(int*));
    for (int i = 0; i < vertices1; i++) {
        G1[i] = (int*)malloc(vertices1 * sizeof(int));
    }
    for (int i = 0; i < vertices2; i++) {
        G2[i] = (int*)malloc(vertices2 * sizeof(int));
    }

    // Generate adjacency matrices
    generate_adjacency_matrix(G1, vertices1);
    generate_adjacency_matrix(G2, vertices2);

    // Print generated matrices
    printf("\nМатрица смежности графа G1:\n");
    print_adjacency_matrix(G1, vertices1);
    printf("\nМатрица смежности графа G2:\n");
    print_adjacency_matrix(G2, vertices2);

    // Allocate memory for result matrices
    int max_vertices = (vertices1 > vertices2) ? vertices1 : vertices2;
    int** union_result = (int**)malloc(max_vertices * sizeof(int*));
    int** intersection_result = (int**)malloc(max_vertices * sizeof(int*));
    int** ring_sum_result = (int**)malloc(max_vertices * sizeof(int*));
    for (int i = 0; i < max_vertices; i++) {
        union_result[i] = (int*)malloc(max_vertices * sizeof(int));
        intersection_result[i] = (int*)malloc(max_vertices * sizeof(int));
        ring_sum_result[i] = (int*)malloc(max_vertices * sizeof(int));
    }

    // Perform graph operations
    union_graphs(G1, vertices1, G2, vertices2, union_result);
    intersection_graphs(G1, vertices1, G2, vertices2, intersection_result);
    ring_sum_graphs(G1, vertices1, G2, vertices2, ring_sum_result);

    // Print results
    printf("\nОбъединение графов G1 и G2:\n");
    print_adjacency_matrix(union_result, max_vertices);
    printf("\nПересечение графов G1 и G2:\n");
    print_adjacency_matrix(intersection_result, max_vertices);
    printf("\nКольцевая сумма графов G1 и G2:\n");
    print_adjacency_matrix(ring_sum_result, max_vertices);

    // Free allocated memory
    for (int i = 0; i < vertices1; i++) {
        free(G1[i]);
    }
    for (int i = 0; i < vertices2; i++) {
        free(G2[i]);
    }
    for (int i = 0; i < max_vertices; i++) {
        free(union_result[i]);
        free(intersection_result[i]);
        free(ring_sum_result[i]);
    }
    free(G1);
    free(G2);
    free(union_result);
    free(intersection_result);
    free(ring_sum_result);

    return 0;
}