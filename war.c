#include <stdio.h>
#include <string.h>

// ================= STRUCT =================

// Struct que representa um território
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// ================= FUNÇÃO PRINCIPAL =================

int main() {

    // Vetor para armazenar 5 territórios
    Territorio territorios[5];

    // ================= ENTRADA DE DADOS =================

    for (int i = 0; i < 5; i++) {

        printf("\n=== Cadastro do Territorio %d ===\n", i + 1);

        // Leitura do nome (fgets permite espaços)
        printf("Digite o nome do territorio: ");
        fgets(territorios[i].nome, 30, stdin);

        // Remover o '\n' do final da string
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0';

        // Leitura da cor do exército
        printf("Digite a cor do exercito: ");
        fgets(territorios[i].cor, 10, stdin);
        territorios[i].cor[strcspn(territorios[i].cor, "\n")] = '\0';

        // Leitura do número de tropas
        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);

        // Limpa o buffer do teclado (IMPORTANTE após scanf)
        getchar();
    }

    // ================= SAÍDA DE DADOS =================

    printf("\n\n===== MAPA DE TERRITORIOS =====\n");

    for (int i = 0; i < 5; i++) {

        printf("\nTerritorio %d\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do exercito: %s\n", territorios[i].cor);
        printf("Tropas: %d\n", territorios[i].tropas);
    }

    return 0;
}