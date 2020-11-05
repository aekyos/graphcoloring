#include "../veinteveinte.h"
#include "helpercomp.h"

/*INICIO 5.1*/
u32 NumCCs(Grafo G){
    u32 numccs = 0;
    u32 total_vertices = NumeroDeVertices(G);

    // La cantidad de vertices que ya recorrimos
    u32 cant_recorridos = 0;

    // Vertice sobre el cual voy a correr BFS.
    u32 v = 0;
    queue bfs_queue = NULL;
    char *recorridos = calloc(total_vertices, sizeof(char));
    if (recorridos == NULL){
        return U32_ERROR;
    }

    while (cant_recorridos < total_vertices && numccs != U32_ERROR) {
        v = buscarVertice(recorridos, cant_recorridos, G);

        bfs_queue = BFS(v,G);
        if (bfs_queue != NULL){
            u32 qlength = queue_length(bfs_queue);
            updateArrayNumCCs(recorridos, bfs_queue, qlength);
            cant_recorridos = cant_recorridos + qlength;

            bfs_queue = queue_destroy(bfs_queue);

            numccs ++;
        } else {
            numccs = U32_ERROR;
        }
    }

    free(recorridos);

    return numccs;
}
/*FIN 5.1*/
