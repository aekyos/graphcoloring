#ifndef GRAFO
#define GRAFO
#include <stdint.h>
typedef uint32_t u32;
typedef struct _vertice{
  u32 nombre;
  u32 grado;
  u32 color;
  u32 orden;
  // Esta lista sera usada cuando creamos el grafo
  struct _vertice **vecinos;
} vertice;

typedef struct {
  // Cantidad de vertices
  u32 n;
  // Cantidad de lados
  u32 m;
  // Arreglo de vértices con index de 0 a n-1
  vertice *V;
  // Vertice de mayor grado del grafo
  u32 Delta;
  // Arreglo con el orden de los vertices
  // orden[i] es el indice que indica en el arreglo V
  // al i-esimo vertice
  u32 *orden;
  // Arreglo con los indices del arreglo de vertices en
  // el orden natural
  vertice **natural;
} GrafoSt;
#endif
