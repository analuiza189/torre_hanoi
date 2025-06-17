#include <stdio.h>
#include <string.h>
#include "torre.h"
#include "historico.h"

int main() {
    Torre torres[TORRES];
    Historico* listaHistorico = NULL;
    char nomeJogador[50];
    int num_discos, movimentos, opcao;

    do {
        printf("\n=== Torre de Hanoi ===\n1. Jogar\n2. Ver histórico\n3. Buscar histórico\n4. Sair\nEscolha: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                printf("Digite seu nome: ");
                fgets(nomeJogador, sizeof(nomeJogador), stdin);
                nomeJogador[strcspn(nomeJogador, "\n")] = 0;

                do {
                    printf("Número de discos (3 a %d): ", MAX_DISCOS);
                    scanf("%d", &num_discos);
                    limparBuffer();
                } while (num_discos < 3 || num_discos > MAX_DISCOS);

                inicializarTorres(torres, num_discos);
                movimentos = 0;

                while (!jogoConcluido(torres, num_discos)) {
                    exibirTorres(torres, num_discos);
                    char origem, destino;
                    printf("Mover de (A/B/C): ");
                    origem = getchar(); limparBuffer();
                    printf("Para (A/B/C): ");
                    destino = getchar(); limparBuffer();
                    moverDisco(torres, num_discos, &movimentos, origem, destino);
                }

                printf("Parabéns, %s! Completou em %d movimentos.\n", nomeJogador, movimentos);
                salvarHistorico(&listaHistorico, nomeJogador, num_discos, movimentos);
                break;

            case 2:
                exibirHistorico(listaHistorico);
                break;

            case 3:
                buscarHistorico(listaHistorico);
                break;

            case 4:
                printf("Saindo...\n");
                break;

            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 4);

    liberarHistorico(listaHistorico);
    return 0;
}
