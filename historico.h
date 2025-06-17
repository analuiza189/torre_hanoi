#ifndef HISTORICO_H
#define HISTORICO_H

typedef struct Historico {
    char jogador[50];
    int movimentos;
    int num_discos;
    char data[30];
    struct Historico* prox;
} Historico;

void salvarHistorico(Historico** lista, const char* jogador, int num_discos, int movimentos);
void exibirHistorico(Historico* lista);
void buscarHistorico(Historico* lista);
void liberarHistorico(Historico* lista);

#endif
