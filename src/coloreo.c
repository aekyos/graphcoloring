#include "../veinteveinte.h"
#include "helpercomp.h"
#include "queue.h"

/*INICIO 3.1*/
u32 Greedy(Grafo G){
    u32 num_colores = 1; // por lo menos tendra un color porque tiene 1 vertice

    char *colores = calloc(Delta(G)+2, sizeof(char));
    if (colores == NULL){
        return U32_ERROR;
    }

    for (u32 v = 0; v < NumeroDeVertices(G); v++){
        char asignar_color = 0;

        u32 grado = Grado(v,G);

        coloresUsados(colores, grado, v, G);

        for (u32 c = 0; c < num_colores; c++){
            if (colores[c] == 0){
                FijarColor(c, v, G);
                asignar_color = 1;
                break;
            }
        }

        if (asignar_color == 0){
            FijarColor(num_colores,v,G);
            num_colores ++;
        }

        for (u32 i = 0; i < grado; i++){
            colores[i] = 0;
        }
    }
    free(colores);

    return num_colores;
}

/*FIN 3.1*/


/* INICIO 3.2 */
char Bipartito(Grafo G){
    char ret = 0;
    u32 v;
    u32 qlength = 0;
    u32 cant_recorridos = 0;

    queue bfs_queue = NULL;
    char *recorridos = calloc(NumeroDeVertices(G), sizeof(char));
    if (recorridos == NULL){
        return CHAR_ERROR;
    }

    while (cant_recorridos < NumeroDeVertices(G) && ret != CHAR_ERROR ){
        v = buscarVertice(recorridos, cant_recorridos, G);
        bfs_queue = BFS(v, G);
        if (bfs_queue != NULL){
            qlength = queue_length(bfs_queue);

            // Actualizamos el arreglo con vertices y los pintamos con el color correspondiente
            updateArrayBip(recorridos, bfs_queue, qlength, G);

            cant_recorridos = cant_recorridos + qlength;
            bfs_queue = queue_destroy(bfs_queue);
        } else {
            ret = CHAR_ERROR;
        }
    }

    if (ret != CHAR_ERROR){
        if (coloreoPropio(G)){
            ret = 1;
        } else {
            Greedy(G);
        }
    }

    free(recorridos);

    return ret;
}
/*FIN 3.2*/

/*INICIO 3.3*/
char SwitchColores(Grafo G, u32 i, u32 j){
    u32 cant_colores = numColores(G);

    if ((i < cant_colores) && (j < cant_colores)){
        for (u32 v = 0; v < NumeroDeVertices(G); v++){
            u32 color = Color(v,G);
            if (color == i){
                FijarColor(j,v,G);
            } else if (color == j){
                FijarColor(i,v,G);
            }
        }
        return 0;
    } else {
        return 1;
    }
}
/*FIN 3.3*/
