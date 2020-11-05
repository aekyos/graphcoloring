#include <stdio.h>
#include "../veinteveinte.h"
#include <time.h>
#include <stdlib.h>

void imprimir_grafo(Grafo G){
    printf("Vertices: %u, Aristas: %u, Delta: %u\n", NumeroDeVertices(G), NumeroDeLados(G), Delta(G));

    for (unsigned int i = 0; i<NumeroDeVertices(G); i++){
        printf("NODO: nombre: %010u, grado: %05u, color: %07u\n", Nombre(i,G), Grado(i,G), Color(i,G));
        /*if (Nombre(i,G) == 4950)
            print_list(G->vertices[i]->vecinos);*/
    }
}

int main(){
    // printf("Grafo \n");
    Grafo G = ConstruccionDelGrafo();

    // for(u32 i=0; i<NumeroDeVertices(G);i++)
    //     FijarOrden(i,G,i);

    clock_t start = clock();
    // u32 cant = Greedy(G);
    for (u32 i=0; i<10; i++){
        ChicoGrandeBC(G);
        // cant =
        Greedy(G);
        // printf("\n\n\n\n\n");
        // Greedy(G);
    }
    clock_t end = clock();
    // printf("DELTA = %u\n", Delta(G));
    // printf("CANTIDAD = %u\n", cant);
    double time = (end-start) / (double) CLOCKS_PER_SEC;
    printf("time in sec = %f\n", time);
    // printf("time in min = %f\n", time / 60);
    // imprimir_grafo(G);
    DestruccionDelGrafo(G);
}
