/**
 *
 * Descripcion: Implementacion de funciones de tiempo
 *
 * Fichero: tiempos.c
 * Autor: Carlos Aguirre Maeso
 * Version: 1.0
 * Fecha: 16-09-2017
 *
 */

#include "tiempos.h"
#include "ordenacion.h"
#include "permutaciones.h"
#include "busqueda.h"
#include <math.h>

/******************************************************/
/* Funcion: tiempo_medio_ordenacion Fecha: 19/10/2017 */
/* Autores: Rafael Sánchez, Sergio Galán              */
/*                                                    */
/* Funcion que guarda en un tipo de dato TIEMPO, la   */
/* informacion relacionada con un metodo de ordenacion*/
/*                                                    */
/* Entrada:                                           */
/* pfunc_ordena metodo: Puntero a una funcion de      */
/* ordenacion                                         */
/* int n_perms: Numero de permutaciones               */
/* int N: Numero de elementos de cada permutacion     */
/* PTIEMPO ptiempo: Puntero al struct TIEMPO donde se */
/* guardaran los datos                                */
/* Salida:                                            */
/* short: OK si no surgió ningún fallo                */
/* ERR en caso de error                               */
/******************************************************/
short tiempo_medio_ordenacion(pfunc_ordena metodo,
                              int n_perms,
                              int N,
                              PTIEMPO ptiempo)
{
  int **permutaciones, current_ob, min_ob, max_ob, all_ob=0, i;
  clock_t t_start, t_end, t_total=0;
  double t_avg, avg_ob, clocks_per_sec_d;

  if(!ptiempo || N < 0 || n_perms < 0 || !metodo){
    return ERR;
  }

  ptiempo->n_elems = n_perms;
  ptiempo->N = N;
  permutaciones = genera_permutaciones(n_perms, N);
  if(!permutaciones){
    return ERR;
  }
  for (i = 0; i < n_perms; i++){
    t_start = clock();
    current_ob = metodo(permutaciones[i], 0, N-1);
    t_end = clock();
    t_total += t_end - t_start;
    if (!i){
      min_ob = current_ob;
      max_ob = current_ob;
    }else{
      if (current_ob < min_ob) min_ob = current_ob;
      if (current_ob > max_ob) max_ob = current_ob;
    }
    all_ob += current_ob;
  }
  clocks_per_sec_d = (double) CLOCKS_PER_SEC;
  avg_ob = (double) all_ob/n_perms;
  t_avg = (double) t_total / n_perms;
  ptiempo->tiempo = t_avg *= 1000.0f/(clocks_per_sec_d);
  ptiempo->min_ob = min_ob;
  ptiempo->medio_ob = avg_ob;
  ptiempo->max_ob = max_ob;

  for(i = 0; i<n_perms; i++){
    free(permutaciones[i]);
  }
  free(permutaciones);

  return OK;
}

/***********************************************************/
/* Funcion: genera_tiempos_ordenacion Fecha: 19/10/2017    */
/* Autores: Rafael Sánchez, Sergio Galán                   */
/*                                                         */
/* Funcion que genera un array de TIEMPO haciendo          */
/* llamadas sucesivas a la funcion tiempo_medio_ordenacion */
/* con un tamaño de permutacion distinto cada vez. Luego,  */
/* tras sucesivas llamadas a guarda_tabla_tiempos, genera  */
/* un fichero con la informacion del array de TIEMPO.      */
/*                                                         */
/* Entrada:                                                */
/* pfunc_ordena metodo: Puntero a una funcion de           */
/* ordenacion                                              */
/* char* fichero: nombre del fichero al que escribir       */
/* int num_min: tamaño minimo de la permutacion            */
/* int num_max: tamaño maximo de la permutacion            */
/* int incr: Variación del tamaño de permutacion en cada   */
/* llamada a tiempo_medio_ordenacion                       */
/* int n_perms: Numero de permutaciones                    */
/* Salida:                                                 */
/* short: OK si no surgió ningún fallo                     */
/* ERR en caso de error                                    */
/***********************************************************/
short genera_tiempos_ordenacion(pfunc_ordena metodo, char* fichero,
                                int num_min, int num_max,
                                int incr, int n_perms)
{
  PTIEMPO ptiempo;
  int i, size, j;

  if (!metodo || !fichero || incr <= 0 || num_min < 0 || num_max < 0 || num_min > num_max || n_perms <= 0){
    return ERR;
  }

  size = ceil((num_max - num_min)/incr);
  ptiempo = calloc(size+1, sizeof(TIEMPO));
  if(!ptiempo){
    return ERR;
  }
  for(i=num_min, j=0; i<=num_max; i+=incr, j++){
    if(ERR == tiempo_medio_ordenacion(metodo, n_perms, i, &ptiempo[j])){
      free(ptiempo);
      return ERR;
    }
  }
  for(j=0;j<=size;j++){
    if (ERR == guarda_tabla_tiempos(fichero, &ptiempo[j], j)){
      free(ptiempo);
      return ERR;
    }
  }
  free(ptiempo);
  return OK;
}

