#ifndef __HELPERCOMP_H_
#define __HELPERCOMP_H_

#include "../veinteveinte.h"
#include "queue.h"

#define U32_ERROR  0xFFFFFFFF
#define CHAR_ERROR 0x7F

queue BFS(u32 i,Grafo G);

/*estructuras auxiliares de comparacion*/
typedef struct _tripla {
    u32 name;
    u32 data;
    u32 color;
} *tripla;

typedef struct _dupla {
    u32 name;
    u32 data;
} *dupla;

u32 numColores(Grafo G);
char coloreoPropio(Grafo G);
void coloresUsados(char *colores, u32 grado, u32 i, Grafo G);

/* Devuelve un vertice sobre el cual no corrio BFS aun*/
u32 buscarVertice(char *recorridos, u32 len, Grafo G);

/*Marcar vertices ya recorridos con BFS*/
void updateArrayNumCCs(char *recorridos, queue q, u32 qlen);

/*Igual que updateArrayCCs pero aca pintamos con el color dado por BFS*/
void updateArrayBip(char *recorridos, queue q, u32 qlen, Grafo G);

/*funciones auxiliares de comparacion usadas*/
int cmpWP(const void * i, const void * j);
int cmpRevierte(const void * i, const void * j);
int cmpChicoGrande(const void * i, const void * j);
int cmpNatDupla(const void * i, const void * j);
int cmpNatTripla(const void * i, const void * j);
int cmpChicoGrande(const void * i, const void * j);
void swap(u32* arr,u32 i, u32 j);

#endif // __HELPERCOMP_H_
