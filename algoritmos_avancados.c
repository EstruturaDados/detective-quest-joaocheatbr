// =================================================================
// PROJETO: DETECTIVE QUEST - O MAPA DA MANSÃO
// Desenvolvido para: Enigma Studios
// Finalidade: Ensinar conceitos de Árvore Binária em C para alunos.
// =================================================================

#include <stdio.h>
#include <stdlib.h> // Para alocação dinâmica (malloc) e para a função exit()
#include <string.h> // Para manipulação de strings (strcpy)

// -----------------------------------------------------------------
// ESTRUTURA DE DADOS
// -----------------------------------------------------------------
// Define a estrutura de uma Sala (nó da árvore).
// Cada sala tem um nome e ponteiros para os caminhos da
// esquerda e da direita.
// -----------------------------------------------------------------
struct Sala {
    char nome[50];
    struct Sala *esquerda;
    struct Sala *direita;
};

// -----------------------------------------------------------------
// PROTÓTIPOS DAS FUNÇÕES
// -----------------------------------------------------------------
// É uma boa prática declarar os "cabeçalhos" das funções aqui.
struct Sala* criarSala(const char* nome);
void explorarSalas(struct Sala* salaInicial);
void liberarMapa(struct Sala* sala); // Função bônus para liberar memória

// =================================================================
// FUNÇÃO PRINCIPAL (MAIN)
// =================================================================
// A função main() é o ponto de entrada do programa.
// Aqui, montamos o mapa inicial da mansão e damos início
// à exploração pelo jogador.
// =================================================================
int main() {
    // --- 1. Montagem do Mapa da Mansão ---
    // Criamos cada sala individualmente usando a função criarSala().
    // A raiz da nossa árvore será o 'Hall de Entrada'.
    struct Sala *hall = criarSala("Hall de Entrada");
    
    // Nível 1: Conectado ao Hall
    hall->esquerda = criarSala("Sala de Estar");
    hall->direita = criarSala("Sala de Jantar");
    
    // Nível 2: Conectado à Sala de Estar
    hall->esquerda->esquerda = criarSala("Biblioteca");
    hall->esquerda->direita = criarSala("Jardim de Inverno");
    
    // Nível 2: Conectado à Sala de Jantar
    hall->direita->esquerda = criarSala("Cozinha");
    
    // Nível 3: Conectado à Biblioteca
    hall->esquerda->esquerda->direita = criarSala("Escritorio Secreto");
    
    // Nível 3: Conectado à Cozinha
    hall->direita->esquerda->esquerda = criarSala("Despensa");

    // --- 2. Início da Exploração ---
    printf("======================================\n");
    printf(" BEM-VINDO AO DETECTIVE QUEST\n");
    printf("======================================\n");
    printf("Explore a mansão e descubra os segredos que ela esconde.\n");

    // Chama a função que controla a navegação do jogador,
    // começando pelo Hall de Entrada.
    explorarSalas(hall);

    // --- 3. Limpeza da Memória ---
    // Após o jogo terminar, liberamos toda a memória que foi alocada
    // para o mapa, evitando "memory leaks".
    liberarMapa(hall);
    printf("\nO mapa da mansão foi liberado da memória. Fim de jogo!\n");

    return 0; // Indica que o programa terminou com sucesso
}


// =================================================================
// IMPLEMENTAÇÃO DAS FUNÇÕES
// =================================================================

// -----------------------------------------------------------------
// Função: criarSala
// -----------------------------------------------------------------
// Responsabilidade: Alocar memória dinamicamente para uma nova
// sala (um novo nó), definir seu nome e inicializar seus
// caminhos (filhos) como nulos (NULL).
//
// Retorno: Um ponteiro para a sala recém-criada.
// -----------------------------------------------------------------
struct Sala* criarSala(const char* nome) {
    // Aloca espaço na memória do tamanho da estrutura 'Sala'.
    struct Sala* novaSala = (struct Sala*) malloc(sizeof(struct Sala));

