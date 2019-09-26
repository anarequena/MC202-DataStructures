/* Nome: Seu nome aqui 
 * RA: Seu RA aqui 
 * Laboratorio 05 - Pré, In e Pós */

#include <stdio.h>
#include <stdlib.h>
#define MAX 53

typedef struct Arv {
  char nome;
  struct Arv *esq, *dir;
} No;


void cria(No **raiz, char chave){
  (*raiz) = malloc(sizeof(No));
  (*raiz)->nome = chave;
  (*raiz)->esq = NULL;
  (*raiz)->dir = NULL;
}

void ImprimeNo(char c, int b) {
   int i;
   for (i=0; i<b; i++)
       printf("-----");
   printf("%c\n", c);
}
void ImprimeArv(No *p, int b) {
   if (!p) {
      ImprimeNo('*', b);
      return;
   }
   ImprimeArv(p->dir, b+1); 
   ImprimeNo(p->nome, b);
   ImprimeArv(p->esq, b+1);
}

void destroi(No **p){
  if (*p) {
    destroi(&(*p)->esq);
    destroi(&(*p)->dir);
    free(*p);
  }
}

void monta_arvore(No **raiz, char *pre, char *in, int inicio, int fim){
  int i = inicio;
  
  if(inicio < fim){
    while(in[i] != pre[inicio])
      i++;
    if((i > 0)&&(i < fim)){
      monta_arvore(&(*raiz)->esq, pre, in, inicio, inicio + i - 1);
      monta_arvore(&(*raiz)->dir, pre, in, inicio + i + 1, fim);
    } 
    else if(i == fim)
      monta_arvore(&(*raiz)->esq, pre, in, inicio, fim - 1);
    else if(i == 0)
      monta_arvore(&(*raiz)->dir, pre, in, 1, fim);
  }
  
  cria(&(*raiz), pre[inicio]);
}


int main () {
  No *raiz;
  char *pre, *in;
  int teste, nos, i;
  
  scanf("%d", &teste);
  
  raiz = malloc(sizeof(No));
  
  for(i=0; i<teste; i++){
    scanf("%d", &nos);
    
    pre = malloc(nos * sizeof(char));
    in = malloc(nos * sizeof(char));
    
    scanf("%s %s", pre, in);
    
    printf("%s %s\n", pre, in);
    
    monta_arvore(&raiz, pre, in, 0, nos-1);
    
    ImprimeArv(raiz, 0);
  }
  
  return 0;
}
    

