/* Nome: Ana Carolina R. Barbosa 
* RA: 163755
* Laboratorio 01 - O problema do acesso à lista */

#include <stdio.h>
#include <stdlib.h>

/* Struct da lista ligada */
typedef struct Lista { 
  int info;
  struct Lista *prox;
} Lista;


/* Insere um novo elemento a lista */
Lista *insere_lista(int chave, Lista *ini){
  Lista *novo;
  novo = malloc(sizeof(Lista));
  novo->info = chave;
  novo->prox = ini->prox;
  ini->prox = novo;
  return novo;
}

/* Imprime a lista */
void imprime_lista(Lista *ini) { 
  if (ini) {
    printf("%d ", ini->info);
    imprime_lista(ini->prox);
  }
}



void move_to_front(char c, int k, Lista *ini){
  Lista *p = ini, *q;
  
  while (p && p->info != k){
    q = p;
    p = p->prox;
    custo++;
  }
  
  if(c == 'a'){
    q->prox = p->prox;
    p->prox = ini->prox;
    ini->prox = p;
  }
  
  if(c == 'i'){
    q = insere_lista(k, q);
  }
  
}


int main() {
  int tam, num, i, k, *custo_mtf, *custo_tr;
  char c;
  Lista *ini1, *ini2, *q, *p;
  
  /* Nos cabecas das listas */
  ini1 = malloc(sizeof(Lista));
  ini1->prox = NULL;
  ini2 = malloc(sizeof(Lista));
  ini2->prox = NULL;
  
  p = ini1;
  q = ini2;  
  
  /* Escaneia o tamanho inicial da lista e o numero de comandos */
  scanf("%d %d", &tam, &num);
  
  /* Escaneia os elementos e insere-os na lista */
  for(i = 0; i < tam; i++){
    scanf("%d", &k);
    p = insere_lista(k, p);
    q = insere_lista(k, q);
  }
  
  for(i = 0; i < num; i++){
    scanf("%c %d", &c, &k);
    move_to_front(c, k, ini1);
    transpose(c, k, ini2);
  }
  
  imprime_lista(ini1->prox);  
  imprime_lista(ini2->prox);
  
  return 0; 
} 

