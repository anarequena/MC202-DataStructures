/* Nome: Ana Carolina R.Barbosa
 * RA: 163755
 * Laboratorio 02 - Matrioshkas Generalizadas */

#include <stdio.h>
#include <stdlib.h>

typedef struct Pilha {
  int info;
  int tam;
  struct Pilha *prox;
} No;

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

/* Verifica se eh Matrioshka ou nao */
void matrioshka(int chave, No *ini){
  
  /* Se o topo for diferente de NULL */
  if(ini->prox){
    /* Se o próximo numero for o inverso do topo, fecha a boneca */
    if(chave + ini->prox->info == 0)
      remove_pilha(ini);
    /* Se o proximo numero for menor que o topo e for negativo, 
     * abre a boneca */
    else if((abs(chave) < abs(ini->prox->tam)) && (chave < 0)){
      ini->prox->tam -= chave;
      insere(chave, chave, ini);
    }
    /* Se o proximo numero for maior que o topo ou for maior que 0,
     * nao eh matrioshka */
    else if((abs(chave) > abs(ini->prox->tam)) || (chave > 0))
      printf("Nao eh Matrioshka.\n");
    
  } 
  /* Se for o primeiro numero da pilha, insere 0 e depois a primeira boneca */
  else {
    insere(0, 0, ini);
    insere(chave, chave, ini);
  } 
}
 
int main (){
  No *ini;
  int tam, mat, i;
  
  ini = malloc(sizeof(No));
  ini->prox = NULL;
  
  /* Realiza os comandos enquanto tamanho for diferente de 0 */
  do {
    /* Escaneia o tamanho da sequencia */
    scanf("%d", &tam);
    
    for(i=1; i<tam; i++){
      /* Se o topo for NULL ou diferente de zero, executa a funcao matrioshka */
      if((ini->prox == NULL) || (ini->prox->info != 0)){
	/* Escaneia o numero e manda para a funcao matrioshka */
	scanf("%d", &mat);
	matrioshka(mat, ini);
      }
      /* Se a boneca maior for fechada e ainda nao foram lidos todos os numeros,
       * nao eh Matrioshka */
      else if(i < tam -1)
	printf("Nao eh Matrioshka.\n");
    }
    /* Se o topo for igual a zero, eh Matrioshka */
    if(ini->prox->info == 0)
      printf("Eh Matrioshka.\n");
    
  }while(tam);
  
  
  return 0;  
}