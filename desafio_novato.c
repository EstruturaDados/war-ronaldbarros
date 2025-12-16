// PROGRAMA DE CADASTRO DE TERRITÓRIOS PARA JOGO WAR (NÍVEL NOVATO)

#include <stdio.h>
#include <string.h>

// Definição de struct
struct Territorio{
    char nome[30];
    char cor[10];
    int tropas;
};

// Declaração do vetor de estruturas
struct Territorio lista_territorios[5];

// Função principal
int main(){


    printf("=======================================================\n");
    printf("------------- Cadastro de Territórios WAR -------------\n");
    printf("=======================================================\n");
    printf("\nInsira os dados para os 5 territórios.\n\n\n");

    int i;

    // Laço para iterar 5 vezes
    for (i = 0; i < 5; i++){
        // Mensagem para solicitar dados de 1 a 5
        printf("\n----------Cadastrando número %d de 5 ----------\n", i + 1);

        // Nome
        printf("\nNome do território: ");
        scanf("%s", lista_territorios[i].nome);

        // Cor
        printf("\nCor do exército: " );
        scanf("%s", lista_territorios[i].cor);

        // Quantidade
        printf("\nNúmero de tropas: ");
        scanf("%d", &lista_territorios[i].tropas);

    }

    printf("\nCadastro de todos os 5 territórios concluído!\n");
    printf("\n=============================================");
    printf("\n        MAPA DO MUNDO - ESTADO ATUAL         ");
    printf("\n=============================================\n");

    // Laço para exibir os dados
    for (i = 0; i < 5; i++){
        printf("\nTerritório %d:\n", i + 1);
        printf(" Nome: %s\n", lista_territorios[i].nome);
        printf(" Cor: %s\n", lista_territorios[i].cor);
        printf(" Tropas: %d\n", lista_territorios[i].tropas);
    }
    printf("\n---------------------------------------------\n");

    return 0;
}

