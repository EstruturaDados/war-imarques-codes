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

// ================= CADASTRO =================

void cadastrarTerritorios(Territorio *t, int n) {
    for (int i = 0; i < n; i++) {
        printf("\n=== Cadastro do Territorio %d ===\n", i + 1);

        printf("Nome: ");
        fgets(t[i].nome, 30, stdin);
        t[i].nome[strcspn(t[i].nome, "\n")] = '\0';

        printf("Cor do exercito: ");
        fgets(t[i].cor, 10, stdin);
        t[i].cor[strcspn(t[i].cor, "\n")] = '\0';

        printf("Numero de tropas: ");
        scanf("%d", &t[i].tropas);
        getchar(); // limpa buffer
    }
}

// ================= EXIBIÇÃO =================

void mostrarTerritorios(Territorio *t, int n) {
    printf("\n===== MAPA ATUAL =====\n");

    for (int i = 0; i < n; i++) {
        printf("\n[%d] %s\n", i + 1, t[i].nome);
        printf("Cor: %s\n", t[i].cor);
        printf("Tropas: %d\n", t[i].tropas);
    }
}

// ================= BATALHA =================

void batalhar(Territorio *t, int atacante, int defensor) {

    // Gerar "dados" aleatórios (1 a 6)
    int dadoAtaque = rand() % 6 + 1;
    int dadoDefesa = rand() % 6 + 1;

    printf("\n=== BATALHA ===\n");
    printf("Atacante (%s) tirou: %d\n", t[atacante].nome, dadoAtaque);
    printf("Defensor (%s) tirou: %d\n", t[defensor].nome, dadoDefesa);

    if (dadoAtaque > dadoDefesa) {
        printf(">>> Ataque venceu!\n");
        t[defensor].tropas--;

        if (t[defensor].tropas <= 0) {
            printf(">>> Territorio conquistado!\n");

            // Transferir domínio (cor)
            strcpy(t[defensor].cor, t[atacante].cor);
            t[defensor].tropas = 1;
        }

    } else if (dadoDefesa > dadoAtaque) {
        printf(">>> Defesa venceu!\n");
        t[atacante].tropas--;

    } else {
        printf(">>> Empate! Nenhuma perda.\n");
    }
}

// ================= MAIN =================

int main() {

    int n = 5;

    // Alocação dinâmica com calloc
    Territorio *territorios = (Territorio*) calloc(n, sizeof(Territorio));

    if (territorios == NULL) {
        printf("Erro de memoria!\n");
        return 1;
    }

    srand(time(NULL));

    cadastrarTerritorios(territorios, n);

    int atacante, defensor;
    char continuar;

    do {
        mostrarTerritorios(territorios, n);

        printf("\nEscolha o territorio atacante (1-5): ");
        scanf("%d", &atacante);

        printf("Escolha o territorio defensor (1-5): ");
        scanf("%d", &defensor);

        // Ajustar índice (usuário começa em 1)
        atacante--;
        defensor--;

        // Validação básica
        if (atacante < 0 || atacante >= n || defensor < 0 || defensor >= n || atacante == defensor) {
            printf("Escolha invalida!\n");
        } else {
            batalhar(territorios, atacante, defensor);
        }

        printf("\nDeseja continuar? (s/n): ");
        scanf(" %c", &continuar);
        getchar();

    } while (continuar == 's');

    // Liberar memória
    free(territorios);

    return 0;
}