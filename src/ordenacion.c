#include "../veinteveinte.h"
#include "helpercomp.h"

/*INICIO 4.1*/
char WelshPowell(Grafo G){
    char ret = 0;
    u32 length = NumeroDeVertices(G);

    // En orden guardo el indice en G de los vertices
    // en orden no creciente.
    dupla orden = calloc(length, sizeof(struct _dupla));
    if (orden == NULL){
        return 1;
    }

    for (u32 i = 0; i < length; i++){
        orden[i].data = Grado(i,G);
        orden[i].name = Nombre(i,G);
    }

    if (ret == 0){
        qsort(orden, length, sizeof(struct _dupla), cmpNatDupla);

        // Pisamos el campo name porque ya no nos sirve.
        // Ahora, guardamos el indice del orden natural.
        for (u32 i = 0; i < length; i++){
            orden[i].name = i;
        }

        // Ordenamos el arreglo por de menor a mayor por grado.
        qsort(orden, length, sizeof(struct _dupla), cmpWP);

        for (u32 i = 0; i < length; i++){
            u32 N = orden[i].name;
            FijarOrden(i,G,N);
        }
    }

    free(orden);
    return ret;
}
/*FIN 4.1*/

/*INICIO 4.2*/
char RevierteBC(Grafo G){
    char ret = 0;
    u32 length = NumeroDeVertices(G);

    // En orden guardo el indice en G de los vertices
    // en orden no creciente.
    dupla orden = calloc(length, sizeof(struct _dupla));
    if (orden == NULL){
        return 1;
    }

    for (u32 i = 0; i < length; i++){
        orden[i].data = Color(i,G);
        orden[i].name = Nombre(i,G);
    }

    if (ret == 0){
        qsort(orden, length, sizeof(struct _dupla), cmpNatDupla);

        // Pisamos el campo name porque ya no sirve.
        // Ahora, guardamos el indice del orden natural.
        for (u32 i = 0; i < length; i++){
            orden[i].name = i;
        }

        // Ordenamos el arreglo por de mayor a menor por color.
        qsort(orden, length, sizeof(struct _dupla), cmpRevierte);

        for (u32 i = 0; i < length; i++){
            u32 N = orden[i].name;
            FijarOrden(i,G,N);
        }
    }

    free(orden);
    return ret;
}
/*FIN 4.2*/

/*INICIO 4.3*/
char ChicoGrandeBC(Grafo G){
    u32 length = NumeroDeVertices(G);
    char ret = 0;

    // Guarda la cantidad de apariciones de cada color
    u32 *colores = calloc(length, sizeof(u32));
    if (colores == NULL){
        return 1;
    }

    //Procesa datos de color,nombre y apariciones
    tripla orden = calloc(length, sizeof(struct _tripla));
    if (orden == NULL){
        ret = 1;
    }

    if (ret == 0){
        // Ver cardinalidad de cada bloque de colores.
        for (u32 i = 0; i < length; i++){
            u32 col = Color(i,G);
            colores[col] ++;
        }

        for (u32 i = 0; i < length; i++){
            u32 color = Color(i,G);
            orden[i].data = colores[color];
            orden[i].color = color;
            orden[i].name = Nombre(i,G);
        }

        qsort(orden, length, sizeof(struct _tripla), cmpNatTripla);

        // Pisamos el nombre (que ya no necesitamos) con el indice del orden natural.
        for (u32 i = 0; i < length; i++){
            orden[i].name = i;
        }
        // Ordenamos segun cardinalidad de bloque de colores.
        qsort(orden, length, sizeof(struct _tripla), cmpChicoGrande);

        for (u32 i = 0; i < length; i++){
            u32 N = orden[i].name;
            FijarOrden(i,G,N);
        }
    }

    free(colores);
    free(orden);
    return ret;
}
/*FIN 4.3*/

/*INICIO 4.4*/
char AleatorizarVertices(Grafo G, u32 r) {
    char ret = 0;
    srand(r);
    u32 length = NumeroDeVertices(G), key;

    // Asumir indices en orden natural para fijar orden
    u32 *neworder = calloc(length, sizeof(u32));
    if (neworder == NULL){
        return 1;
    }

    for (u32 i= 0; i < length; i++){
        neworder[i] = i;
    }

    // Aleatorizar con base en key
    for (u32 i = length-1; i > 0; i--){
        key = rand() % (i+1);
        swap(neworder, i, key);
    }

    for (u32 i = 0; i < length;i++){
        FijarOrden(i, G, neworder[i]);
    }

    free(neworder);
    return ret;
}
/*FIN 4.4*/
