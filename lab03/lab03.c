/* Nome: Ana Carolina R. Barbosa
 * RA: 163755
 * Laboratorio 03 - Sistema Único de Saúde */

#include <stdio.h>
#include <stdlib.h>

typedef struct Fila {
  int num;
  struct Fila *prox;
} Paciente;

/* Finaliza a fila e libera a memória */
void finaliza_fila(Paciente *ini) {
  Paciente *p = ini->prox, *q;
  
  while (p != ini) {
    q = p->prox;
    free(p);
    p = q;
  }
  
  free(p);
}

/* Insere o paciente no final da fila */
void ins_fila(int pac, Paciente *ini, Paciente **fim) {
  Paciente *p = malloc(sizeof(Paciente));
  
  p->num = pac;
  (*fim)->prox = p;
  p->prox = ini;
  *fim = p;
}

/* Remove o paciente do começo da fila */
int rem_fila(Paciente **ini, Paciente *fim) {
  Paciente *p;
  int pac;
  
  p = (*ini)->prox;
  pac = p->num;
  (*ini)->prox = p->prox;
  
  if (fim == p) 
    fim = *ini;
  
  free(p);
  return pac;
}


void emergencia(Paciente **ini, int pac) {
  Paciente *p = (*ini)->prox, *q = (*ini);
  
  while (p && p->num != pac){
    p = p->prox;
    q = q->prox;
  }
  
  q->prox = p->prox;
  p->prox = (*ini)->prox;
  (*ini)->prox = p;   
  
}


void imprime_fila(Paciente *ini){
  Paciente *p = ini->prox;
  
  while(p != ini){
    printf("%d ", p->num);
    p = p->prox;
  }
  
  printf("\n");
}


int main() {
  Paciente *fim, *ini;
  int pacientes, pac, i;
  char evento;
  
  /* Inicia lista circular */
  ini = malloc(sizeof(Paciente));
  ini->prox = ini;
  fim = ini;
  
  scanf("%d", &pacientes);
  
  for(i=0; i < pacientes; i++){
    ins_fila(i+1, ini, &fim);
  }
  /*
  imprime_fila(ini);*/
  
  scanf(" %c", &evento);
  
  while(evento != 'F'){
    if(evento == 'A'){
      pac = rem_fila(&ini, fim);
      ins_fila(pac, ini, &fim);
      printf("%d\n", pac);
    }
    
    else if(evento == 'E'){
      scanf("%d", &pac);
      emergencia(&ini, pac);
    }
    /*
    imprime_fila(ini);*/
    
    scanf(" %c", &evento);
  }
  
  
  finaliza_fila(ini);
  
  return 0;

} 
