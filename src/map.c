#include "map.h"
#include <assert.h>
#include <stdlib.h>
// Para compilar
// gcc -Wall  -Wextra -pedantic -std=c99 -g -c map.c testing.c
// gcc -Wall -Werror -Wextra -pedantic -g -std=c99 -o test string.o map.o
// testing.o
// una linea: gcc -Wall -Werror -Wextra -pedantic -g -std=c99 -o test string.c
// map.c testing.c

struct _node_t {
  map_t left;
  map_t right;
  key_type key;
  value_t value;
};

map_t map_empty() { return NULL; }
// las funciones static solamente se van a utilizar en este archivo
// crea un nodo nuevo con los parametros dados
static map_t create_node(key_type key, value_t value, map_t left, map_t right) {
  map_t node = NULL;
  node = calloc(1, sizeof(struct _node_t));
  node->left = left;
  node->right = right;
  node->key = key;
  node->value = value;
  return (node);
}
// libera el nodo dado
static map_t free_node(map_t node) {
  // node->key = key_destroy(node->key);
  // node->value = value_destroy(node->value);
  free(node);
  node = NULL;
  return node;
}
// busca en el map  la key(palabra), si llega a estar reemplaza el value, por el
// nuevo, en caso de que no este crea uno nuevo
map_t map_put(map_t map, key_type key, value_t value) {
  assert(value != NULL);
  map_t node = map;

  if (node != NULL) {
    if (key < node->key) {
      node->left = map_put(node->left, key, value);
    } else if (node->key < key) {
      node->right = map_put(node->right, key, value);
    } else if (key < node->key) {
      node->value = value;
    }
  } else if (node == NULL) {
    node = create_node(key, value, NULL, NULL);
  }
  return (node);
}
// obtiene el value si esta la key(palabra) en el árbol(diccionario), si no esta
// tira NULL
value_t map_get(map_t map, key_type key) {
  value_t value = NULL;

  if (map != NULL) {
    if (key < map->key) {
      value = map_get(map->left, key);
    } else if (map->key < key) {
      value = map_get(map->right, key);
    } else if (key == map->key) {
      value = map->value;
    }
  } else {
    value = NULL;
  }
  return (value);
}
// func booleana, que comprueba que una key(palabra) determinada esta en el
// árbol(diccionario)
// bool map_contains(map_t map, key_t key) {
//   assert(key != NULL);
//   bool r = false;
//
//   if (map != NULL) {
//     if (key_less(key, map->key)) {
//       r = map_contains(map->left, key);
//     } else if (key_less(map->key, key)) {
//       r = map_contains(map->right, key);
//     } else {
//       r = key_eq(key, map->key);
//     }
//   }
//   return r;
// }
// remueve un nodo
// static map_t del_max(map_t map) {
//   map_t aux = map;
//   map_t tmp;
//   if (map->right == NULL) {
//     tmp = map->left;
//     free_node(map);
//     map = tmp;
//   }
//   aux = map->right;
//   tmp = map;
//   while (aux->right != NULL) {
//     tmp = aux;
//     aux = aux->right;
//   }
//   tmp->right = aux->left;
//   free_node(aux);
//   return map;
// }
//
// static map_t max_node(map_t map) {
//   assert(map != NULL);
//   map_t aux = map;
//   while (aux->right != NULL) {
//     aux = aux->right;
//   }
//   return aux;
// }
// // función auxiliar Ejercicio 3
// static map_t min_node(map_t map) {
//   assert(map != NULL);
//   map_t aux = map;
//   while (aux->left != NULL) {
//     aux = aux->left;
//   }
//   return aux;
// }
//
// map_t map_remove(map_t map, key_t key) {
//   map_t result = map;
//   // busco el max de la izq y lo meto a la raiz, y luego elimino el del lado
//   // izq.
//   if (result != NULL) {
//     if (key_eq(key, map->key) && result->left == NULL) {
//       map_t tmp = result->right;
//       result = free_node(result);
//       result = tmp;
//     } else if (key_eq(key, map->key) && result->left != NULL) {
//       map_t tmp = max_node(result->left);
//       result->value = tmp->value;
//       result->key = tmp->key;
//       result->left = del_max(result->left);
//     } else if (key_less(key, map->key)) {
//       result->left = map_remove(result->left, key);
//     } else {
//       result->right = map_remove(result->right, key);
//     }
//   }
//   return (result);
// }

// destruye el diccionario o árbol completo
map_t map_destroy(map_t map) {
  if (map != NULL) {
    map->right = map_destroy(map->right);
    map->left = map_destroy(map->left);
    //     map = map_remove(map,map->key);
    map = free_node(map);
  }
  return (map);
}

// imprime el árbol(dicionario)
// void map_dump(map_t map, FILE *file) {
//   if (map != NULL) {
//     map_dump(map->left, file);
//     key_dump(map->key, file);
//     fprintf(file, ": ");
//     value_dump(map->value, file);
//     fprintf(file, "\n");
//     map_dump(map->right, file);
//   }
// }
// Ejercicio 3
// bool es_abb(map_t map) {
//   bool b;
//   if (map == map_empty()) {
//     b = true;
//   } else if (map->left == NULL && map->right == NULL) {
//     b = true;
//   } else if (map->left == NULL) {
//     b = es_abb(map->right) && map->key < min_node(map->right)->key;
//   } else if (map->right == NULL) {
//     b = es_abb(map->left) && max_node(map->right)->key < map->key;
//   } else {
//     b = es_abb(map->right) && es_abb(map->right) &&
//         max_node(map->right)->key < map->key &&
//         map->key < min_node(map->right)->key;
//   }
//   return b;
// }

/*
grep map_t * | grep typedef

grep -r map_t *

grep -ri map_t *


valgrind --leak-check=full ./test

*/
