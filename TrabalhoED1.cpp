/*Trabalho de Estrutura de Dados 

by Cristiano Pirolli

dia 21/08/2024 ####*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct livro {
    char nome[30];
    struct livro *prox;
};


struct livro *aloca() {
    struct livro *novo_livro = (struct livro *)malloc(sizeof(struct livro));
    if (novo_livro == NULL) {
        perror("FALHA AO ALOCAR MEMORIA");
        exit(EXIT_FAILURE);
    }
    return novo_livro;
}


void addItem(struct livro **cabeca) {
    struct livro *aux, *novo;

    
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    
    novo = aloca();
    printf("DIGITE O NOME DO LIVRO: ");
    fgets(novo->nome, sizeof(novo->nome), stdin);
    novo->nome[strcspn(novo->nome, "\n")] = '\0'; 
    novo->prox = NULL;

    
    if (*cabeca == NULL) {
        *cabeca = novo;
    } else {
    
        aux = *cabeca;
        while (aux->prox != NULL) {
            aux = aux->prox;
        }
        aux->prox = novo;
    }

    
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    printf("LIVRO ADICIONADO COM SUCESSO!\n");
    printf("\nPressione Enter para continuar...");
    getchar(); 
}


void excluirItem(struct livro **cabeca) {
    struct livro *atual = *cabeca;
    struct livro *anterior = NULL;
    char nome[30];


    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    if (atual == NULL) {
        printf("A LISTA ESTA VAZIA.\n");
        printf("\nPressione Enter para continuar...");
        getchar();
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
        
        printf("LIVRO NAO ENCONTRADO.\n");
    } else {
        if (anterior == NULL) {
        
            *cabeca = atual->prox;
        } else {
        
            anterior->prox = atual->prox;
        }
        free(atual);
        printf("LIVRO EXCLUIDO COM SUCESSO!\n");
    }

    printf("\nPressione Enter para continuar...");
    getchar(); 
}


void exibirLivros(struct livro *cabeca) {
    struct livro *aux = cabeca;


    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    printf("LIVROS NO ACERVO\n\n");
    while (aux != NULL) {
        printf("%s\n", aux->nome);
        aux = aux->prox;
    }
    printf("\nPressione Enter para continuar...");
    getchar(); 
}


void pesquisarLivro(struct livro *cabeca) {
    struct livro *aux = cabeca;
    char nome[30];


    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    if (aux == NULL) {
        printf("A LISTA ESTA VAZIA.\n");
        printf("\nPressione Enter para continuar...");
        getchar();
        return;
    }

    printf("DIGITE O NOME DO LIVRO A SER PESQUISADO: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0'; 

    while (aux != NULL) {
        if (strcmp(aux->nome, nome) == 0) {
            printf("LIVRO ENCONTRADO: %s\n", aux->nome);
            printf("\nPressione Enter para continuar...");
            getchar();
            return;
        }
        aux = aux->prox;
    }

    printf("LIVRO NAO ENCONTRADO.\n");
    printf("\nPressione Enter para continuar...");
    getchar();
}


void contarLivros(struct livro *cabeca) {
    struct livro *aux = cabeca;
    int count = 0;

    while (aux != NULL) {
        count++;
        aux = aux->prox;
    }

    printf("TOTAL DE LIVROS NO ACERVO: %d\n", count);
    printf("\nPressione Enter para continuar...");
    getchar();
}


void inserirEmPosicao(struct livro **cabeca, int pos) {
    struct livro *novo, *aux;
    int i;


    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif


    novo = aloca();
    printf("DIGITE O NOME DO LIVRO: ");
    fgets(novo->nome, sizeof(novo->nome), stdin);
    novo->nome[strcspn(novo->nome, "\n")] = '\0'; 
    novo->prox = NULL;

    if (pos == 0) {
        novo->prox = *cabeca;
        *cabeca = novo;
        return;
    }

    aux = *cabeca;
    for (i = 0; i < pos - 1 && aux != NULL; i++) {
        aux = aux->prox;
    }

    if (aux == NULL) {
        printf("POSICAO INVALIDA.\n");
        free(novo);
    } else {
        novo->prox = aux->prox;
        aux->prox = novo;
    }

    printf("LIVRO INSERIDO NA POSICAO %d COM SUCESSO!\n", pos);
    printf("\nPressione Enter para continuar...");
    getchar();
}


void ordenarLivros(struct livro **cabeca) {
    struct livro *i, *j;
    char temp[30];


    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    if (*cabeca == NULL) {
        printf("A LISTA ESTA VAZIA.\n");
        printf("\nPressione Enter para continuar...");
        getchar();
        return;
    }

    for (i = *cabeca; i != NULL; i = i->prox) {
        for (j = i->prox; j != NULL; j = j->prox) {
            if (strcmp(i->nome, j->nome) > 0) {
                
                strcpy(temp, i->nome);
                strcpy(i->nome, j->nome);
                strcpy(j->nome, temp);
            }
        }
    }

    printf("LISTA ORDENADA COM SUCESSO!\n");
    printf("\nPressione Enter para continuar...");
    getchar();
}


void liberarLista(struct livro *cabeca) {
    struct livro *atual = cabeca;
    struct livro *temp;

    while (atual != NULL) {
        temp = atual;
        atual = atual->prox;
        free(temp);
    }
}

int main() {
    struct livro *acervo = NULL; 
    int opcao;

    while (1) {
        
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        printf("\n-------------------------");
        printf("\n|      MENU             |\n");
        printf("|                       |\n");
        printf("| 1. ADICIONAR LIVRO    |\n");
        printf("| 2. EXIBIR LIVROS      |\n");
        printf("| 3. EXCLUIR LIVRO      |\n");
        printf("| 4. PESQUISAR LIVRO    |\n");
        printf("| 5. CONTAR LIVROS      |\n");
        printf("| 6. INSERIR EM POSICAO |\n");
        printf("| 7. ORDENAR LIVROS     |\n");
        printf("| 8. SAIR               |\n");
        printf("|                       |\n");
        printf("| ESCOLHA UMA OPCAO     |\n");
        printf("-------------------------\n");
        
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
                liberarLista(acervo);
                printf("SAINDO...\n");
                exit(EXIT_SUCCESS);
            default:
                
                #ifdef _WIN32
                    system("cls");
                #else
                    system("clear");
                #endif
                printf("OPCAO INVALIDA, TENTE NOVAMENTE.\n");
                printf("\nPressione Enter para continuar...");
                getchar(); 
        }
    }

    return 0;
}

