#include "helpercomp.h"

queue BFS(u32 i,Grafo G){
    queue cola = queue_init(NumeroDeVertices(G));
    if (cola == NULL){
        return NULL;
    }

    queue historico = queue_init(NumeroDeVertices(G));

    u32 color = 0;

    cola = queue_add(i, color, cola);
    historico = queue_add(i, color, historico);

    while (queue_length(cola) != 0 && cola != NULL && historico != NULL){
        u32 pcolor = queue_get_color(cola);
        u32 p = queue_get_index(cola);
        queue_remove(cola);
        u32 grado = Grado(p, G);

        color = (pcolor + 1) % 2;

        for (u32 j = 0; j < grado; j++) {
            u32 vecino = OrdenVecino(j, p, G);

            if (! queue_in(vecino, historico)){
                cola = queue_add(vecino, color, cola);
                historico = queue_add(vecino, color, historico);
            }
        }
    }

    cola = queue_destroy(cola);

    return historico;
}
/* auxiliar de greedy */
void coloresUsados(char *colores, u32 grado, u32 i, Grafo G){
    for (u32 j = 0; j < grado; j++) {
        if (OrdenVecino(j,i,G) < i){
            u32 colorvec = ColorVecino(j,i,G);
            if (colorvec < grado){
                colores[colorvec] = 1;
            }
        }
    }
}
/* fin auxiliar de greedy */

/* auxiliar de switchcolores */
u32 numColores(Grafo G){
    u32 num = 0, color;

    // Recorremos todos los vertices buscando el mayor color.
    for (u32 i = 0; i < NumeroDeVertices(G); i++){
        color = Color(i,G);
        if (color > num){
            num = color;
        }
    }

    // Aumentamos en 1 el numero porque los colores van desde 0 hasta n-1.
    return (num + 1);
}
/*fin auxiliar de switchcolores*/

char coloreoPropio(Grafo G){
    u32 ret = 1, i = 0;
    while ((i < NumeroDeVertices(G)) && ret){
        u32 color = Color(i,G), j = 0, grado = Grado(i,G);
        // Vemos si algunos de los vecinos tienen el mismo color
        while ((j < grado) && ret) {
            u32 colorvec = ColorVecino(j,i,G);
            if (colorvec == color){
                ret = 0;
            }
            j++;
        }
        i++;
    }
    return ret;
}

/*auxiliares para Bipartito y NumCCs*/
u32 buscarVertice(char *recorridos, u32 len, Grafo G){
    u32 i = 0;

    if (len > 0){
        while ((recorridos[i] != 0) && (i < NumeroDeVertices(G))){
            i++;
        }
    }

    return i;
}

void updateArrayNumCCs(char *recorridos, queue q, u32 qlen){
    u32 index;
    for (u32 i = 0; i < qlen; i++){
        index = queue_get_index(q);
        recorridos[index] = 1;

        queue_remove(q);
    }
}

void updateArrayBip(char *recorridos, queue q, u32 qlen, Grafo G){
    u32 color;
    u32 index;
    for (u32 i = 0; i < qlen; i++){
        index = queue_get_index(q);
        recorridos[index] = 1;
        color = queue_get_color(q);
        FijarColor(color, index, G);

        queue_remove(q);
    }
}
/*fin auxiliares Bipartito y NumCCs*/

/* auxiliares para sorts */
int cmpRevierte(const void * i, const void * j){
    int ret = 1;
    u32 ni = (*(dupla)i).data;
    u32 nj = (*(dupla)j).data;

    if (ni > nj){
        ret = -1;
    } else if (ni == nj){
        ret = 0;
    }

    return ret;
}

int cmpWP(const void * i, const void * j){
    int ret = 1;
    u32 ni = (*(dupla)i).data;
    u32 nj = (*(dupla)j).data;

    if (ni > nj){
        ret = -1;
    } else if (ni ==nj){
        ret = 0;
    }

    return ret;
}

int cmpNatDupla(const void * i, const void * j){
    int ret = 1;
    u32 ni = (*(dupla)i).name;
    u32 nj = (*(dupla)j).name;

    if (ni < nj){
        ret = -1;
    } else if (ni == nj){
        ret = 0;
    }
    return ret;
}

int cmpNatTripla(const void * i, const void * j){
    int ret = 1;
    u32 ni = (*(tripla)i).name;
    u32 nj = (*(tripla)j).name;

    if (ni < nj){
        ret = -1;
    } else if (ni == nj){
        ret = 0;
    }
    return ret;
}

int cmpChicoGrande(const void * i, const void * j){
    int ret = 1;
    u32 ni = (*(tripla)i).data;
    u32 ci = (*(tripla)i).color;
    u32 nj = (*(tripla)j).data;
    u32 cj = (*(tripla)j).color;

    if (ni < nj){
        ret = -1;
    } else if (ni == nj && ci < cj){
        ret = -1;
    } else if (ni == nj && ci == cj){
        ret = 0;
    } // else if (ni == nj && ci > cj){
    //     ret = 1;
    // } else if (ni > nj){
    //     ret = 1;
    // }

    // int eq = (ni == nj);
    // int may = (ni > nj);
    // if (ret == 3)
    //     printf("i(%02u %02u) j(%02u %02u) rel %d %d ret:%d\n", ni,ci,nj,cj,eq,may,ret);

    return ret;
}
/*fin auxiliares sorts*/

/*auxiliar para aleatorizar*/
void swap(u32 *arr, u32 i, u32 j){
    u32 target = arr[i];
    arr[i] = arr[j];
    arr[j] = target;
}
/*fin auxiliar aleatorizar*/
