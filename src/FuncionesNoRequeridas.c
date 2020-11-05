#include "map.h"
#include "../veinteveinte.h"
#include <assert.h>

typedef struct _tupla {
  u32 n1, n2;
} tupla;

// ParseGrafo() es la funcion que parsea el grafo desde STDIN
static char ParseGrafo(Grafo G);

// ConstruccionDelGrafo() reserva la memoria para la estructura
// y llama a la funcion auxiliar ParseGrafo() para continuar
Grafo ConstruccionDelGrafo() {
  Grafo g = calloc(1, sizeof(GrafoSt));
  if (!g) {
    return NULL;
  }
  ParseGrafo(g);
  return g;
}

// DestruccionDelGrafo() debe ser completada, no tuve tiempo
void DestruccionDelGrafo(Grafo G) {
  for (u32 i = 0u; i < G->n; i++)
    if (G->V[i].vecinos)
      free(G->V[i].vecinos);
  free(G->V);
  free(G->orden);
  free(G->natural);
  free(G);
}

// CopiarGrafo() debe ser completada, no tuve tiempo
Grafo CopiarGrafo(Grafo G) {
  Grafo g = calloc(1, sizeof(GrafoSt));
  g->n = G->n;
  g->m = G->m;
  g->V = calloc(g->n, sizeof(vertice));
  g->Delta = G->Delta;
  g->orden = calloc(g->n, sizeof(u32));
  g->natural = calloc(g->n, sizeof(vertice*));
  for (u32 i = 0u; i < g->n; i++) {
    // Copio los datos de cada vertice
    g->orden[i] = G->orden[i];
    g->V[i].nombre = G->V[i].nombre;
    g->V[i].grado = G->V[i].grado;
    g->V[i].color = G->V[i].color;
    g->V[i].orden = G->V[i].orden;
    g->V[i].vecinos = NULL;
    g->V[i].vecinos = calloc(g->V[i].grado, sizeof(vertice*));
    g->natural[i] =
        (vertice*)((int64_t)g->V + (int64_t)G->natural[i] - (int64_t)G->V);
    for (u32 j = 0u; j < g->V[i].grado; j++)
      // Copio el corrimiento del array original mas la base del nuevo
      g->V[i].vecinos[j] =
          (void*)((int64_t)g->V + (int64_t)G->V[i].vecinos[j] - (int64_t)G->V);
  }
  return g;
}

// NumeroDeVertices() devuelve el campo n de la estructura
u32 NumeroDeVertices(Grafo G) {
  return G->n;
}

// NumeroDeLados() devuelve el campo m de la estructura
u32 NumeroDeLados(Grafo G) {
  return G->m;
}

// Delta() devuelve el campo Delta de la estructura
u32 Delta(Grafo G) {
  return G->Delta;
}

// Nombre() devuelve el nombre del vertice i en el orden de G en ese momento
u32 Nombre(u32 i, Grafo G) {
  return G->V[G->orden[i]].nombre;
}

// Color() devuelve el color del vertice i en el orden de G en ese momento
u32 Color(u32 i, Grafo G) {
  return G->V[G->orden[i]].color;
}

// Grado() devuelve el grado del vertice i en el orden de G en ese momento
u32 Grado(u32 i, Grafo G) {
  return G->V[G->orden[i]].grado;
}

// ColorVecino() devuelve el color del j-esimo vecino del i-esimo vertice
// El orden del j-esimo es interno
// El orden del i-esimo es del Grafo
u32 ColorVecino(u32 j, u32 i, Grafo G) {
  return ((vertice*)G->V[G->orden[i]].vecinos[j])->color;
}

// NombreVecino() devuelve el nombre del j-esimo vecino del i-esimo vertice
// El orden del j-esimo es interno
// El orden del i-esimo es del Grafo
u32 NombreVecino(u32 j, u32 i, Grafo G) {
  assert(j < Grado(i, G));
  return ((vertice*)G->V[G->orden[i]].vecinos[j])->nombre;
}

// OrdenVecino() devuelve el orden del j-esimo vecino del i-esimo vertice
// El orden del j-esimo es interno
// El orden del i-esimo es del Grafo
u32 OrdenVecino(u32 j, u32 i, Grafo G) {
  return ((vertice*)G->V[G->orden[i]].vecinos[j])->orden;
}

// FijarColor() asigna el color x al vertice i-esimo en el orden del grafo
char FijarColor(u32 x, u32 i, Grafo G) {
  if (i < G->n) {
    // Indexo el arreglo de vertices con el indice que indica el i-esimo
    // vertice dado el orden actual del grafo y seteo su color a x
    G->V[G->orden[i]].color = x;
    return 0;
  } else {
    return 1;
  }
}
// FijarOrden() asigna el orden N al vertice i-esimo en el orden que tiene
// el grafo en ese momento
char FijarOrden(u32 i, Grafo G, u32 N) {
  if (i < G->n && N < G->n) {
    // Es lo que especifica la consigna, utilizar con cuidado
    G->orden[i] = ((long unsigned int)G->natural[N] - (long unsigned int)G->V) /
                  sizeof(vertice);
    G->V[G->orden[i]].orden = i;
    return 0;
  } else {
    return 1;
  }
}
/* Funciones auxiliares */

