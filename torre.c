#include <stdio.h>
#include <ctype.h>
#include "torre.h"

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void inicializarTorres(Torre torres[], int num_discos) {
    for (int i = 0; i < TORRES; i++)
        torres[i].topo = -1;
    for (int i = 0; i < num_discos; i++)
        torres[0].discos[i] = num_discos - i;
    torres[0].topo = num_discos - 1;
}

int indiceTorre(char c) {
    c = toupper(c);
    if (c == 'A') return 0;
    if (c == 'B') return 1;
    if (c == 'C') return 2;
    return -1;
}

int peek(Torre torres[], int torre) {
    if (torres[torre].topo == -1) return -1;
    return torres[torre].discos[torres[torre].topo];
}

int pop(Torre torres[], int torre) {
    if (torres[torre].topo == -1) return -1;
    return torres[torre].discos[torres[torre].topo--];
}

void push(Torre torres[], int torre, int disco) {
    torres[torre].discos[++torres[torre].topo] = disco;
}

int moverDisco(Torre torres[], int num_discos, int* movimentos, char origem, char destino) {
    int iO = indiceTorre(origem), iD = indiceTorre(destino);
    if (iO < 0 || iD < 0 || torres[iO].topo < 0) {
        printf("Movimento inválido!\n");
        return 0;
    }
    int dO = peek(torres, iO), dD = peek(torres, iD);
    if (dD != -1 && dD < dO) {
        printf("Movimento inválido! Disco maior sobre menor.\n");
        return 0;
    }
    pop(torres, iO);
    push(torres, iD, dO);
    (*movimentos)++;
    return 1;
}

void exibirTorres(Torre torres[], int num_discos) {
    int maxLargura = num_discos * 2 - 1, espacoEntre = 8;
    for (int nivel = num_discos - 1; nivel >= 0; nivel--) {
        for (int t = 0; t < TORRES; t++) {
            int disco = (nivel <= torres[t].topo) ? torres[t].discos[nivel] : -1;
            int largura = (disco > 0 ? disco * 2 - 1 : 1);
            int espacos = (maxLargura - largura) / 2;
            for (int i = 0; i < espacos; i++) printf(" ");
            if (disco == -1) printf("|");
            else for (int i = 0; i < largura; i++) printf("=");
            for (int i = 0; i < espacos; i++) printf(" ");
            for (int i = 0; i < espacoEntre; i++) printf(" ");
        }
        printf("\n");
    }
    for (int t = 0; t < TORRES; t++) {
        for (int i = 0; i < maxLargura; i++) printf("-");
        for (int i = 0; i < espacoEntre; i++) printf(" ");
    }
    printf("\n");
    for (int t = 0; t < TORRES; t++) {
        int esq = (maxLargura - 1) / 2;
        for (int i = 0; i < esq; i++) printf(" ");
        printf("%c", 'A' + t);
        for (int i = 0; i < esq; i++) printf(" ");
        for (int i = 0; i < espacoEntre; i++) printf(" ");
    }
    printf("\n");
}

int jogoConcluido(Torre torres[], int num_discos) {
    return torres[2].topo == num_discos - 1;
}
