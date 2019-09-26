/* Nome: Ana Carolina R. Barbosa 
 * RA: 163755
 * Laboratorio 04 - Soltando bolas em uma árvore */
 
#include <stdio.h>
#include <stdlib.h> 

typedef struct arv_no{
  int num;
  unsigned int flag;
  struct arv_no *esq, *dir;
} No;


typedef struct arbin{
  No *raiz;
  int depth;
} arbin;

void cria(No **raiz, int chave, int num);
void destroi(No **p);
void caminho(No **p, int *final);
