/**
 *
 * Descripcion: Implementacion de funciones de generacion de permutaciones
 *
 * Fichero: permutaciones.c
 * Autor: Carlos Aguirre
 * Version: 1.0
 * Fecha: 16-09-2017
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include "permutaciones.h"

/***************************************************/
/* Funcion: aleat_num Fecha: 19/10/2017            */
/* Autores: Rafael Sánchez, Sergio Galán           */
/*                                                 */
/* Rutina que genera un numero aleatorio           */
/* entre dos numeros dados                         */
/*                                                 */
/* Entrada:                                        */
/* int inf: limite inferior                        */
/* int sup: limite superior                        */
/* Salida:                                         */
/* int: numero aleatorio                           */
/***************************************************/

int aleat_num (int inf, int sup){
  int temp, r;
  if (inf > sup){
    temp = inf;
    inf = sup;
    sup = temp;
  }
  sup++;
  r = (int) inf + rand() / (RAND_MAX / (sup - inf) + 1);
  return r;
}

/***************************************************/
/* Funcion: genera_perm Fecha: 19/10/2017          */
/* Autores: Rafael Sánchez, Sergio Galán           */
/*                                                 */
/* Rutina que genera una permutacion               */
/* aleatoria                                       */
/*                                                 */
/* Entrada:                                        */
/* int n: Numero de elementos de la                */
/* permutacion                                     */
/* Salida:                                         */
/* int *: puntero a un array de enteros            */
/* que contiene a la permutacion                   */
/* o NULL en caso de error                         */
/***************************************************/
int* genera_perm(int N)
{
  int* arr;
  int perm, temp;
  unsigned int i;
  if (N <= 0){
    return NULL;
  }
  arr = calloc(N, sizeof(int));
  if (!arr){
    return NULL;
  }
  for (i = 1; i <= N; i++){
    arr[i-1]=i;
  }
  for (i = 0; i < N; i++){
    perm = aleat_num(0, N-1);
    temp = arr[i];
    arr[i] = arr[perm];
    arr[perm] = temp;
  }
  return arr;
}

/***************************************************/
/* Funcion: genera_permutaciones Fecha: 19/10/2017 */
/* Autores: Rafael Sánchez, Sergio Galán           */
/*                                                 */
/* Funcion que genera n_perms permutaciones        */
/* aleatorias de tamanio elementos                 */
/*                                                 */
/* Entrada:                                        */
/* int n_perms: Numero de permutaciones            */
/* int N: Numero de elementos de cada              */
/* permutacion                                     */
/* Salida:                                         */
/* int**: Array de punteros a enteros              */
/* que apuntan a cada una de las                   */
/* permutaciones                                   */
/* NULL en caso de error                           */
/***************************************************/
int** genera_permutaciones(int n_perms, int N)
{
  int **arr, i, j;
  arr = calloc(n_perms, sizeof(int*));
  if(!arr){
    return NULL;
  }
  for(i=0; i < n_perms; i++){
    arr[i] = genera_perm(N);
    if (!arr[i]){
      for(j=0; j<i; j++){
        free(arr[j]);
      }
      free(arr);
      return NULL;
    }
  }
  return arr;
}
