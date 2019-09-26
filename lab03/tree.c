/* Nome: Seu nome aqui 
 * RA: Seu RA aqui 
 * Laboratorio 05 - Pré, In e Pós */

void cria(No *raiz, char chave){
  raiz = malloc(sizeof(No));
  raiz->nome = chave;
  raiz->esq = NULL;
  raiz->dir = NULL;