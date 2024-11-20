#include <iostream>
#include <hls_stream.h>
#include "bfs.h"
#include <cstdlib>


void initialize_graph(node_t num_nodes, node_t num_edges) {
    node_t edge_index = 0;

    
    for (node_t i = 0; i < num_nodes - 1; i++) {
        csr_row_ptr[i] = edge_index;
        csr_col_indices[edge_index++] = i + 1;
    }
    csr_row_ptr[num_nodes - 1] = edge_index;

   
    for (node_t i = 0; i < num_edges - (num_nodes - 1); i++) {
        node_t src = rand() % num_nodes;
        node_t dest = rand() % num_nodes;
        if (src != dest) {
            csr_col_indices[edge_index++] = dest;
        }
    }
    csr_row_ptr[num_nodes] = edge_index;
}


void test_bfs() {
    const node_t num_nodes = 100000; 
    const node_t num_edges = 500000; 

    initialize_graph(num_nodes, num_edges);

    node_t source = 0;
    hls::stream<node_t> in_stream;
    in_stream.write(source);

    
    bfs_gas(in_stream, source, num_nodes);

   
    std::cout << "Distances from source node " << source << ":\n";
    for (node_t i = 0; i < 10; i++) { // Print only the first 10 nodes
        if (distances[i] == -1)
            std::cout << "Node " << i << ": Unreachable\n";
        else
            std::cout << "Node " << i << ": " << distances[i] << "\n";
    }
}

int main() {
    test_bfs();
    return 0;
}
