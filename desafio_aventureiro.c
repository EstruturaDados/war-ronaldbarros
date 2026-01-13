// PROGRAMA DE CADASTRO DE TERRITÓRIOS PARA JOGO WAR (NÍVEL NOVATO)

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

// Definição de struct
struct Territorio{
    char nome[30];
    char cor[10];
    int tropas;
};

// Função de cadastro de territórios
void cadastrar_territorios(struct Territorio *territorio, int num_territorios)
{
    int i;
    for (i = 0; i < num_territorios; i++){
        // Mensagem para solicitar dados de 1 a 5
        printf("\n----------Cadastrando número %d de %d ----------\n", i + 1, num_territorios);

        // Nome
        printf("\nNome do território: ");
        scanf("%29s", (territorio + i)->nome);

        // Cor
        printf("\nCor do exército: " );
        scanf("%9s", (territorio + i)->cor);
        // Quantidade
        printf("\nNúmero de tropas: ");
        scanf("%d", &(territorio + i)->tropas);

    }

    printf("\nCadastro de todos os %d territórios concluído!\n", num_territorios);
}

// Função de exibição dos territórios
void exibir_territorios(struct Territorio *territorio, int num_territorios)
{
    int i;
    printf("\n=============================================");
    printf("\n        MAPA DO MUNDO - ESTADO ATUAL         ");
    printf("\n=============================================\n");

    for (i = 0; i < num_territorios; i++){
        printf("\nTerritório %d:\n", i + 1);
        printf(" Nome: %s\n", (territorio + i)->nome);
        printf(" Cor: %s\n", (territorio + i)->cor);
        printf(" Tropas: %d\n", (territorio + i)->tropas);
    }
    printf("\n---------------------------------------------\n");
}

// Função de ataque
void atacar(struct Territorio *atacante, struct Territorio *defensor)
{
    int dado_atacante, dado_defensor;

    printf("\n=== COMBATE ===\n");
    printf("%s (Atacante) vs %s (Defensor)\n\n", atacante->nome, defensor->nome);

    // Simula o ataque e a defesa com dados de 6 lados
    dado_atacante = rand() % 6 + 1;
    dado_defensor = rand() % 6 + 1;
    printf("Atacante: %d | defensor: %d\n\n", dado_atacante, dado_defensor);

   // Regra: Atacante só vence se tirar MAIOR. Empate favorece defesa.
    if(dado_atacante > dado_defensor)
    {
        printf("Vitória do ataque! %s perde 1 tropa.\n", defensor->nome);
        defensor->tropas--;
    }
    else
    {
        printf("Vitória da defesa! %s perde 1 tropa.\n", atacante->nome);
        atacante->tropas--;
    }
    
    // VERIFICAÇÃO DE ELIMINAÇÃO / CONQUISTA
    if(defensor->tropas <= 0)
    {
        printf("\n!!! TERRITÓRIO CONQUISTADO !!!\n");
        printf("%s foi eliminado de %s.\n", defensor->cor, defensor->nome);
        
        // O defensor agora pertence ao atacante
        strcpy(defensor->cor, atacante->cor);
        
        // Movimentação de tropas: Atacante deve mover pelo menos 1 tropa.
        int tropas_transferidas = atacante->tropas / 2;
        if (tropas_transferidas < 1) tropas_transferidas = 1;

        defensor->tropas = tropas_transferidas;
        atacante->tropas -= tropas_transferidas;

        printf("%s agora é cor %s e recebeu %d tropas de ocupação.\n", 
               defensor->nome, defensor->cor, defensor->tropas);
    }

    printf("\nEstado: %s(%d) | %s(%d)\n", atacante->nome, atacante->tropas, defensor->nome, defensor->tropas);
}

