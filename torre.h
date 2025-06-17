#ifndef TORRE_H
#define TORRE_H

#define MAX_DISCOS 10
#define TORRES 3

typedef struct {
    int discos[MAX_DISCOS];
    int topo;
} Torre;

void inicializarTorres(Torre torres[], int num_discos);
void exibirTorres(Torre torres[], int num_discos);
int moverDisco(Torre torres[], int num_discos, int* movimentos, char origem, char destino);
int jogoConcluido(Torre torres[], int num_discos);
void limparBuffer();

#endif
