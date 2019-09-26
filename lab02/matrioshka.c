/* Nome: Ana Carolina R.Barbosa
 * RA: 163755
 * Laboratorio 02 - Matrioshkas Generalizadas */

#include <stdio.h>
#include "pilha.h"
#include "matrioshka.h"

/* Verifica se eh Matrioshka ou nao */
int matrioshka(int chave, No *ini){
  
  /* Se o topo for diferente de NULL */
  if(ini->prox){
    /* Se o próximo numero for o inverso do topo, fecha a boneca */
    if(chave + ini->prox->info == 0){
      remove_pilha(ini);
    }
    /* Se o proximo numero for menor que o topo e for negativo, 
     * abre a boneca */
    else if((abs(chave) < abs(ini->prox->tam)) && (chave < 0)){
      ini->prox->tam -= chave;
      insere(chave, chave, ini);
    }
    /* Se o proximo numero for maior que o topo ou for maior que 0,
     * nao eh matrioshka */
    else if((abs(chave) > abs(ini->prox->info)) || (chave > 0)){
      insere(chave, chave, ini);
      return -1;
    }
    
  } 
  /* Se for o primeiro numero da pilha, insere 0 e depois a primeira boneca */
  else {
    insere(0, 0, ini);
    insere(chave, chave, ini);
  } 
  
  return 0;
}
   