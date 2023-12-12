#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#ifdef PRODUCAO_H
//#define PRODUCAO-H 
//#include "producao.h"

typedef struct data{
    int dia;
    int mes;
    int ano;
} Data;

typedef struct fardo{
    char cultivar[20];
    char tipoDeFeno;
    int diametro;
} Fardo;


typedef struct producao{
    int codigo;
    Data dataProducao;
    Fardo tipoDeFardo;
    int qtDeFardo;
    float duracao;
    struct producao *proximo;
} Producao;






// função incluir Produção

Producao* incluirProducao(Producao* list) {
    Producao* novo = (Producao*)malloc(sizeof(Producao));


    printf("Digite o código da producao: ");
    scanf("%d", &novo->codigo);


    Producao* atual = list;
    while (atual != NULL) {
        if (atual->codigo == novo->codigo) {
            printf("O código de produção já existe. Não é possível adicionar.\n");
            free(novo);
            return list;
        }
        atual = atual->proximo;
    }

    printf("Digite a data da producao (dia mes ano): ");
    scanf("%d %d %d", &novo->dataProducao.dia, &novo->dataProducao.mes, &novo->dataProducao.ano);

    printf("Digite o tipo de feno: ");
    scanf("%s", &novo->tipoDeFardo.tipoDeFeno);
    
    printf("Digite o numero de fardo: ");
    scanf("%s",novo->qtDeFardo);

    novo->proximo = list;  // Adicionar novo nó no início da lista
    return novo;  // Retorna o novo início da lista
}

// funçao para Consultar



int main(){

    Producao* lista = NULL;
    
    int escolha;
    

    do {
        // Exibir menu
        printf("\nMenu:\n");
        printf("1. Incluir Produção\n");
        printf("2. Consultar\n");
        printf("3. Alterar\n");
        printf("4. Excluir\n");
        printf("5. Listar todos\n");
        printf("6. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                // Incluir Produção
                lista = incluirProducao(lista);
                break;

            case 2:
                // Consultar
                printf("1. Consultar por data\n");
                printf("2. Consultar por cultivar\n");
                printf("Escolha uma opção: ");
                scanf("%d", &escolha);

                break;

            case 3:
                // Alterar
               
                break;

            case 4:
                // Excluir
                
                break;

            case 5:
                // Listar todos
                
                break;

            case 6:
                // Sair
                
                break;

            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (escolha != 6);

    return 0;
}

    


