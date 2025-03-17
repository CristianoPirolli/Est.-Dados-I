#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct livro {
    char nome[30];
    int ano_publicacao;
    int classificacao;
    struct livro *prox;
    struct livro *prev;
};

void limparTela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

struct livro *aloca() {
    struct livro *novo_livro = (struct livro *)malloc(sizeof(struct livro));
    if (novo_livro == NULL) {
        perror("FALHA AO ALOCAR MEMORIA");
        exit(EXIT_FAILURE);
    }
    return novo_livro;
}

void exibirMensagem(char *mensagem) {
    printf("%s\n", mensagem);
    printf("\nPressione Enter para continuar...");
    getchar();
}

void addItem(struct livro **cabeca) {
    struct livro *novo, *aux;

    limparTela();

    novo = aloca();
    printf("DIGITE O NOME DO LIVRO: ");
    fgets(novo->nome, sizeof(novo->nome), stdin);
    novo->nome[strcspn(novo->nome, "\n")] = '\0'; 

    printf("DIGITE O ANO DE PUBLICACAO: ");
    scanf("%d", &novo->ano_publicacao);
    getchar();  

    printf("DIGITE A CLASSIFICACAO (1 A 5 ESTRELAS): ");
    scanf("%d", &novo->classificacao);
    getchar();  

    if (novo->classificacao < 1 || novo->classificacao > 5) {
        printf("CLASSIFICACAO INVALIDA. DEFININDO COMO 1 ESTRELA.\n");
        novo->classificacao = 1;
    }

    novo->prox = NULL;
    novo->prev = NULL;

    if (*cabeca == NULL) {
        *cabeca = novo;
    } else {
        aux = *cabeca;
        while (aux->prox != NULL) {
            aux = aux->prox;
        }
        aux->prox = novo;
        novo->prev = aux;
    }

    limparTela();
    exibirMensagem("LIVRO ADICIONADO COM SUCESSO!");
}

void excluirItem(struct livro **cabeca) {
    struct livro *atual = *cabeca;
    struct livro *anterior = NULL;
    char nome[30];

    limparTela();

    if (atual == NULL) {
        exibirMensagem("A LISTA ESTA VAZIA.");
        return;
    }

    printf("DIGITE O NOME DO LIVRO A SER EXCLUIDO: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0'; 

    while (atual != NULL && strcmp(atual->nome, nome) != 0) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) {
        exibirMensagem("LIVRO NAO ENCONTRADO.");
    } else {
        if (anterior == NULL) {
            *cabeca = atual->prox;
            if (*cabeca != NULL) {
                (*cabeca)->prev = NULL;
            }
        } else {
            anterior->prox = atual->prox;
            if (atual->prox != NULL) {
                atual->prox->prev = anterior;
            }
        }
        free(atual);
        exibirMensagem("LIVRO EXCLUIDO COM SUCESSO!");
    }
}

void exibirLivros(struct livro *cabeca) {
    struct livro *aux = cabeca;
    int pos = 0;

    limparTela();

    if (aux == NULL) {
        exibirMensagem("A LISTA ESTA VAZIA.");
        return;
    }

    printf("LIVROS NO ACERVO\n\n");
    printf("+------+-------------------------------+------+-------+\n");
    printf("| INDEX| NOME                          | ANO  | CLASS |\n");
    printf("+------+-------------------------------+------+-------+\n");

    while (aux != NULL) {
        printf("| %4d | %-29s | %4d | %5d |\n", pos, aux->nome, aux->ano_publicacao, aux->classificacao);
        aux = aux->prox;
        pos++;
    }

    printf("+------+-------------------------------+------+-------+\n");
    exibirMensagem("");
}

