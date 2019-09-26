/* Nome: Ana Carolina R. Barbosa
 * RA: 163755 
 * Laboratorio 07 - Filas de Prioridade com Duas Extremidades */
 
 
#include <stdio.h>
#include <stdlib.h>
#include "lab07.h"
#define MAX 259


int main (){
  heap V[MAX];
  int elem, impar, i, troca, nos, insere, true = 1;
  char com;
  
  scanf("%d", &elem);
  
  impar = elem%2;
  nos = elem/2;
  
  for(i=1; i<=nos; i++){
    scanf("%d %d", &V[i].min, &V[i].max);
    
    /* Se o min do novo elemento for maior que o max, troca os dois */
    if(V[i].min > V[i].max){
      troca = V[i].max;
      V[i].max = V[i].min;
      V[i].min = troca;
    }
  }
  
  /* Se o num de elementos for impar, 
   * aumenta o numeo de no e insere apenas um elemento no ultimo no */
  if(impar){
    nos++;
    scanf("%d", &V[i].min);
    V[i].max = 0;
    /* Se o min no novo elemento for maior que seu pai, troca o elem para o max */
    if((i > 1) && (V[i].min > V[i/2].max)){
      V[i].max = V[i].min;
      V[i].min = 0;
    }
  }
  
  /* Arruma o vetor de forma que seja um heap */
  constroi_heap(V, nos);
  
  while(true){
    scanf("%c", &com);
    /* Se chegar ao fim, para o loop */
    if((com == 'f') || (com == 'F'))
      true = 0;
    /* Se o comando for 'i', insere o novo elemento */
    else if(com == 'i'){
      scanf("%d", &insere);
      /* Se tiver um numero par de elementos, a insercao adiciona um novo no */
       
      elem = insert(V, elem, insere);
    }
    /* Se o comando for 'm', remove o elemento min da raiz */
    else if(com == 'm')
      elem = rem_menor(V, elem);
    /* Se o comando for 'M', remove o elemento max da raiz */  
    else if(com == 'M')
      elem = rem_maior(V, elem);
  } 
  
  /* Confere se o novo num de elementos é impar */
  impar = elem%2;
  
  if(impar)
    elem++;
  printf("\n");
  /* Imprime a pre-ordem minima e maxima */
  printf("Min-heap:");
  preordem_min(V, elem/2, 1);
  printf(" \n");
  printf("Max-heap:");
  preordem_max(V, elem/2, 1);
  printf(" \n");  
  
  
  return 0;
  
}