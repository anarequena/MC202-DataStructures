/* Nome: Ana Carolina R.Barbosa
 * RA: 163755
 * Laboratorio 02 - Matrioshkas Generalizadas */

#include <stdlib.h>

typedef struct Pilha {
  int info;
  int tam;
  struct Pilha *prox;
} No;

void insere(int chave, int tam_boneca, No *ini);

void remove_pilha(No *ini);