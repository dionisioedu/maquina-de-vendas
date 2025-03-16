#include <stdio.h>
#include <stdlib.h>

#ifdef WINDOWS
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

typedef struct {
    char nome[20]; //20 bytes
    float preco; //4 bytes
    int quantidade; //4 bytes
} Produto;

void aguardaUsuario();
void exibirMenu(Produto* itens[], int tamanho, float saldo);
void inserirDinheiro(float *saldo);
void comprar(Produto* produto, float* saldo);

int main() {
    Produto itens[] = {
        { "Refrigerante", 6.0, 10 },
        { "Chocolate", 3.0, 20 },
        { "Salgadinho", 5.0, 10 }
    };

    const int TOTAL_PRODUTOS = sizeof(itens) / sizeof(Produto);

    Produto *maquina[TOTAL_PRODUTOS];
    for (int i = 0; i < TOTAL_PRODUTOS; i++) {
        maquina[i] = &itens[i];
    }

    float saldo = 0.0;

    int opcao = -1;
    while (opcao != 0) {
        inserirDinheiro(&saldo);

        exibirMenu(maquina, TOTAL_PRODUTOS, saldo);

        printf("Escolha o número do item ou 0 (zero) para sair: ");
        scanf("%d", &opcao);

        if (opcao < 1 || opcao > TOTAL_PRODUTOS) {
            printf("Opção inválida! Tente novamente!\n");
            aguardaUsuario();
            continue;
        } else {
            comprar(maquina[opcao - 1], &saldo);
        }
    }

    printf("Programa encerrado!\n");

    return 0;
}

void aguardaUsuario() {
    getchar();
    getchar();
}

void exibirMenu(Produto* itens[], int tamanho, float saldo) {
    system(CLEAR);

    printf("=== Máquina de Vendas ===\n");
    printf("Saldo atual: R$%.2f\n", saldo);

    for (int i = 0; i < tamanho; i++) {
        printf("%d. %s\t- R$%.2f (Estoque: %d)\n",
            (i + 1), itens[i]->nome, itens[i]->preco, itens[i]->quantidade);
    }

    printf("\n0. Sair\n");
}

void inserirDinheiro(float *saldo) {
    float notas_disponiveis[] = { 2.0f, 5.0f, 10.0f, 20.0f, 50.0f, 100.0f };
    int quantidade_notas = sizeof(notas_disponiveis) / sizeof(float);

    while (1) {
        system(CLEAR);
        printf("\nInsira uma nota:\n");
        for (int i = 0; i < quantidade_notas; i++) {
            printf("%d. %.2f\n", i + 1, notas_disponiveis[i]);
        }

        int escolha;
        scanf("%d", &escolha);
        if (escolha == 0) {
            return;
        } else if (escolha < 1 || escolha > quantidade_notas) {
            printf("Escolha inválida! Tente novamente!\n");
            aguardaUsuario();
        } else {
            *saldo += notas_disponiveis[escolha - 1];
            break;
        }
    }
}

void comprar(Produto* produto, float* saldo) {
    produto->quantidade--;
    *saldo -= produto->preco;
}
