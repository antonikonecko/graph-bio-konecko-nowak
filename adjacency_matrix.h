#ifndef _ADJACENCY_MATRIX_H_
#define _ADJACENCY_MATRIX_H_

struct graph {
    size_t size;                // number of vertices
    int **matrix;               // adjacency matrix
};

struct graph *graph_create(size_t size) {
    // TODO: implement this
    return NULL;
}

void graph_destroy(struct graph *g) {
    // TODO: implement this
}

void graph_add_edge(struct graph *g, int i, int j) {
    // TODO: implement this
}

bool graph_has_edge(struct graph *g, int i, int j) {
    // TODO: implement this
    return false;
}

void dfs(struct graph *g, int i, int *visited) {
    // TODO: implement this
}

void bfs(struct graph *g, int *visited) {
    // TODO: implement this
}

#endif