int cmpf(const void* a, const void* b) {
  vertice *v1 = *(vertice**)a, *v2 = *(vertice**)b;
  if (v1->nombre < v2->nombre) {
    return -1;
  } else if (v1->nombre > v2->nombre) {
    return 1;
  } else {
    return 0;
  }
}

int cmpTupla(const void* a, const void* b) {
  u32 n1 = (*(tupla*)a).n1, n2 = (*(tupla*)b).n1;
  if (n1 < n2) {  // Wtf
    return -1;
  } else if (n1 > n2) {
    return 1;
  } else {
    return 0;
  }
}

map_t AgregarAlArbol(map_t a, u32* arr_n, u32 n, vertice* arr_V) {
  long long unsigned int m = 0, log = 0, i = 0, j = 1, k = 0, index = 0;
  m = n;
  while (m >>= 1)
    ++log;
  m = 1 << (log + 1);
  while (i < n) {
    k = 0;
    while (2 * k + 1 < (u32)(1 << j) && i < n) {
      index = ((2 * k + 1) * m) >> j;
      if (index >= n)
        break;
      a = map_put(a, arr_n[index], arr_V + index);
      i++;
      k++;
    }
    j++;
  }
  return a;
}

// ParseGrafo() se encarga de leer informacion de un grafo desde STDIN y
// transformarla a la estructura GrafoSt
static char ParseGrafo(Grafo g) {
  u32 k1, k2;
  char ch = '\n';
  while (ch != 'p') {
    ch = getchar();
    if (ch == 'c')
      while (ch != '\n')
        ch = getchar();
  }
  // Obtenemos la cantidad de vertices y aristas del grafo
  int err = scanf("%*s %u %u", &g->n, &g->m);
  // Reservamos memoria para el arreglo de vertices
  g->V = (vertice*)calloc(g->n, sizeof(vertice));
  // Reservamos memoria para el arreglo de orden de vertices
  g->orden = (u32*)calloc(g->n, sizeof(u32));
  // Inicializamos los vertices, el color no puede ser 1
  for (u32 i = 0; i < g->n; i++) {
    g->V[i].nombre = g->V[i].grado = g->V[i].color = 0;
    g->V[i].orden = g->orden[i] = i;
  }
  // Arreglo de tuplas de aristas con (v,w) in E <=> (w,v) in E
  tupla* t = calloc(2 * g->m, sizeof(tupla));
  /* Debug */
  /* End debug */
  // Leemos nombre un vertice y nombre del otro y agregamos arista a E
  for (u32 i = 0u; i < g->m; i++) {
    err = scanf("%*s %u %u", &k1, &k2);
    t[2 * i].n1 = t[2 * i + 1].n2 = k1;
    t[2 * i].n2 = t[2 * i + 1].n1 = k2;
    if (err == -1) perror("error al leer aristas\n");
  }
  // Ordeno el arreglo de tuplas en funcion de la primer coordenada de cada una
  qsort(t, 2 * g->m, sizeof(tupla), cmpTupla);

  // Para testear la ordenacion
  // for (u32 i = 0; i < 2 * g->m; i++)
  //   printf("%u  %u\n", t[i].n1, t[i].n2);

  // Arreglo de nombres de vertices
  u32* arr_n = calloc(g->n, sizeof(u32));
  // Arreglo de grados de vertices
  // (arr_n[i], arr_g[i+1]) = (nombre, grado)

  u32* arr_g = calloc(g->n + 1, sizeof(u32));  // +1 porque hago sumas parciales
  arr_g[0] = 0;                                // Los uso como tuplas
  u32 j = 0;

  arr_n[0] = t[0].n1;
  arr_g[1] = 0;
  for (u32 i = 0; i < 2 * g->m; i++)
    if (arr_n[j] != t[i].n1) {
      arr_n[++j] = t[i].n1;
      arr_g[j + 1] = 1;  // El vertice se encontro en una arista
    } else {
      arr_g[j + 1]++;
    }
  // Genero un arbol binario de busqueda balanceado de nombres de vertices
  // Testeo que la suma de los grados sea el doble de las aristas
  map_t map = map_empty();
  map = AgregarAlArbol(map, arr_n, g->n, g->V);
  for (u32 i = 0; i < g->n; i++) {
    g->V[i].nombre = arr_n[i];
    g->V[i].grado = arr_g[i + 1];

    if (g->V[i].grado > g->Delta){
        g-> Delta = g->V[i].grado;
    }

    g->V[i].vecinos = calloc(g->V[i].grado, sizeof(vertice*));
    g->V[i].color = i;
    for (u32 k = 0; k < g->V[i].grado; k++) {
      g->V[i].vecinos[k] = (vertice*)map_get(map, t[k + arr_g[i]].n2);
    }
    arr_g[i + 1] += arr_g[i];  // suma parcial
  }
  map_destroy(map);
  // Ha surgido nueva información de FijarOrden(). Conviene ordenar el
  // arreglo De vertices de forma creciente (en funcion del nombre)
  g->natural = calloc(g->n, sizeof(vertice*));
  for (u32 i = 0; i < g->n; i++) {
    g->natural[i] = &(g->V[i]);
  }
  qsort(g->natural, g->n, sizeof(vertice*), cmpf);
  free(arr_n);
  free(t);
  free(arr_g);

  return 0;
}
