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

PDICC ini_diccionario (int tamanio, char orden)
{
	/* vuestro codigo */
}

void libera_diccionario(PDICC pdicc)
{
	/* vuestro codigo */
}

int inserta_diccionario(PDICC pdicc, int clave)
{
	/* vuestro codigo */
}

int insercion_masiva_diccionario (PDICC pdicc,int *claves, int n_claves)
{
	/* vuestro codigo */
}

int busca_diccionario(PDICC pdicc, int clave, int *ppos, pfunc_busqueda metodo)
{
	/* vuestro codigo */
}


/* Funciones de busqueda del TAD Diccionario */
int bbin(int *tabla,int P,int U,int clave,int *ppos)
{
	/* vuestro codigo */
}

int blin(int *tabla,int P,int U,int clave,int *ppos)
{
	/* vuestro codigo */
}

int blin_auto(int *tabla,int P,int U,int clave,int *ppos)
{
	/* vuestro codigo */
}


