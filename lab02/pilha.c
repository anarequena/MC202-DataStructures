/* Nome: Ana Carolina R.Barbosa
 * RA: 163755
 * Laboratorio 02 - Matrioshkas Generalizadas */

#include <stdlib.h>
#include "pilha.h"

/* Insere um elemento no topo da pilha */
void insere(int chave, int tam_boneca, No *ini) {
  No *q = malloc(sizeof(No));
  
  q->info = chave;
  q->tam = tam_boneca;
  q->prox = ini->prox;
  ini->prox = q;
}

/* Remove o elemento do topo da pilha */
void remove_pilha(No *ini) {
  No *q = ini->prox;
  ini->prox = q->prox;
  free(q);
}
