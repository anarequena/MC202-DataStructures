/* Nome: Ana Carolina R.Barbosa
 * RA: 163755
 * Laboratorio 02 - Matrioshkas Generalizadas */

#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"
#include "matrioshka.h"
 
int main (){
  No *ini;
  int tam, mat, i, true, false;
  
  ini = malloc(sizeof(No));
  ini->prox = NULL;
  
  /* Realiza os comandos enquanto tamanho for diferente de 0 */
  do {
    false = 0;
    /* Escaneia o tamanho da sequencia */
    scanf("%d", &tam);
    if(tam){  
      for(i=0; i<tam; i++){
	scanf("%d", &mat);
	/* Se o topo for NULL ou diferente de zero, executa a funcao matrioshka */
	if((ini->prox == NULL) || (ini->prox->info != 0)){
	  true = matrioshka(mat, ini);
	} else
	  false = 1;
	
	if(true < 0)
	  false = 1;
      }
      
      /* Se o topo for igual a zero, eh Matrioshka */
      if((!false) && (ini->prox->info == 0) && (i == tam))
	printf("Eh Matrioshka.\n");
      /* Se a boneca maior for fechada e ainda nao foram lidos todos os numeros,
      * nao eh Matrioshka */
      else
	printf("Nao eh Matrioshka.\n");
      
      while(ini->prox)
	remove_pilha(ini);
    }
  }while(tam);
  
  
  return 0;  
}