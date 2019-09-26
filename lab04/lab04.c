/* Nome: Ana Carolina R. Barbosa 
 * RA: 163755
 * Laboratorio 04 - Soltando bolas em uma árvore */

#include <stdio.h>
#include <stdlib.h> 
#include "lab04.h"

/* Cria a arvore */
void cria(No **raiz, int chave, int num){
  /* Enquanto a chave for menor ou igual que o numero de nos da arvore, cria a arvore */
  if(chave <= num){
    *raiz = malloc(sizeof(No));
    (*raiz)->num = chave;
    (*raiz)->flag = 0;
    (*raiz)->esq = NULL;
    (*raiz)->dir = NULL;
    cria(&(*raiz)->esq, 2*chave, num);
    cria(&(*raiz)->dir, 2*chave+1, num);
  }
}

/* Libera a arvore */
void destroi(No **p){
  if (*p) {
    destroi(&(*p)->esq);
    destroi(&(*p)->dir);
    free(*p);
  }
}

/* Reproduz o caminho feito pela bola */
void caminho(No **p, int *final){
  /* Se a bola estiver numa das extremidades da arvore, guarda o local onde a bola parou na variavel final */
  if ((*p)->esq == NULL) {
    *final = (*p)->num;
  } 
  /* Caso contrario, executa o caminho */    
  else {
    /* Se a flag for true, muda a flag para false e a bola vai para a direita */
    if((*p)->flag){
      (*p)->flag = 0;
      caminho(&(*p)->dir, &(*final));
    } 
    /* Caso contrario, muda a flag para true e a bola vai para a esquerda */
    else {
      (*p)->flag = 1;
      caminho(&(*p)->esq, &(*final));
    }
  }
  
}
