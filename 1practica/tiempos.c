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
#include <math.h>

/***************************************************/
/* Funcion: tiempo_medio_ordenacion Fecha:         */
/*                                                 */
/* Vuestra documentacion (formato igual            */
/* que en el primer apartado):                     */
/***************************************************/
short tiempo_medio_ordenacion(pfunc_ordena metodo,
                              int n_perms,
                              int N,
                              PTIEMPO ptiempo)
{
  int **permutaciones, current_ob, min_ob, max_ob, all_ob=0, i;
  clock_t t_start, t_end, t_total=0;
  double t_avg, avg_ob;

  if(!ptiempo || N < 0 || n_perms < 0){
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
  avg_ob = (double) all_ob/n_perms;
  t_avg = (double) t_total / n_perms;
  t_avg *= 1000.0;
  ptiempo->tiempo = (double) t_avg/(CLOCKS_PER_SEC);
  ptiempo->min_ob = min_ob;
  ptiempo->medio_ob = avg_ob;
  ptiempo->max_ob = max_ob;

  for(i = 0; i<n_perms; i++){
    free(permutaciones[i]);
  }
  free(permutaciones);

  return OK;
}

/***************************************************/
/* Funcion: genera_tiempos_ordenacion Fecha:       */
/*                                                 */
/* Vuestra documentacion                           */
/***************************************************/
short genera_tiempos_ordenacion(pfunc_ordena metodo, char* fichero,
                                int num_min, int num_max,
                                int incr, int n_perms)
{
  PTIEMPO ptiempo;
  int i, size, j;

  if (!metodo || !fichero || incr <= 0 || num_min < 0 || num_max < 0 || num_min > num_max || n_perms < 0){
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

/***************************************************/
/* Funcion: guarda_tabla_tiempos Fecha:            */
/*                                                 */
/* Vuestra documentacion (formato igual            */
/* que en el primer apartado):                     */
/***************************************************/
short guarda_tabla_tiempos(char* fichero, PTIEMPO tiempo, int n_tiempos)
{
  FILE* fp;
  fp = fopen(fichero, "a");
  fprintf(fp, "%d %f %f %d %d\n",tiempo->N, tiempo->tiempo, tiempo->medio_ob, tiempo->min_ob, tiempo->max_ob);
  fclose(fp);
  return OK;

}
