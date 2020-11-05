#include <stdio.h>
#include "../veinteveinte.h"

void imprimir_grafo(Grafo G){
    // printf("Vertices: %u, Aristas: %u, Delta: %u\n", NumeroDeVertices(G), NumeroDeLados(G), Delta(G));

    for (unsigned int i = 0; i<NumeroDeVertices(G); i++){
        printf("NODO: nombre: %05u, grado: %05u, color: %02u\n", Nombre(i,G), Grado(i,G), Color(i,G));
        /*if (Nombre(i,G) == 4950)
            print_list(G->vertices[i]->vecinos);*/
    }
}

int main() {
    Grafo G = ConstruccionDelGrafo();

    if (WelshPowell(G) == 1){
        printf("Algo anduvo mal en Welsh Powell\n");
    }

    imprimir_grafo(G);

    return 0;
}
