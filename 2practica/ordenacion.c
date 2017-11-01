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
#include <math.h>
#include <stdlib.h>
/* Funciones privada */
int merge (int* tabla, int ip, int iu, int imedio);
int partir(int* tabla, int ip, int iu, int *pos);
int medio (int *tabla, int ip, int iu, int *pos);
int medio_avg (int *tabla, int ip, int iu, int *pos);
int medio_stat (int *tabla, int ip, int iu, int *pos);

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


/***************************************************/
/* Funcion: MergeSort    Fecha: 20/10/2017         */
/* Autores: Rafael Sánchez, Sergio Galán           */
/*                                                 */
/* Funcion que ordena una tabla por el método de   */
/* merge sort                                      */
/*                                                 */
/* Entrada:                                        */
/* int* tabla: Array de enteros a ordenar          */
/* int ip: Indice del elemento desde el que ordenar*/
/* int iu: Indice del elemento hasta el que ordenar*/
/* Salida:                                         */
/* int: Numero de veces que se ejecutó la OB       */
/* ERR en caso de error                            */
/***************************************************/
int MergeSort (int* tabla, int ip, int  iu){
  int im, errcode;
  if (!tabla || ip > iu){
    return ERR;
  }
  if (ip == iu){
    return 0;
  }
  im = floor((ip+iu)/2);
  errcode = MergeSort(tabla, ip, im);
    if(errcode == ERR){
      return ERR;
    }
  errcode = MergeSort(tabla, im+1, iu);
    if(errcode == ERR){
      return ERR;
    }
  return merge(tabla, ip, iu, im);
}

/***************************************************/
/* Funcion: QuickSort    Fecha: 20/10/2017         */
/* Autores: Rafael Sánchez, Sergio Galán           */
/*                                                 */
/* Funcion que ordena una tabla por el método de   */
/* Quick Sort                                     */
/*                                                 */
/* Entrada:                                        */
/* int* tabla: Array de enteros a ordenar          */
/* int ip: Indice del elemento desde el que ordenar*/
/* int iu: Indice del elemento hasta el que ordenar*/
/* Salida:                                         */
/* int: Numero de veces que se ejecutó la OB       */
/* ERR en caso de error                            */
/***************************************************/
int QuickSort (int* tabla, int ip, int  iu){
  int errcode1 = 0, errcode2 = 0, c, *pivote = NULL;

  if (!tabla || ip > iu){
    return ERR;
  }
  if (ip == iu){
    return 0;
  }
  pivote = calloc(1, sizeof(int));
  if(!pivote){
  	return ERR;
  }
  c = partir(tabla, ip, iu, pivote);
  if(ip < (*pivote) -1){
    errcode1 = QuickSort(tabla, ip, (*pivote)-1);
    if(errcode1 == ERR){
      free(pivote);
      return ERR;
    }
  }
  if((*pivote)+1 < iu){
    errcode2 = QuickSort(tabla, (*pivote)+1, iu);
    if(errcode2 == ERR){
      free(pivote);
      return ERR;
    }
  }
  free(pivote);
  return errcode1 + errcode2 + c;
}

int merge (int* tabla, int ip, int iu,  int imedio){
  int* taux, i,j,k, nOb=0;
  if(!tabla){
    return ERR;
  }
  taux = calloc(iu-ip+1, sizeof(int));
  if(!taux){
    return ERR;
  }
  i=ip;
  k=0;
  j=imedio+1;
  while (i <= imedio && j<=iu) {
    if(tabla[i] < tabla[j]){
      taux[k]=tabla[i];
      i++;
    }else{
      taux[k]=tabla[j];
      j++;
    }
    k++;nOb++;
  }
  if (i>imedio){
    while (j <= iu) {
      taux[k]=tabla[j];
      j++;k++;
    }
  }else if (j>iu){
    while (i <= imedio){
      taux[k]=tabla[i];
      i++;k++;
    }
  }
  for (k=0; ip <=iu; ip++, k++) {
    tabla[ip]=taux[k];
  }
  free(taux);
  return nOb;
}


int partir(int* tabla, int ip, int iu, int *pos){
  int temp, k, i, nOb = 0, ret;
  ret = medio(tabla, ip, iu, pos);
  if(ERR == ret){
    return ERR;
  }
  nOb += ret;
  k = tabla[*pos];
  temp = tabla[*pos];
  tabla[*pos] = tabla[ip];
  tabla[ip] = temp;
  *pos = ip;
  for (i = ip+1; i <= iu; i++) {
    if(tabla[i] < k){
      *pos = (*pos)+1 ;
      temp = tabla[i];
      tabla[i] = tabla[*pos];
      tabla[*pos] = temp;
    }
    nOb++;
  }
  temp = tabla[ip];
  tabla[ip] = tabla[*pos];
  tabla[*pos] = temp;
  return nOb;
}
int medio (int *tabla, int ip, int iu, int *pos){
  *pos = ip;
  return 0;
}
int medio_avg (int *tabla, int ip, int iu, int *pos){
  *pos = floor((ip+iu)/2);
  return 0;
}
int medio_stat (int *tabla, int ip, int iu, int *pos){
  int medio = floor((ip+iu)/2);
  int a = tabla[ip], b = tabla[medio], c = tabla[iu];
  if ((b - a) * (c - b) >= 0){ /* c > b > a || c < b < a */
    *pos = medio;
    return 1;
  }
  if((a - b) * (c - a) >= 0){
    *pos = ip;
    return 2;
  }
  *pos = iu;
  return 2;
}
