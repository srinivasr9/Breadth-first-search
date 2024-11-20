#include "bfs_gas.h"

void bfs_gas(hls::stream<node_t> &in_stream, node_t source, node_t num_nodes) {
    #pragma HLS INTERFACE s_axilite port=return bundle=control
    #pragma HLS INTERFACE s_axilite port=source bundle=control
    #pragma HLS INTERFACE s_axilite port=num_nodes bundle=control
    #pragma HLS INTERFACE m_axi port=csr_row_ptr offset=slave bundle=gmem
    #pragma HLS INTERFACE m_axi port=csr_col_indices offset=slave bundle=gmem
    #pragma HLS INTERFACE m_axi port=distances offset=slave bundle=gmem
    #pragma HLS INTERFACE m_axi port=visited offset=slave bundle=gmem

    #pragma HLS bind_storage variable=csr_row_ptr type=ram_2p impl=bram
    #pragma HLS bind_storage variable=csr_col_indices type=ram_1p impl=uram
    #pragma HLS bind_storage variable=distances type=ram_1p impl=uram
    #pragma HLS bind_storage variable=visited type=ram_2p impl=bram

    #pragma HLS ARRAY_PARTITION variable=distances cyclic factor=16 dim=1

    
    for (node_t i = 0; i < num_nodes; i++) {
        #pragma HLS PIPELINE II=1
        visited[i] = false;
        distances[i] = -1;
    }
    visited[source] = true;
    distances[source] = 0;

    
    while (!in_stream.empty()) {
        
        node_t current_node = in_stream.read();

       
        node_t start = csr_row_ptr[current_node];
        node_t end = csr_row_ptr[current_node + 1];

       
        for (node_t i = start; i < end; i++) {
            #pragma HLS PIPELINE II=1
            node_t neighbor = csr_col_indices[i];

           
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                distances[neighbor] = distances[current_node] + 1;
                in_stream.write(neighbor);
            }
        }
    }
}
