/**
 *
 * Descripcion: Implementacion de funciones de ordenacion
 *
 * Fichero: ordenacion.c
 * Autor: Carlos Aguirre
 * Version: 1.0
 * Fecha: 16-09-2017
 *
 */


#include "ordenacion.h"

/***************************************************/
/* Funcion: InsertSort    Fecha:                   */
/* Vuestro comentario                              */
/***************************************************/
int BubbleSort(int* tabla, int ip, int iu)
{
  int i,j,temp, ret=0;
  for ( i = iu; i >= ip+1; i--){
    for (j = ip; j <= i-1; j++){
      ret++;
      if (tabla[j] > tabla[j+1]){
        temp = tabla[j];
        tabla[j] = tabla[j+1];
        tabla[j+1]=temp;
      }
    }
  }
  if(ret==0){
    return ERR;
  }
  return ret;
}
