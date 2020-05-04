#ifndef _EDGE_LIST_H_
#define _EDGE_LIST_H_

#include <stdbool.h>

struct edge_list {
    size_t size;                // number of edges
    int *vertices;              // adjacent vertices
};

struct graph {
    size_t size;                // number of vertices
    struct edge_list *edges;    // edge lists
};

struct graph *graph_create(size_t size) {
    // TODO: implement this
  struct graph*new_graph = (struct graph*)malloc(sizeof(struct graph));
  new_graph->size = size;
  new_graph->edges = (struct edge_list*)malloc(sizeof(struct edge_list) * size);
  memset(&new_graph->edges[0], 0, sizeof(struct edge_list) * size);

  return new_graph;
}

void graph_destroy(struct graph *g) {
    // TODO: implement this
    for (size_t i = 0; i < g->size; ++i) {
    free(g->edges[i].vertices);
  }

  free(g->edges);
  free(g);
}

void graph_add_edge(struct graph *g, int i, int j) {
    // TODO: implement this
   int* vertex = (int*)malloc(sizeof(int) * (g->edges[i].size + 1));
  for (size_t a = 0; a< g->edges[i].size; ++a) {
    vertex[a] = g->edges[i].vertices[a];
  }

  vertex[g->edges[i].size] = j;
  free(g->edges[i].vertices);
  g->edges[i].vertices = vertex;
  g->edges[i].size += 1;
}

bool graph_has_edge(struct graph *g, int i, int j) {
    // TODO: implement this
    for (size_t x = 0; x < g->edges[i].size; ++x) {
    if (g->edges[i].vertices[x] == j) {
      return true;
    }
  }
  return false;
}

void dfs(struct graph *g, int i, int *visited) {
    // TODO: implement this
    if (!visited[i]) {
    visited[i] = 1;
    for (size_t b = 0; b < g->edges[i].size; ++b) {
      dfs(g, g->edges[i].vertices[b], visited);
    }
  }
}

void bfs(struct graph *g, int *visited) {
    // TODO: implement this
    struct fifo* queue = fifo_create(g->size);
  fifo_enqueue(queue, 0);

  while (!fifo_is_empty(queue)) {
    int i = fifo_dequeue(queue);
    visited[i] = 1;
    for (size_t c= 0; c< g->edges[i].size; ++c) {
      int value = g->edges[i].vertices[c];
      if (!visited[value]) {
        fifo_enqueue(queue, value);
        visited[value] = 1;
      }
    }
  }
}
#endif