void exibirLivrosReverso(struct livro *cabeca) {
    struct livro *aux = cabeca;
    int pos = 0;

    limparTela();

    if (aux == NULL) {
        exibirMensagem("A LISTA ESTA VAZIA.");
        return;
    }

    while (aux->prox != NULL) {
        aux = aux->prox;
    }

    printf("LIVROS NO ACERVO (REVERSO)\n\n");
    printf("+------+-------------------------------+------+-------+\n");
    printf("| INDEX| NOME                          | ANO  | CLASS |\n");
    printf("+------+-------------------------------+------+-------+\n");

    while (aux != NULL) {
        printf("| %4d | %-29s | %4d | %5d |\n", pos, aux->nome, aux->ano_publicacao, aux->classificacao);
        aux = aux->prev;
        pos++;
    }

    printf("+------+-------------------------------+------+-------+\n");
    exibirMensagem("");
}

void pesquisarLivro(struct livro *cabeca) {
    struct livro *aux = cabeca;
    char nome[30];

    limparTela();

    if (aux == NULL) {
        exibirMensagem("A LISTA ESTA VAZIA.");
        return;
    }

    printf("DIGITE O NOME DO LIVRO A SER PESQUISADO: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0'; 

    while (aux != NULL) {
        if (strcmp(aux->nome, nome) == 0) {
            printf("LIVRO ENCONTRADO: NOME: %s, ANO: %d, CLASSIFICACAO: %d\n", aux->nome, aux->ano_publicacao, aux->classificacao);
            exibirMensagem("");
            return;
        }
        aux = aux->prox;
    }

    exibirMensagem("LIVRO NAO ENCONTRADO.");
}

void contarLivros(struct livro *cabeca) {
    struct livro *aux = cabeca;
    int count = 0;

    while (aux != NULL) {
        count++;
        aux = aux->prox;
    }

    printf("TOTAL DE LIVROS NO ACERVO: %d\n", count);
    exibirMensagem("");
}

void inserirEmPosicao(struct livro **cabeca, int pos) {
    struct livro *novo, *aux;
    int i;

    limparTela();

    novo = aloca();
    printf("DIGITE O NOME DO LIVRO: ");
    fgets(novo->nome, sizeof(novo->nome), stdin);
    novo->nome[strcspn(novo->nome, "\n")] = '\0'; 

    printf("DIGITE O ANO DE PUBLICACAO: ");
    scanf("%d", &novo->ano_publicacao);
    getchar();  

    printf("DIGITE A CLASSIFICACAO (1 A 5 ESTRELAS): ");
    scanf("%d", &novo->classificacao);
    getchar();  

    if (novo->classificacao < 1 || novo->classificacao > 5) {
        printf("CLASSIFICACAO INVALIDA. DEFININDO COMO 1 ESTRELA.\n");
        novo->classificacao = 1;
    }

    novo->prox = NULL;
    novo->prev = NULL;

    if (pos == 0) {
        novo->prox = *cabeca;
        if (*cabeca != NULL) {
            (*cabeca)->prev = novo;
        }
        *cabeca = novo;
        exibirMensagem("LIVRO INSERIDO NA POSICAO 0 COM SUCESSO!");
        return;
    }

    aux = *cabeca;
    for (i = 0; i < pos - 1 && aux != NULL; i++) {
        aux = aux->prox;
    }

    if (aux == NULL) {
        exibirMensagem("POSICAO INVALIDA.");
        free(novo);
    } else {
        novo->prox = aux->prox;
        novo->prev = aux;
        if (aux->prox != NULL) {
            aux->prox->prev = novo;
        }
        aux->prox = novo;
        exibirMensagem("LIVRO INSERIDO NA POSICAO COM SUCESSO!");
    }
}

void ordenarLivrosPorNome(struct livro **cabeca) {
    struct livro *i, *j;
    char temp_nome[30];
    int temp_ano, temp_classificacao;

    if (*cabeca == NULL) return;

    for (i = *cabeca; i->prox != NULL; i = i->prox) {
        for (j = i->prox; j != NULL; j = j->prox) {
            if (strcmp(i->nome, j->nome) > 0) {
                strcpy(temp_nome, i->nome);
                strcpy(i->nome, j->nome);
                strcpy(j->nome, temp_nome);

                temp_ano = i->ano_publicacao;
                i->ano_publicacao = j->ano_publicacao;
                j->ano_publicacao = temp_ano;

                temp_classificacao = i->classificacao;
                i->classificacao = j->classificacao;
                j->classificacao = temp_classificacao;
            }
        }
    }
}

void ordenarLivros(struct livro **cabeca) {
    ordenarLivrosPorNome(cabeca);
    exibirMensagem("LIVROS ORDENADOS POR NOME COM SUCESSO!");
}

void exibirLivrosPorClassificacao(struct livro *cabeca) {
    struct livro *aux = cabeca;
    int classificacao, pos = 0;

    limparTela();

    if (aux == NULL) {
        exibirMensagem("A LISTA ESTA VAZIA.");
        return;
    }

    printf("DIGITE A CLASSIFICACAO PARA FILTRAR (1 A 5 ESTRELAS): ");
    scanf("%d", &classificacao);
    getchar();  

    if (classificacao < 1 || classificacao > 5) {
        exibirMensagem("CLASSIFICACAO INVALIDA.");
        return;
    }

    printf("LIVROS COM CLASSIFICACAO %d ESTRELAS\n\n", classificacao);
    printf("+------+-------------------------------+------+-------+\n");
    printf("| INDEX| NOME                          | ANO  | CLASS |\n");
    printf("+------+-------------------------------+------+-------+\n");

    while (aux != NULL) {
        if (aux->classificacao == classificacao) {
            printf("| %4d | %-29s | %4d | %5d |\n", pos, aux->nome, aux->ano_publicacao, aux->classificacao);
        }
        aux = aux->prox;
        pos++;
    }

    printf("+------+-------------------------------+------+-------+\n");
    exibirMensagem("");
}

void liberarLista(struct livro *cabeca) {
    struct livro *aux;
    while (cabeca != NULL) {
        aux = cabeca;
        cabeca = cabeca->prox;
        free(aux);
    }
}

int main() {
    struct livro *acervo = NULL; 
    int opcao;

    while (1) {
        limparTela();

        printf("\n-------------------------------");
        printf("\n|          MENU               |\n");
        printf("|                             |\n");
        printf("| 1. ADICIONAR LIVRO          |\n");
        printf("| 2. EXIBIR LIVROS            |\n");
        printf("| 3. EXCLUIR LIVRO            |\n");
        printf("| 4. PESQUISAR LIVRO          |\n");
        printf("| 5. CONTAR LIVROS            |\n");
        printf("| 6. INSERIR EM POSICAO       |\n");
        printf("| 7. ORDENAR LIVROS           |\n");
        printf("| 8. EXIBIR REVERSO           |\n");
        printf("| 9. EXIBIR POR CLASSIFICACAO |\n");
        printf("| 10. SAIR                    |\n");
        printf("|                             |\n");
        printf("| ESCOLHA UMA OPCAO           |\n");
        printf("-------------------------------\n");

        scanf("%d", &opcao);
        getchar();  

        switch (opcao) {
            case 1:
                addItem(&acervo);
                break;
            case 2:
                exibirLivros(acervo);
                break;
            case 3:
                excluirItem(&acervo);
                break;
            case 4:
                pesquisarLivro(acervo);
                break;
            case 5:
                contarLivros(acervo);
                break;
            case 6: {
                int pos;
                printf("DIGITE A POSICAO PARA INSERIR O LIVRO: ");
                scanf("%d", &pos);
                getchar(); 
                inserirEmPosicao(&acervo, pos);
                break;
            }
            case 7:
                ordenarLivros(&acervo);
                break;
            case 8:
                exibirLivrosReverso(acervo);
                break;
            case 9:
                exibirLivrosPorClassificacao(acervo);
                break;
            case 10:
                liberarLista(acervo);
                printf("SAINDO...\n");
                exit(EXIT_SUCCESS);
            default:
                limparTela();
                exibirMensagem("OPCAO INVALIDA, TENTE NOVAMENTE.");
        }
    }

    return 0;
}

