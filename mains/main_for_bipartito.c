#include <stdio.h>
#include "../veinteveinte.h"

int main(void) {
    Grafo G = ConstruccionDelGrafo();

    printf("ES BIP? %d\n", Bipartito(G));
    WelshPowell(G);
    printf("ES BIP? %d\n", Bipartito(G));

    DestruccionDelGrafo(G);
    return 0;
}
