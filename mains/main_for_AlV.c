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
    Grafo G = ConstruccionDelGrafo();
    u32 cant = 100;
    printf("%u\n", cant);
    printf("%u\n", NumeroDeVertices(G));

    for (u32 i=0; i < cant; i++){
    	AleatorizarVertices(G,i);
        imprimir_grafo(G);
    	AleatorizarVertices(G,i);
        imprimir_grafo(G);
    }
}
