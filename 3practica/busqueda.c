/**
 *
 * Descripcion: Implementacion funciones para busqueda
 *
 * Fichero: busqueda.c
 * Autor: Carlos Aguirre
 * Version: 1.0
 * Fecha: 11-11-2016
 *
 */

#include "busqueda.h"

#include <stdlib.h>
#include <math.h>

/**
 *  Funciones de geracion de claves
 *
 *  Descripcion: Recibe el numero de claves que hay que generar
 *               en el parametro n_claves. Las claves generadas
 *               iran de 1 a max. Las claves se devuelven en
 *               el parametro claves que se debe reservar externamente
 *               a la funcion.
 */

/**
 *  Funcion: generador_claves_uniforme
 *               Esta fucnion genera todas las claves de 1 a max de forma
 *               secuencial. Si n_claves==max entonces se generan cada clave
 *               una unica vez.
 */
void generador_claves_uniforme(int *claves, int n_claves, int max)
{
  int i;

  for(i = 0; i < n_claves; i++) claves[i] = 1 + (i % max);

  return;
}

/**
 *  Funcion: generador_claves_potencial
 *               Esta funcion genera siguiendo una distribucion aproximadamente
 *               potencial. Siendo los valores mas pequenos mucho mas probables
 *               que los mas grandes. El valor 1 tiene una probabilidad del 50%,
 *               el dos del 17%, el tres el 9%, etc.
 */
void generador_claves_potencial(int *claves, int n_claves, int max)
{
  int i;

  for(i = 0; i < n_claves; i++) {
    claves[i] = (1+max) / (1 + max*((double)rand()/RAND_MAX));
  }

  return;
}

void _swap_ (int *a, int *b){
  int temp;
  temp = *a;
  *a = *b;
  *b = temp;
}

PDICC ini_diccionario (int tamanio, char orden)
{
  DICC *d;
  if (tamanio <= 0 || (orden != ORDENADO && orden != NO_ORDENADO)) return NULL;
	d = calloc(1, sizeof(DICC));
  if (!d) return NULL;
  d->tabla = calloc(tamanio,sizeof(int));
  if(!d->tabla){
    free (d);
    return NULL;
  }
  d->tamanio = tamanio;
  d->n_datos = 0;
  d->orden = orden;
  return d;
}

void libera_diccionario(PDICC pdicc)
{
	if(!pdicc) return;
  free(pdicc->tabla);
  free(pdicc);
}

int inserta_diccionario(PDICC pdicc, int clave)
{
  int i, cdc;
	if(!pdicc) return ERR;
  if(pdicc->n_datos + 1 > pdicc->tamanio) return ERR;
  pdicc->tabla[pdicc->n_datos]=clave;
  if(pdicc->orden == NO_ORDENADO){
    pdicc->n_datos++;
    return 0;
  }
  if(pdicc->n_datos == 0){
    pdicc->n_datos++;
    return 0;
  }
  cdc = 0;
  i = pdicc->n_datos-1;
  while(clave < pdicc->tabla[i]){
    _swap_(&pdicc->tabla[i],&pdicc->tabla[i+1]);
    i--;
    cdc++;
  }
  pdicc->n_datos++;
  return cdc;
}

int insercion_masiva_diccionario (PDICC pdicc,int *claves, int n_claves)
{
  int i, cdc;
  if(!pdicc || !claves || n_claves < 1) return ERR;
  if(pdicc->n_datos + n_claves > pdicc->tamanio) return ERR;
  for (i = 0, cdc = 0; i < n_claves; i++){
    cdc += inserta_diccionario(pdicc, claves[i]);
  }
  return cdc;
}

int busca_diccionario(PDICC pdicc, int clave, int *ppos, pfunc_busqueda metodo)
{
  int cdc;
	if(!pdicc || !ppos || !metodo) return ERR;

  cdc = metodo(pdicc->tabla, 0, pdicc->n_datos-1, clave, ppos);
  return cdc;
}


/* Funciones de busqueda del TAD Diccionario */
int bbin(int *tabla, int P, int U, int clave,int *ppos)
{
  int i, cdc;
	if(!tabla || P < 0 || U < 0 || P > U) return ERR;
  for (cdc = 0, i = (P+U)/2; P <= U ;cdc++, i = (P+U)/2){
    if(clave == tabla[i]){
      *ppos = i;
      return cdc+1;
    }
    if(clave > tabla[i]){
      P = i + 1;
    }else{
      U = i -1;
    }
  }
  *ppos = NO_ENCONTRADO;
  return cdc;
}

int blin(int *tabla,int P,int U,int clave,int *ppos)
{
  int *taux, *end, cdc;
	if(!tabla || P < 0 || U < 0 || P > U) return ERR;
  for(taux = tabla + P, end = tabla + U, cdc = 0; taux <= end; taux++, cdc++){
    if(clave == *taux){
      *ppos = taux - tabla;
      return ++cdc;
    }
  }
  *ppos = NO_ENCONTRADO;
  return cdc;
}

int blin_auto(int *tabla,int P,int U,int clave,int *ppos)
{
  int *taux, *end, cdc=0;
	if(!tabla || P < 0 || U < 0 || P > U) return ERR;
  if(clave == *tabla){
    *ppos = 0;
    return ++cdc;
  }
  for(taux = tabla + P + 1, end = tabla + U, cdc = 1; taux <= end; taux++, cdc++){
    if(clave == *taux){
      _swap_(taux, taux-1);
      *ppos = taux - tabla - 1;
      return ++cdc;
    }
  }
  *ppos = NO_ENCONTRADO;
  return cdc;
}
