#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ================= STRUCT =================

typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// ================= FUNÇÕES =================

// Atribui missão aleatória
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int indice = rand() % totalMissoes;
    strcpy(destino, missoes[indice]);
}

// Exibe missão (apenas uma vez)
void exibirMissao(char* missao) {
    printf("\n>>> SUA MISSAO: %s\n", missao);
}

// Verifica missão (lógica simples)
int verificarMissao(char* missao, Territorio* mapa, int tamanho) {

    // Exemplo 1: conquistar 3 territórios
    if (strstr(missao, "3 territorios") != NULL) {
        int count = 0;

        for (int i = 0; i < tamanho; i++) {
            if (mapa[i].tropas > 0)
                count++;
        }

        if (count >= 3)
            return 1;
    }

    // Exemplo 2: eliminar tropas vermelhas
    if (strstr(missao, "vermelha") != NULL) {
        int existe = 0;

        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "vermelha") == 0 && mapa[i].tropas > 0) {
                existe = 1;
            }
        }

        if (!existe)
            return 1;
    }

    return 0;
}

// Mostrar mapa
void exibirMapa(Territorio* t, int n) {
    printf("\n===== MAPA =====\n");

    for (int i = 0; i < n; i++) {
        printf("[%d] %s | Cor: %s | Tropas: %d\n",
               i + 1, t[i].nome, t[i].cor, t[i].tropas);
    }
}

// Simulação de ataque
void atacar(Territorio* t, int a, int d) {
    int dadoA = rand() % 6 + 1;
    int dadoD = rand() % 6 + 1;

    printf("\nAtaque: %d | Defesa: %d\n", dadoA, dadoD);

    if (dadoA > dadoD) {
        t[d].tropas--;

        if (t[d].tropas <= 0) {
            strcpy(t[d].cor, t[a].cor);
            t[d].tropas = 1;
            printf(">>> Territorio conquistado!\n");
        }
    } else if (dadoD > dadoA) {
        t[a].tropas--;
    } else {
        printf("Empate!\n");
    }
}

// Liberar memória
void liberarMemoria(Territorio* t, char* missao) {
    free(t);
    free(missao);
}

// ================= MAIN =================

int main() {

    srand(time(NULL));

    int n = 5;

    // Alocação dinâmica dos territórios
    Territorio* mapa = malloc(n * sizeof(Territorio));

    // Cadastro simples
    for (int i = 0; i < n; i++) {
        printf("\nTerritorio %d\n", i + 1);

        printf("Nome: ");
        scanf(" %[^\n]", mapa[i].nome);

        printf("Cor: ");
        scanf("%s", mapa[i].cor);

        printf("Tropas: ");
        scanf("%d", &mapa[i].tropas);
    }

    // ================= MISSÕES =================

    char* missoes[] = {
        "Conquistar 3 territorios",
        "Eliminar tropas da cor vermelha",
        "Dominar o mapa",
        "Conquistar 2 territorios seguidos",
        "Eliminar inimigo azul"
    };

    int totalMissoes = 5;

    // Alocação dinâmica da missão do jogador
    char* missaoJogador = malloc(100 * sizeof(char));

    atribuirMissao(missaoJogador, missoes, totalMissoes);
    exibirMissao(missaoJogador);

    // ================= LOOP DE JOGO =================

    int a, d;
    char continuar;

    do {

        exibirMapa(mapa, n);

        printf("\nAtacante (1-5): ");
        scanf("%d", &a);

        printf("Defensor (1-5): ");
        scanf("%d", &d);

        a--; d--;

        if (a >= 0 && a < n && d >= 0 && d < n && a != d) {
            atacar(mapa, a, d);
        } else {
            printf("Escolha invalida!\n");
        }

        // Verificação da missão (silenciosa)
        if (verificarMissao(missaoJogador, mapa, n)) {
            printf("\n>>> PARABENS! MISSAO CUMPRIDA!\n");
            break;
        }

        printf("\nContinuar? (s/n): ");
        scanf(" %c", &continuar);

    } while (continuar == 's');

    liberarMemoria(mapa, missaoJogador);

    return 0;
}