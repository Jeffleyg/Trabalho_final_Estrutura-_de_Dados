/* Jeffley Garçon & Nycollas Widney*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING 20

// Tipos de Feno
#define TIPO_A 'A'
#define TIPO_B 'B'
#define TIPO_C 'C'

typedef struct data {
    int dia;
    int mes;
    int ano;
} Data;

typedef struct fardo {
    char cultivar[MAX_STRING];
    char tipoDeFeno;
    float diametro;
    float altura;
} Fardo;

typedef struct producao {
    int codigo;
    Data dataProducao;
    Fardo tipoDeFardo;
    int qtDeFardo;
    float duracao;
    struct producao* proximo;
    struct producao* anterior;
} Producao;

typedef struct tipoFenoLista {
    Producao* inicio;
    Producao* fim;
} TipoFenoLista;

// TAD
TipoFenoLista inicializarTipoFenoLista();
void adicionarProducaoAoTipoFenoLista(const Producao* producao, TipoFenoLista* lista);
Producao* incluirProducao(Producao* list);
void consultarPorData(Producao* list, int dia, int mes, int ano);
void alterarProducao(Producao* list, int codigo);
Producao* excluirProducao(Producao* list, int codigo);
void listarTodos(Producao* list);
void listarAgrupadoPorTipoFeno(const Producao* list);
Producao* excluirProducaoPoTipoFeno(Producao* list, char tipoDeFeno);

TipoFenoLista inicializarTipoFenoLista() {
    TipoFenoLista lista;
    lista.inicio = NULL;
    lista.fim = NULL;
    return lista;
}

 
void adicionarProducaoAoTipoFenoLista(const Producao* producao, TipoFenoLista* lista) {
    Producao* novoNo = (Producao*)malloc(sizeof(Producao));
    if (novoNo == NULL) {
        fprintf(stderr, "Erro na alocação de memória para adicionar produção.\n");
        exit(EXIT_FAILURE);
    }

    
    novoNo->tipoDeFardo = producao->tipoDeFardo;
    strcpy(novoNo->tipoDeFardo.cultivar, producao->tipoDeFardo.cultivar);
    novoNo->qtDeFardo = producao->qtDeFardo;
    novoNo->codigo = producao->codigo;
    novoNo->dataProducao = producao->dataProducao;
    novoNo->duracao = producao->duracao;

    // Configuração dos ponteiros .... ...
    novoNo->anterior = lista->fim;
    novoNo->proximo = NULL;

    if (lista->inicio == NULL) {
        lista->inicio = novoNo;
        lista->fim = novoNo;
    } else {
        lista->fim->proximo = novoNo;
        lista->fim = novoNo;
    }
}

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
    scanf(" %c", &novo->tipoDeFardo.tipoDeFeno);

    printf("Digite o numero de fardo: ");
    scanf("%d", &novo->qtDeFardo);

    do {
        printf("Digite o diâmetro do fardo (entre 80 cm e 160 cm): ");
        scanf("%f", &novo->tipoDeFardo.diametro);

        if (novo->tipoDeFardo.diametro < 80 || novo->tipoDeFardo.diametro > 160) {
            printf("Erro: Diâmetro fora da faixa aceitável. Tente novamente.\n");
        }
    } while (novo->tipoDeFardo.diametro < 80 || novo->tipoDeFardo.diametro > 160);

    novo->tipoDeFardo.altura = 150.0;

    printf("Digite a duração da produção: ");
    scanf("%f", &novo->duracao);

    printf("Produção registrada com sucesso!!!\n\n");

    novo->proximo = list;
    novo->anterior = NULL; // O anterior do novo nó é NULL, pois é o novo início
    if (list != NULL) {
        list->anterior = novo; // Atualiza o anterior do nó antigo para apontar para o novo nó
    }
    return novo;
}

void consultarPorData(Producao* list, int dia, int mes, int ano) {
    Producao* atual = list;
    Producao* ultimo = NULL;

    while (atual != NULL) {
        ultimo = atual; // Guarda o último nó que a gente visita para percorrer a lista de trás para frente
        atual = atual->proximo;

        if (ultimo->dataProducao.dia == dia && ultimo->dataProducao.mes == mes && ultimo->dataProducao.ano == ano) {
            printf("Código: %d\n", ultimo->codigo);
            printf("Data: %d/%d/%d\n", ultimo->dataProducao.dia, ultimo->dataProducao.mes, ultimo->dataProducao.ano);
            printf("Tipo de Feno: %c\n", ultimo->tipoDeFardo.tipoDeFeno);
            printf("Quantidade de Fardo: %d\n", ultimo->qtDeFardo);
            printf("Diâmetro do Fardo: %.2f cm\n", ultimo->tipoDeFardo.diametro);
            printf("Altura do Fardo: %.2f cm\n", ultimo->tipoDeFardo.altura);
            printf("Duracao: %.2f\n", ultimo->duracao);
            return;
        }
    }

    // Percorre a lista da última posição até a primeira
    while (ultimo != NULL) {
        if (ultimo->dataProducao.dia == dia && ultimo->dataProducao.mes == mes && ultimo->dataProducao.ano == ano) {
            printf("Código: %d\n", ultimo->codigo);
            printf("Data: %d/%d/%d\n", ultimo->dataProducao.dia, ultimo->dataProducao.mes, ultimo->dataProducao.ano);
            printf("Tipo de Feno: %c\n", ultimo->tipoDeFardo.tipoDeFeno);
            printf("Quantidade de Fardo: %d\n", ultimo->qtDeFardo);
            printf("Diâmetro do Fardo: %.2f cm\n", ultimo->tipoDeFardo.diametro);
            printf("Altura do Fardo: %.2f cm\n", ultimo->tipoDeFardo.altura);
            printf("Duracao: %.2f\n", ultimo->duracao);
            return;
        }
        ultimo = ultimo->anterior;
    }

    printf("ERRO: Produção não encontrada para a data especificada.\n\n\n");
}



void alterarProducao(Producao* list, int codigo) {
    Producao* atual = list;

    while (atual != NULL) {
        if (atual->codigo == codigo) {
            printf("**********************\n");
            printf("Produção encontrada. Insira os novos dados:\n");

            int novoCodigo;
            printf("Digite o novo código da producao: ");
            scanf("%d", &novoCodigo);

            // Verifica se o novo código já existe na lista
            Producao* existente = list;
            while (existente != NULL) {
                if (existente != atual && existente->codigo == novoCodigo) {
                    printf("O código de produção já existe. Não é possível alterar.\n");
                    return;
                }
                existente = existente->proximo;
            }

            atual->codigo = novoCodigo;
            printf("Digite a nova data da producao (dia mes ano): ");
            scanf("%d %d %d", &atual->dataProducao.dia, &atual->dataProducao.mes, &atual->dataProducao.ano);

            printf("Digite o novo tipo de feno: ");
            scanf(" %c", &atual->tipoDeFardo.tipoDeFeno);

            printf("Digite a nova quantidade de fardo: ");
            scanf("%d", &atual->qtDeFardo);

            // Configuração do equipamento
            do {
                printf("Digite o novo diâmetro do fardo (entre 80 cm e 160 cm): ");
                scanf("%f", &atual->tipoDeFardo.diametro);

                // Validar o diâmetro
                if (atual->tipoDeFardo.diametro < 80 || atual->tipoDeFardo.diametro > 160) {
                    printf("Erro: Diâmetro fora da faixa aceitável. Tente novamente.\n");
                }
            } while (atual->tipoDeFardo.diametro < 80 || atual->tipoDeFardo.diametro > 160);

            // Altura fixa
            atual->tipoDeFardo.altura = 150.0;

            printf("Digite a nova duracao: ");
            scanf("%f", &atual->duracao);

            printf("Produção alterada com sucesso.\n");
            return;
        }

        atual = atual->proximo;
    }

    printf("\nProdução não encontrada para o código especificado.\n");
}


Producao* excluirProducao(Producao* list, int codigo) {
    Producao* atual = list;

    while (atual != NULL) {
        if (atual->codigo == codigo) {
            if (atual->proximo != NULL) {
                atual->proximo->anterior = atual->anterior;
            }

            if (atual->anterior != NULL) {
                atual->anterior->proximo = atual->proximo;
            } else {
                list = atual->proximo; // Se o nó a ser excluído for o primeiro da lista
            }

            free(atual);
            printf("\nItem excluído com sucesso!!!\n");
            return list;
        }

        atual = atual->proximo;
    }

    printf("Produção não encontrada para o código especificado.\n");
    return list;
}

// ...



// ...
Producao* excluirProducaoPorTipoFeno(Producao* list, char tipoDeFeno) {
    Producao* atual = list;
    Producao* proximo = NULL;
    Producao* anterior = NULL;

    while (atual != NULL) {
        proximo = atual->proximo;

        if (atual->tipoDeFardo.tipoDeFeno == tipoDeFeno) {
            if (anterior != NULL) {
                anterior->proximo = proximo;
            } else {
                list = proximo; // Se o nó a ser excluído for o primeiro da lista
            }

            if (proximo != NULL) {
                proximo->anterior = anterior;
            }

            free(atual);
            printf("\nItem excluído com sucesso!!!\n");
        } else {
            anterior = atual; // Move o ponteiro 'anterior' apenas se o nó não for excluído
        }

        atual = proximo;
    }

    if (list == NULL) {
        printf("A lista está vazia.\n");
    }

    return list;
}



void listarTodos(Producao* list) {
    if (list == NULL) {
        printf("A lista está vazia.\n");
        return;
    }

    Producao* atual = list;

    while (atual != NULL) {
        printf("**************************************\n");
        printf("Código: %d\n", atual->codigo);
        printf("Data: %d/%d/%d\n", atual->dataProducao.dia, atual->dataProducao.mes, atual->dataProducao.ano);
        printf("Tipo de Feno: %c\n", atual->tipoDeFardo.tipoDeFeno);
        printf("Quantidade de Fardo: %d\n", atual->qtDeFardo);
        printf("Diâmetro do Fardo: %.2f cm\n", atual->tipoDeFardo.diametro);
        printf("Altura do Fardo: %.2f cm\n", atual->tipoDeFardo.altura);
        printf("Duracao: %.2f\n\n", atual->duracao);

        atual = atual->proximo;
    }
}


void listarAgrupadoPorTipoFeno(const Producao* list) {

    TipoFenoLista tipoA = inicializarTipoFenoLista();
    TipoFenoLista tipoB = inicializarTipoFenoLista();
    TipoFenoLista tipoC = inicializarTipoFenoLista();

    const Producao* atual = list;

    while (atual != NULL) {
        switch (atual->tipoDeFardo.tipoDeFeno) {
            case TIPO_A:
                adicionarProducaoAoTipoFenoLista(atual, &tipoA);
                break;
            case TIPO_B:
                adicionarProducaoAoTipoFenoLista(atual, &tipoB);
                break;
            case TIPO_C:
                adicionarProducaoAoTipoFenoLista(atual, &tipoC);
                break;
            default:
                printf("Tipo de feno desconhecido.\n");
                break;
        }

        atual = atual->proximo;
    }

    printf("\nProduções Tipo A:\n");
    listarTodos(tipoA.inicio);

    printf("\nProduções Tipo B:\n");
    listarTodos(tipoB.inicio);

    printf("\nProduções Tipo C:\n");
    listarTodos(tipoC.inicio);
}

int main() {
    Producao* lista = NULL;
    int escolha, codigo, dia, mes, ano, verif = 0;
    char tipo;

    do {
        if (verif != 0) break;
        printf("😊 Bem-vindo ao nosso sistema!!!! 😊\n");

        printf("\nMenu:\n");
        printf("1. Incluir Produção\n");
        printf("2. Consultar\n");
        printf("3. Alterar\n");
        printf("4. Excluir\n");
        printf("5. Listar todos\n");
        printf("6. Listar por tipo de feno\n");
        printf("7. Sair\n");
        printf("8. excluir por tipo de feno\n");
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
                printf("Digite a data (dia mes ano): ");
                scanf("%d %d %d", &dia, &mes, &ano);
                consultarPorData(lista, dia, mes, ano);
                break;

            case 3:
                // Alterar
                printf("Digite o código da producao a ser alterada: ");
                scanf("%d", &codigo);
                alterarProducao(lista, codigo);
                break;

            case 4:
                // Excluir
                printf("Digite o código da producao a ser excluída: ");
                scanf("%d", &codigo);
                lista = excluirProducao(lista, codigo);
                break;

            case 5:
                // Listar todos
                listarTodos(lista);
                break;

            case 6:
                // tipo de feno
                listarAgrupadoPorTipoFeno(lista);
                break;
            
            case 7:
                // Sair
                printf("Saindo do programa...\n");

                verif++;
                break;
            case 8:
                printf("Digite o tipo de feno a ser excluído: ");
                getchar(); // Limpar o buffer de entrada
                scanf("%c", &tipo);
                lista = excluirProducaoPorTipoFeno(lista, tipo);
                break;
        }
    } while (escolha != 7);

    // para liberar a memória
    while (lista != NULL) {
        Producao* proximo = lista->proximo;
        free(lista);
        lista = proximo;
    }

    return 0;
}

