/* Nome: Ana Carolina R. Barbosa
 * RA: 163755 
 * Laboratorio 07 - Filas de Prioridade com Duas Extremidades */
 
 
#include <stdio.h>
#include <stdlib.h>
#include "lab07.h"
#define MAX 259


void min_heap(heap V[], int nos, int pai) {
  int novo, indice = 2*pai, troca;
  
  if(indice <= nos){
    /* Aponta para o menor dos filhos */
    if(indice < nos)
      if((V[indice].min > V[indice + 1].min) && (V[indice + 1].min >0))
	indice++;
    
    /* Se o pai for maior que o filho, troca os elementos e chama a recursao */  
    if((V[indice].min > 0) && (V[pai].min > V[indice].min)) {
      novo = V[pai].min;
      V[pai].min = V[indice].min;
      V[indice].min = novo;
      
      
      
      /* Se o elemento minimo do no for maior que o elemento max, troca */
      if(V[indice].min > V[indice].max){
	troca = V[indice].max;
	V[indice].max = V[indice].min;
	V[indice].min = troca;
      }
      
      min_heap(V, nos, indice);
    }
    else if((V[indice].max > 0) && (V[pai].min > V[indice].max)){
      novo = V[pai].min;
      V[pai].min = V[indice].max;
      V[indice].max = novo;
      
      /* Se o elemento minimo do no for maior que o elemento max, troca */
      if(V[indice].min > V[indice].max){
	troca = V[indice].max;
	V[indice].max = V[indice].min;
	V[indice].min = troca;
      }
      
      min_heap(V, nos, indice);
    }      
  }
}  
      

void max_heap(heap V[], int nos, int pai) {
  int novo, indice = 2*pai, troca;
  
  if(indice <= nos){
    /* Aponta para o maior dos filhos */
    if((indice < nos) && (V[indice].max < V[indice + 1].max))
      indice++;
    
    /* Se o pai for menor que o filho, troca os elementos e chama a recursao */ 
    if(V[indice/2].max < V[indice].max) {
      novo = V[indice/2].max;
      V[indice/2].max = V[indice].max;
      V[indice].max = novo;
      
      /* Se o elemento minimo do no for maior que o elemento max, troca */
      if(V[indice].min > V[indice].max){
	troca = V[indice].max;
	V[indice].max = V[indice].min;
	V[indice].min = troca;
      }
      
      max_heap(V, nos, indice);
    } 
    else if(V[indice/2].max < V[indice].min){
      novo = V[indice/2].max;
      V[indice/2].max = V[indice].min;
      V[indice].min = novo;
      
      /* Se o elemento minimo do no for maior que o elemento max, troca */
      if(V[indice].min > V[indice].max){
	troca = V[indice].max;
	V[indice].max = V[indice].min;
	V[indice].min = troca;
      }
      
      max_heap(V, nos, indice);
    }      
  }    
}
  

void constroi_heap(heap V[], int nos) {
  int i;
  
  for(i = nos/2; i > 0; i--){
    max_heap(V, nos, i);    
    min_heap(V, nos, i); 
  }
}


int insert(heap V[], int elem, int chave) {
  int impar = elem%2, indice = elem/2+1, i, troca;
  
  /* Se o num de elementos for par, adiciona um novo no ao vetor */
  if(!impar){
    
    V[indice].max = 0;
    V[indice].min = chave;
    /* Se o elemento a ser inserido for menor que o min de seu pai,
     * atualiza o heap de minimo */
    if(chave < V[indice/2].min){
      for(i = indice/2; i > 0; i--)
	min_heap(V, indice, i);
    }
    /* Se o elemento a ser inserido for maior que o max de seu pai,
     * atualiza o heap de maximo */
    else if(chave > V[indice/2].max){
      for(i = indice/2; i > 0; i--)
	max_heap(V, indice, i);
    }
    return (elem+1);
  }
  
  else{
    if(V[indice].min == 0)
      V[indice].min = chave;
    else
      V[indice].max = chave;
    
    if(V[indice].min > V[indice].max){
      troca = V[indice].max;
      V[indice].max = V[indice].min;
      V[indice].min = troca;
    }
    
    if(V[indice].max > V[indice/2].max)
      for(i = indice/2; i > 0; i--)
	max_heap(V, indice, i);
    
    else if(V[indice].min < V[indice/2].min)
      for(i = indice/2; i>0; i--)
	min_heap(V, indice, i);
      
    return (elem+1);
  }
}


