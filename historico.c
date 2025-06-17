#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "historico.h"

void salvarHistorico(Historico** lista, const char* jogador, int num_discos, int movimentos) {
    FILE* arquivo = fopen("historico.txt", "a");
    if (!arquivo) { printf("Erro ao abrir o histórico.\n"); return; }

    time_t agora = time(NULL);
    char data[30];
    strftime(data, sizeof(data), "%d/%m/%Y %H:%M:%S", localtime(&agora));

    fprintf(arquivo, "Jogador: %s | Discos: %d | Movimentos: %d | Data: %s\n",
        jogador, num_discos, movimentos, data);
    fclose(arquivo);

    Historico* novo = malloc(sizeof(Historico));
    if (!novo) { printf("Erro de memória.\n"); exit(1); }
    strcpy(novo->jogador, jogador);
    novo->num_discos = num_discos;
    novo->movimentos = movimentos;
    strcpy(novo->data, data);
    novo->prox = *lista;
    *lista = novo;
}

void exibirHistorico(Historico* lista) {
    if (!lista) { printf("\nNenhum histórico disponível.\n"); return; }
    printf("\n=== Histórico de Partidas ===\n");
    for (Historico* aux = lista; aux; aux = aux->prox)
        printf("Jogador: %s | Discos: %d | Movimentos: %d | Data: %s\n",
            aux->jogador, aux->num_discos, aux->movimentos, aux->data);
}

void buscarHistorico(Historico* lista) {
    char bj[50] = "", bd[30] = "";
    printf("Nome do jogador (ou ENTER): ");
    fgets(bj, sizeof(bj), stdin);
    bj[strcspn(bj, "\n")] = 0;
    printf("Data (dd/mm/aaaa, ou ENTER): ");
    fgets(bd, sizeof(bd), stdin);
    bd[strcspn(bd, "\n")] = 0;

    printf("\n=== Resultados da Busca ===\n");
    int found = 0;
    for (Historico* aux = lista; aux; aux = aux->prox) {
        if ((strlen(bj) == 0 || strstr(aux->jogador, bj)) &&
            (strlen(bd) == 0 || strstr(aux->data, bd))) {
            printf("Jogador: %s | Discos: %d | Movimentos: %d | Data: %s\n",
                aux->jogador, aux->num_discos, aux->movimentos, aux->data);
            found = 1;
        }
    }
    if (!found) printf("Nenhum resultado encontrado.\n");
}

void liberarHistorico(Historico* lista) {
    while (lista) {
        Historico* temp = lista;
        lista = lista->prox;
        free(temp);
    }
}
