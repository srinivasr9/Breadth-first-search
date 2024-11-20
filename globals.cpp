#include "bfs.h"

node_t csr_row_ptr[MAX_NODES + 1];
node_t csr_col_indices[MAX_EDGES];
distance_t distances[MAX_NODES];
bool visited[MAX_NODES];