int rem_menor(heap V[], int elem){
  int i, impar = elem%2, indice = elem/2;

  /* Se o heap for vazio, imprime 'Fila vazia!" */
  if(elem == 0){
    printf("Fila vazia!\n");
    return 0;
  }
  
  /* Se o heap tiver apenas um elemento, devolve-o e deixa o heap vazio */
  else if(elem == 1){
    if(V[1].min){
      printf("%d\n", V[1].min);
      V[1].min = 0;
    }
    else {
      printf("%d\n", V[1].max);
      V[1].max = 0;
    }
    return 0;
  }
  
  else {
    /* Se o num de elementos for impar, aumento o indice */
    if(impar)
      indice++;
    
    if(V[1].min) printf("%d\n", V[1].min);
    else printf("%d\n", V[1].max);
    /* Se o min do ultimo no for diferente de 0, coloca-o na raiz */
    if(V[indice].min){
      V[1].min = V[indice].min;
      V[indice].min = 0;
    }
    /* Se nao, coloca o elemento max do ultimo no na raiz e apaga o ultimo no */
    else {
      V[1].min = V[indice].max;
      V[indice].max = 0;
      indice--;
    }
    
    /* Arruma o vetor de heap */
    for(i = indice/2; i > 0; i--){
      min_heap(V, indice, i);
    }
    
    /* Retorna o novo num de elementos */
    return (elem-1);
  }
}


int rem_maior(heap V[], int elem){
  int i, impar = elem%2, indice = elem/2;
  
  /* Se o heap for vazio, imprime 'Fila vazia!" */
  if(elem == 0){
    printf("Fila vazia!\n");
    return 0;
  }
  
  /* Se o heap tiver apenas um elemento, devolve-o e deixa o heap vazio */
  else if(elem == 1){
    if(V[1].min){
      printf("%d\n", V[1].min);
      V[1].min = 0;
    }
    else {
      printf("%d\n", V[1].max);
      V[1].max = 0;
    }
    return 0;
  }
  
  else {
    /* Se o num de elementos for impar, aumento o indice */
    if(impar)
      indice++;
    
    if(V[1].max) printf("%d\n", V[1].max);
    else printf("%d\n", V[1].min);
    /* Se o min do ultimo no for diferente de 0, coloca-o na raiz */
    if(V[indice].max){
      V[1].max = V[indice].max;
      V[indice].max = 0;
    }
    /* Se nao, coloca o elemento max do ultimo no na raiz e apaga o ultimo no */
    else {
      V[1].max = V[indice].min;
      V[indice].max = 0;
      indice--;
    }
    /* Arruma o vetor de heap */
    for(i = indice/2; i>0; i--)
      max_heap(V, indice, i);
    
    /* Retorna o novo num de elementos */
    return (elem-1);
  }
}
  
void preordem_max (heap V[], int n, int indice){
  if(indice <= n){
    if(V[indice].max == 0)
      printf(" %3d", V[indice].min);
    else
      printf(" %3d", V[indice].max);
    preordem_max(V, n, indice*2);
    preordem_max(V, n, indice*2+1);
  }
}


void preordem_min (heap V[], int n, int indice){
  if(indice <= n){
    if(V[indice].min == 0)
      printf(" %3d", V[indice].max);
    else
      printf(" %3d", V[indice].min);
    preordem_min(V, n, indice*2);
    preordem_min(V, n, indice*2+1);
  }
}
