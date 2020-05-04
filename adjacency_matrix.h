#ifndef _ADJACENCY_MATRIX_H_
#define _ADJACENCY_MATRIX_H_

#include "fifo.h"

struct graph {
  size_t size;                // number of vertices
  int **matrix;               // adjacency matrix
};

struct graph *graph_create(size_t size) {
  struct graph* new_graph = (struct graph*)malloc(sizeof(struct graph));
  new_graph->size = size;
  new_graph->matrix = (int**)malloc(sizeof(int*) * size);
    
  for (size_t i = 0; i < size; ++i) {
    new_graph->matrix[i] = (int*)malloc(sizeof(int) * size);
    memset(&new_graph->matrix[i][0], 0, sizeof(int) * size);
  }

  return new_graph;
}

void graph_destroy(struct graph *g) {
  for (size_t i = 0; i < g->size; ++i) {
    free(g->matrix[i]);
  }

  free(g->matrix);
  free(g);
}

void graph_add_edge(struct graph *g, int i, int j) {
  g->matrix[i][j] = 1;
}

bool graph_has_edge(struct graph *g, int i, int j) {
  if (g->matrix[i][j])
    return true;
  return false;
}

void dfs(struct graph *g, int i, int *visited) {
  if (!visited[i]) {
    visited[i] = 1;
    for (size_t j = 0; j < g->size; ++j) {
      if (graph_has_edge(g, i, j)) {
        dfs(g, j, visited);
      }
    }
  }
}

void bfs(struct graph *g, int *visited) {
  struct fifo* queue = fifo_create(g->size);
  fifo_enqueue(queue, 0);

  while (!fifo_is_empty(queue)) {
    int i = fifo_dequeue(queue);
    visited[i] = 1;
    for (size_t j = 0; j < g->size; ++j) {
      if (!visited[j] && graph_has_edge(g, i, j)) {
        fifo_enqueue(queue, j);
        visited[j] = 1;
      }
    }
  }
}
#endif