// Função de execução de ataque entre dois territórios
void executar_ataque(struct Territorio *lista_territorios, int num_territorios) {
    int indice_atq, indice_def;
    char continuar_ataque, novo_combate;

    do {
        printf("\n=== SELEÇÃO DE ATAQUE ===\n");
        exibir_territorios(lista_territorios, num_territorios);

        // 1. Seleção do Atacante
        printf("\nEscolha o território atacante (1 a %d): ", num_territorios);
        if (scanf("%d", &indice_atq) != 1) return;
        indice_atq--; // Ajuste para índice 0 do array

        // 2. Seleção do Defensor
        printf("Escolha o território defensor (1 a %d): ", num_territorios);
        if (scanf("%d", &indice_def) != 1) return;
        indice_def--;

        // 3. Validações de Regra
        if (indice_atq < 0 || indice_atq >= num_territorios || 
            indice_def < 0 || indice_def >= num_territorios) {
            printf("Erro: Território inválido!\n");
        } 
        else if (indice_atq == indice_def) {
            printf("Erro: Um território não pode atacar a si mesmo!\n");
        } 
        else if (lista_territorios[indice_atq].tropas < 2) {
            printf("Erro: %s não tem tropas suficientes (mínimo 2)!\n", lista_territorios[indice_atq].nome);
        }
        else {
            // 4. Loop de Batalha
            do {
                // Chama a função de combate passando os endereços
                atacar(&lista_territorios[indice_atq], &lista_territorios[indice_def]);
                // Exibe o estado atualizado dos territórios
                exibir_territorios(lista_territorios, num_territorios);

                // Verifica se a conquista ocorreu (defensor mudou de cor)
                if (strcmp(lista_territorios[indice_atq].cor, lista_territorios[indice_def].cor) == 0) {
                    printf("Ataque encerrado: Território Conquistado!\n");
                    break;
                }

                // Verifica se o atacante ainda pode atacar
                if (lista_territorios[indice_atq].tropas < 2) {
                    printf("Ataque encerrado: Tropas insuficientes para continuar.\n");
                    break;
                }

                printf("\nDeseja continuar atacando de %s contra %s? (s/n): ", 
                        lista_territorios[indice_atq].nome, lista_territorios[indice_def].nome);
                scanf(" %c", &continuar_ataque);

            } while (continuar_ataque == 's' || continuar_ataque == 'S');
        }

        printf("\nDeseja iniciar um NOVO combate entre outros territórios? (s/n): ");
        scanf(" %c", &novo_combate);
    } while (novo_combate == 's' || novo_combate == 'S');
}

// Função principal
int main() {
    setlocale(LC_ALL, "Portuguese");
    srand(time(NULL)); // Inicializa o gerador de números aleatórios

    printf("=======================================================\n");
    printf("------------- Cadastro de Territórios WAR -------------\n");
    printf("=======================================================\n");

    int num_territorios;
    do {
        printf("\nDigite o número de territórios ou '0' para sair:\n> ");
        scanf("%d", &num_territorios);
        if (num_territorios == 0) {
            printf("Encerrando o programa.\n");
            return 0;
        }
        if (num_territorios < 2) {
            printf("O jogo requer pelo menos 2 territórios para iniciar.\n");
        }
    } while (num_territorios < 2);

    struct Territorio *lista_territorios = malloc(num_territorios * sizeof(struct Territorio));
    
    // Cadastro inicial
    cadastrar_territorios(lista_territorios, num_territorios);

    int opcao_menu = 0;
    while (1) { // LOOP DO MENU PRINCIPAL
        printf("\n========= MENU PRINCIPAL =========\n");
        printf("1. Ver Mapa de Territórios\n");
        printf("2. Iniciar Fase de Ataque\n");
        printf("3. Sair do Jogo\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao_menu);

        if (opcao_menu == 1) {
            exibir_territorios(lista_territorios, num_territorios);
        } 
        else if (opcao_menu == 2) {
            // Chama a função de ataque. 
            executar_ataque(lista_territorios, num_territorios);
        } 
        else if (opcao_menu == 3) {
            printf("Encerrando partida...\n");
            break; // Sai do loop principal
        } 
        else {
            printf("Opção inválida!\n");
        }
    }

    free(lista_territorios);
    return 0;
}