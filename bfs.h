
#ifndef BFS_H
#define BFS_H

#include <hls_stream.h>
#include <ap_int.h>

#define MAX_NODES 1000000
#define MAX_EDGES 5000000


typedef ap_uint<32> node_t;
typedef ap_uint<32> distance_t;


extern node_t csr_row_ptr[MAX_NODES + 1];
extern node_t csr_col_indices[MAX_EDGES];
extern distance_t distances[MAX_NODES];
extern bool visited[MAX_NODES];
void bfs_gas(hls::stream<node_t> &in_stream, node_t source, node_t num_nodes);

#endif
