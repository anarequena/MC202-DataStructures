/* Nome: Ana Carolina R. Barbosa 
 * RA: 163755
 * Laboratorio 04 - Soltando bolas em uma árvore */

#include <stdio.h>
#include <stdlib.h> 
#include <math.h>
#include "lab04.h"

int main () {
  arbin *Arvore;
  int i, j, k, testes, deep, bolas, final;
  double num_nos;
  
  Arvore = malloc(sizeof(arbin));
  
  scanf("%d", &testes);
  
  /* Enquanto ainda tiverem testes a serem feitos, executa as funcoes */ 
  for(i=0; i<testes; i++){
    scanf("%d %d", &deep, &bolas);
    
    /* Guarda a profundidade da arvore e calcula o numero de nos */
    Arvore->depth = deep;
    num_nos = pow(2, deep) - 1;
    k = (int) num_nos;
    
    /* Cria a arvore */
    cria(&Arvore->raiz, 1, k);
    
    /* Faz o caminho das j bolas */
    for(j=0; j<bolas; j++)
      caminho(&Arvore->raiz, &final);
    
    /* Imprime o no de chegada da ultima bola */  
    printf("%d\n", final);
    
    /* Libera a arvore criada */
    destroi(&Arvore->raiz);
  }

  /* Libera a Arvore */
  free(Arvore);
  return 0;
}
