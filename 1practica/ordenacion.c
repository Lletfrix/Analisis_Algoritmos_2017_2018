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
/* Funcion: BubbleSort    Fecha: 19/10/2017        */
/* Autores: Rafael Sánchez, Sergio Galán           */
/*                                                 */
/* Funcion que ordena una tabla por el método de   */
/* la burbuja                                      */
/*                                                 */
/* Entrada:                                        */
/* int* tabla: Array de enteros a ordenar          */
/* int ip: Indice del elemento desde el que ordenar*/
/* int iu: Indice del elemento hasta el que ordenar*/
/* Salida:                                         */
/* int: Numero de veces que se ejecutó la OB       */
/* ERR en caso de error                            */
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
