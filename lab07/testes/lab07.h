/* Nome: Ana Carolina R. Barbosa
 * RA: 163755 
 * Laboratorio 07 - Filas de Prioridade com Duas Extremidades */
 
 
#include <stdio.h>
#include <stdlib.h>
#define MAX 259


typedef struct vetor {
  int min;
  int max;
} heap;

void min_heap(heap V[], int nos, int pai);

void max_heap(heap V[], int nos, int pai);

void constroi_heap(heap V[], int nos);

int insert(heap V[], int elem, int chave);

int rem_menor(heap V[], int elem);

int rem_maior(heap V[], int elem);

void preordem_max (heap V[], int n, int indice);

void preordem_min (heap V[], int n, int indice);