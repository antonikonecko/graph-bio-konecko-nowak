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
}

void graph_destroy(struct graph *g) {
    // TODO: implement this
}

void graph_add_edge(struct graph *g, int i, int j) {
    // TODO: implement this
}

bool graph_has_edge(struct graph *g, int i, int j) {
    // TODO: implement this
}

void dfs(struct graph *g, int i, int *visited) {
    // TODO: implement this
}

void bfs(struct graph *g, int *visited) {
    // TODO: implement this
}

#endif
