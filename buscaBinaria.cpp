#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int *chaves;
    int tamanho;
} ListaChaves;

ListaChaves* criarLista(int tamanho) {
    ListaChaves *lista = (ListaChaves *)malloc(sizeof(ListaChaves));
    lista->chaves = (int *)malloc(tamanho * sizeof(int));
    lista->tamanho = tamanho;
    return lista;
}

void liberarLista(ListaChaves *lista) {
    free(lista->chaves);
    free(lista);
}

int* buscaBinaria(ListaChaves *lista, int chave, int *count, int *iteracoes, int *valores) {
    int inicio = 0, fim = lista->tamanho - 1;
    int *posicoes = (int *)malloc(lista->tamanho * sizeof(int));
    *count = 0;
    *iteracoes = 0; 

    while (inicio <= fim) {
        (*iteracoes)++; 
        int meio = inicio + (fim - inicio) / 2;
        
        valores[*iteracoes - 1] = lista->chaves[meio];

        if (lista->chaves[meio] == chave) {
            posicoes[(*count)++] = meio;
            for (int i = meio - 1; i >= 0 && lista->chaves[i] == chave; i--) {
                posicoes[(*count)++] = i;
            }
            for (int i = meio + 1; i < lista->tamanho && lista->chaves[i] == chave; i++) {
                posicoes[(*count)++] = i;
            }
            break;
        } else if (lista->chaves[meio] < chave) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    if (*count == 0) {
        free(posicoes);
        return NULL;
    }

    return posicoes;
}

void ordenarLista(ListaChaves *lista) {
    for (int i = 0; i < lista->tamanho - 1; i++) {
        for (int j = 0; j < lista->tamanho - 1 - i; j++) {
            if (lista->chaves[j] > lista->chaves[j + 1]) {
                int temp = lista->chaves[j];
                lista->chaves[j] = lista->chaves[j + 1];
                lista->chaves[j + 1] = temp;
            }
        }
    }
}

void exibirLista(ListaChaves *lista) {
    printf("Chaves: ");
    for (int i = 0; i < lista->tamanho; i++) {
        printf("%d ", lista->chaves[i]);
    }
    printf("\n");
}

int contarOcorrencias(ListaChaves *lista, int chave) {
    int count = 0;
    for (int i = 0; i < lista->tamanho; i++) {
        if (lista->chaves[i] == chave) {
            count++;
        }
    }
    return count;
}

void exibirEstatisticas(ListaChaves *lista) {
    int menor = lista->chaves[0];
    int maior = lista->chaves[0];

    for (int i = 0; i < lista->tamanho; i++) {
        if (lista->chaves[i] < menor) menor = lista->chaves[i];
        if (lista->chaves[i] > maior) maior = lista->chaves[i];
    }

    printf("\nMenor chave: %d\n", menor);
    printf("Maior chave: %d\n", maior);
}

int main() {
    int n, chave, intervalo_min, intervalo_max;
    srand(time(NULL));

    printf("Digite o numero de chaves: ");
    scanf("%d", &n);
    printf("Digite o intervalo minimo e maximo para as chaves: ");
    scanf("%d %d", &intervalo_min, &intervalo_max);

    ListaChaves *lista = criarLista(n);

    for (int i = 0; i < n; i++) {
        lista->chaves[i] = intervalo_min + rand() % (intervalo_max - intervalo_min + 1);
    }

    ordenarLista(lista);
    exibirLista(lista);

    printf("Digite a chave a ser buscada: ");
    scanf("%d", &chave);

    int count, iteracoes;
    int *posicoes = (int *)malloc(n * sizeof(int)); 
    int *valores = (int *)malloc(n * sizeof(int)); 

    posicoes = buscaBinaria(lista, chave, &count, &iteracoes, valores); 

    printf("\nIteracoes na busca: %d\n", iteracoes);
    printf("Valores verificados: ");
    for (int i = 0; i < iteracoes; i++) {
        printf("%d ", valores[i]);
    }
    printf("\n");

    if (posicoes) {
        printf("A chave %d foi encontrada nas posicoes: ", chave);
        for (int i = 0; i < count; i++) {
            printf("%d ", posicoes[i]);
        }
        printf("\n");
        printf("Ocorrencias: %d\n", contarOcorrencias(lista, chave));
        free(posicoes);
    } else {
        printf("A chave %d nao foi encontrada.\n", chave);
    }

    exibirEstatisticas(lista);
    free(valores); 
    liberarLista(lista);
    return 0;
}