    // Verifica se a alocação de memória foi bem-sucedida.
    // Se malloc retorna NULL, significa que não há memória disponível.
    if (novaSala == NULL) {
        printf("Erro: Falha ao alocar memória para uma nova sala.\n");
        exit(1); // Encerra o programa em caso de erro crítico.
    }

    // Copia o nome recebido para a variável 'nome' da struct.
    strcpy(novaSala->nome, nome);

    // Inicializa os ponteiros esquerda e direita como NULL.
    // Isso indica que, por padrão, uma nova sala não leva a lugar algum.
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;

    return novaSala; // Retorna o endereço da sala criada.
}


// -----------------------------------------------------------------
// Função: explorarSalas
// -----------------------------------------------------------------
// Responsabilidade: Controlar a navegação interativa do jogador
// pela mansão. A função executa um loop que continua até que o
// jogador chegue a uma sala sem saída (nó-folha) ou decida sair.
// -----------------------------------------------------------------
void explorarSalas(struct Sala* salaInicial) {
    struct Sala* salaAtual = salaInicial; // O jogador começa na sala inicial.
    char escolha;

    // O loop continua enquanto a sala atual for válida (não for NULL).
    while (salaAtual != NULL) {
        printf("\n--------------------------------------\n");
        printf("Você está em: %s\n", salaAtual->nome);
        printf("--------------------------------------\n");

        // Verifica se a sala atual é um "nó-folha" (sem saídas).
        if (salaAtual->esquerda == NULL && salaAtual->direita == NULL) {
            printf("Este cômodo não tem mais saídas. Fim da exploração neste caminho!\n");
            break; // Sai do loop while.
        }

        // Mostra as opções de caminho disponíveis.
        if (salaAtual->esquerda != NULL) {
            printf("[e] Ir para a Esquerda: %s\n", salaAtual->esquerda->nome);
        }
        if (salaAtual->direita != NULL) {
            printf("[d] Ir para a Direita: %s\n", salaAtual->direita->nome);
        }
        printf("[s] Sair do jogo\n");

        // Pede a entrada do jogador.
        printf("\nPara onde você quer ir? ");
        scanf(" %c", &escolha); // O espaço antes de %c ignora quebras de linha anteriores.

        // Processa a escolha do jogador.
        if (escolha == 'e' || escolha == 'E') {
            if (salaAtual->esquerda != NULL) {
                salaAtual = salaAtual->esquerda; // Move o jogador para a sala da esquerda.
            } else {
                printf("Caminho bloqueado. Não há nada à esquerda.\n");
            }
        } else if (escolha == 'd' || escolha == 'D') {
            if (salaAtual->direita != NULL) {
                salaAtual = salaAtual->direita; // Move o jogador para a sala da direita.
            } else {
                printf("Caminho bloqueado. Não há nada à direita.\n");
            }
        } else if (escolha == 's' || escolha == 'S') {
            printf("Você decidiu parar a exploração por enquanto...\n");
            break; // Sai do loop while.
        } else {
            printf("Opção inválida! Por favor, escolha 'e', 'd' ou 's'.\n");
        }
    }
}


// -----------------------------------------------------------------
// Função: liberarMapa (Bônus de Boas Práticas)
// -----------------------------------------------------------------
// Responsabilidade: Percorrer a árvore de forma recursiva e
// liberar a memória alocada para cada sala, evitando vazamentos
// de memória (memory leaks). A travessia é pós-ordem.
// -----------------------------------------------------------------
void liberarMapa(struct Sala* sala) {
    // Condição de parada da recursão: se a sala não existe, não há o que liberar.
    if (sala == NULL) {
        return;
    }

    // Libera primeiro os filhos da esquerda.
    liberarMapa(sala->esquerda);
    
    // Depois libera os filhos da direita.
    liberarMapa(sala->direita);
    
    // Por último, libera a própria sala (o nó pai).
    // printf("Liberando a sala: %s\n", sala->nome); // (Linha para depuração)
    free(sala);
}