/***********************************************************/
/* Funcion: genera_tiempos_ordenacion Fecha: 19/10/2017    */
/* Autores: Rafael Sánchez, Sergio Galán                   */
/*                                                         */
/* Funcion que abre un fichero y escribe en el la          */
/* informacion de un array de TIEMPO                       */
/*                                                         */
/* Entrada:                                                */
/* char* fichero: nombre del fichero al que escribir       */
/* int num_min: tamaño minimo de la permutacion            */
/* PTIEMPO tiempo:Array que guarda los tiempos de ejecucion*/
/* int n_tiempos: Numero de elementos del array TIEMPO     */
/* Salida:                                                 */
/* short: OK si no surgió ningún fallo                     */
/* ERR en caso de error                                    */
/***********************************************************/
short guarda_tabla_tiempos(char* fichero, PTIEMPO tiempo, int n_tiempos)
{
  FILE* fp;
  fp = fopen(fichero, "a");
  if(!fp){
    return ERR;
  }
  fprintf(fp, "%d %.16f %f %d %d\n",tiempo->N, tiempo->tiempo, tiempo->medio_ob, tiempo->min_ob, tiempo->max_ob);
  fclose(fp);
  return OK;

}


short genera_tiempos_busqueda(pfunc_busqueda metodo, pfunc_generador_claves generador,
                                int orden, char* fichero,
                                int num_min, int num_max,
                                int incr, int n_veces)
{
  PTIEMPO ptiempo;
  int i, size, j;

  if (!metodo || !fichero || incr <= 0 || num_min < 0 || num_max < 0 || num_min > num_max || n_veces <= 0 || (orden != ORDENADO && orden != NO_ORDENADO) || !generador){
    return ERR;
  }

  size = ceil((num_max - num_min)/incr);
  ptiempo = calloc(size+1, sizeof(TIEMPO));
  if(!ptiempo){
    return ERR;
  }
  for(i=num_min, j=0; i<=num_max; i+=incr, j++){
    if(ERR == tiempo_medio_busqueda(metodo, generador, orden, i, n_veces, &ptiempo[j])){
      free(ptiempo);
      return ERR;
    }
  }
  for(j=0;j<=size;j++){
    if (ERR == guarda_tabla_tiempos(fichero, &ptiempo[j], j)){
      free(ptiempo);
      return ERR;
    }
  }
  free(ptiempo);
  return OK;
}

short tiempo_medio_busqueda(pfunc_busqueda metodo, pfunc_generador_claves generador,
                              int orden,
                              int N,
                              int n_veces,
                              PTIEMPO ptiempo)
{
  DICC* d;
  int *perm, *claves, *caux, *end, current_ob, min_ob, max_ob, pos;
  long all_ob = 0;
  clock_t t_start, t_end, t_total=0;
  double t_avg, avg_ob, clocks_per_sec_d;

  if(!ptiempo || N <= 0 || n_veces <= 0 || !metodo || !generador || (orden != ORDENADO && orden != NO_ORDENADO)){
    return ERR;
  }

  d = ini_diccionario(N, orden);
  if(!d){
    return ERR;
  }
  perm = genera_perm(N);
  if(!perm){
    libera_diccionario(d);
    return ERR;
  }
  if (ERR==insercion_masiva_diccionario(d, perm, N)){
    free(perm);
    libera_diccionario(d);
    return ERR;
  }
  claves = calloc(n_veces * N, sizeof(int));
  if(!claves){
    free(perm);
    libera_diccionario(d);
    return ERR;
  }
  generador(claves, n_veces*N, N);

  ptiempo->n_elems = N*n_veces;
  ptiempo->N = N;

  for (caux = claves, end = claves + N*n_veces; caux < end; ++caux){
    t_start = clock();
    current_ob = busca_diccionario(d, *caux, &pos, metodo);
    t_end = clock();
    if(current_ob == ERR){
      free(claves);
      free(perm);
      libera_diccionario(d);
      return ERR;
    }
    t_total += t_end - t_start;
    if(!(caux - claves)){
      min_ob = current_ob;
      max_ob = current_ob;
    }else{
      if (current_ob < min_ob) min_ob = current_ob;
      if (current_ob > max_ob) max_ob = current_ob;
    }
    all_ob += current_ob;
  }
  clocks_per_sec_d = (double) CLOCKS_PER_SEC;
  avg_ob = (double) all_ob/ptiempo->n_elems;
  t_avg = (double) t_total /ptiempo->n_elems;
  ptiempo->tiempo = t_avg *= 1.0f/(clocks_per_sec_d);
  ptiempo->min_ob = min_ob;
  ptiempo->medio_ob = avg_ob;
  ptiempo->max_ob = max_ob;

  free(claves);
  free(perm);
  libera_diccionario(d);

  return OK;
}
