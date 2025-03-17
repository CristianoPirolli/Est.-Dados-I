#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TABLE_SIZE 73  // Tamanho da tabela hash
#define FILE_NAME "nomes.txt"

// Estruturas e funções de hash permanecem as mesmas

typedef struct Node {
    char *name;
    struct Node *prev;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    Node *tail;
    int count;
} Bucket;

typedef struct {
    Bucket *buckets;
    int size;
} HashTable;

// Função de hash com o número primo 37
unsigned int hashFunction(char *name) {
    unsigned int hash = 0;
    for (int i = 0; name[i] != '\0'; i++) {
        hash = (hash * 37 + (unsigned char)name[i]) % TABLE_SIZE;  // Usando 37 em vez de 31
    }
    return hash % TABLE_SIZE;
}

// Função para criar um novo nó
Node* createNode(char *name) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->name = strdup(name);
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Função para criar a tabela hash
HashTable* createHashTable(int size) {
    HashTable *table = (HashTable*)malloc(sizeof(HashTable));
    table->size = size;
    table->buckets = (Bucket*)calloc(size, sizeof(Bucket));
    return table;
}

// Função para inserir um nome na tabela hash
void insert(HashTable *table, char *name) {
    unsigned int index = hashFunction(name);
    Node *newNode = createNode(name);
    
    if (table->buckets[index].head == NULL) {
        table->buckets[index].head = newNode;
        table->buckets[index].tail = newNode;
    } else {
        newNode->prev = table->buckets[index].tail;
        table->buckets[index].tail->next = newNode;
        table->buckets[index].tail = newNode;
    }
    table->buckets[index].count++;
}

// Função para contar o número de elementos em um bucket específico
int count(HashTable *table, char *name) {
    unsigned int index = hashFunction(name);
    return table->buckets[index].count;
}

// Função para carregar os nomes de um arquivo para a tabela hash
void loadNamesFromFile(HashTable *table) {
    FILE *file = fopen(FILE_NAME, "r");
    if (!file) {
        perror("Erro ao abrir o arquivo.");
        return;
    }

    char name[100];
    while (fscanf(file, "%99s", name) == 1) { 
        insert(table, name);
    }
    fclose(file);
}

// Função para liberar a memória da tabela hash
void freeHashTable(HashTable *table) {
    for (int i = 0; i < table->size; i++) {
        Node *current = table->buckets[i].head;
        while (current) {
            Node *temp = current;
            current = current->next;
            free(temp->name);
            free(temp);
        }
    }
    free(table->buckets);
    free(table);
}

// Função para pesquisar um nome na tabela hash
void search(HashTable *table, char *name) {
    unsigned int index = hashFunction(name);
    Node *current = table->buckets[index].head;
    while (current) {
        if (strcmp(current->name, name) == 0) {
            printf("Nome '%s' encontrado no bucket %d.\n", name, index);
            return;
        }
        current = current->next;
    }
    printf("Nome '%s' não encontrado.\n", name);
}

// Função para remover um nome da tabela hash
void removeName(HashTable *table, char *name) {
    unsigned int index = hashFunction(name);
    Node *current = table->buckets[index].head;
    
    while (current) {
        if (strcmp(current->name, name) == 0) {
            if (current->prev) {
                current->prev->next = current->next;
            } else {
                table->buckets[index].head = current->next;
            }
            if (current->next) {
                current->next->prev = current->prev;
            } else {
                table->buckets[index].tail = current->prev;
            }
            free(current->name);
            free(current);
            table->buckets[index].count--;
            printf("Nome '%s' removido com sucesso.\n", name);
            return;
        }
        current = current->next;
    }
    printf("Nome '%s' não encontrado para remoção.\n", name);
}

// Função para exibir a quantidade de elementos e os nomes de um bucket específico
void countElements(HashTable *table, int bucketIndex) {
    if (bucketIndex >= 0 && bucketIndex < table->size) {
        printf("Bucket %d possui %d elementos: ", bucketIndex, table->buckets[bucketIndex].count);
        Node *current = table->buckets[bucketIndex].head;
        if (current == NULL) {
            printf("Nenhum elemento neste bucket.\n");
        } else {
            while (current) {
                printf("%s -> ", current->name);
                current = current->next;
            }
            printf("NULL\n");
        }
    } else {
        printf("Índice do bucket inválido.\n");
    }
}

// Função para exibir todos os buckets e seus nomes
void displayBuckets(HashTable *table) {
    for (int i = 0; i < table->size; i++) {
        printf("Bucket %d (%d elementos): ", i, table->buckets[i].count);
        Node *current = table->buckets[i].head;
        while (current) {
            printf("%s -> ", current->name);
            current = current->next;
        }
        printf("NULL\n");
    }
}

// Função para calcular e exibir as estatísticas dos buckets
void printStats(HashTable *table) {
    int totalElements = 0;
    int maxCount = 0, minCount = __INT_MAX__;
    int maxBucket = -1, minBucket = -1;
    
    // Calcular o total de elementos e encontrar o maior e o menor bucket
    for (int i = 0; i < table->size; i++) {
        totalElements += table->buckets[i].count;
        if (table->buckets[i].count > maxCount) {
            maxCount = table->buckets[i].count;
            maxBucket = i;
        }
        if (table->buckets[i].count < minCount && table->buckets[i].count > 0) {
            minCount = table->buckets[i].count;
            minBucket = i;
        }
    }

    double average = (double)totalElements / table->size;

    // Exibir estatísticas
    printf("\n-----------------------------------------\n");
    printf("|           Estatisticas                |\n");
    printf("-----------------------------------------\n");
    printf("| Total de nomes: %d\n", totalElements);
    printf("| Bucket com mais nomes: Bucket %d com %d nomes\n", maxBucket, maxCount);
    printf("| Bucket com menos nomes: Bucket %d com %d nomes\n", minBucket, minCount);
    printf("| Media de nomes por bucket: %.2f\n", average);

    // Calcular e exibir a porcentagem de diferença do maior e menor bucket em relação à média
    if (maxCount > 0)
        printf("| Maior bucket ficou %.2f%% acima da media.\n", ((maxCount - average) / average) * 100);
    if (minCount > 0)
        printf("| Menor bucket ficou %.2f%% abaixo da media.\n", ((average - minCount) / average) * 100);

    // Exibir a diferença entre o maior e o menor bucket
    printf("| Diferenca entre o maior e o menor bucket: %d\n", maxCount - minCount);
    printf("------------------------------------------------------\n");
}

// Função para exibir o menu e obter a opção do usuário
void displayMenu() {
    printf("------------------------------------------\n");
    printf("|           Menu de Operacoes:           |\n");
    printf("|  1. Pesquisar nome                     |\n");
    printf("|  2. Quantidade de elementos por chave  |\n");
    printf("|  3. Remover um nome                    |\n");
    printf("|  4. Inserir um nome                    |\n");
    printf("|  5. Exibir todos os buckets            |\n");
    printf("|  6. Exibir as estatisticas             |\n");
    printf("|  7. Sair                               |\n");
    printf("|        Escolha uma opcao:              |\n");
    printf("------------------------------------------\n");
}

int main() {
    HashTable *table = createHashTable(TABLE_SIZE);
    loadNamesFromFile(table);
    
    int option;
    char name[100];
    int bucketIndex;

    do {
        displayMenu();
        scanf("%d", &option);

        switch (option) {
            case 1:
                printf("Digite o nome a ser pesquisado: ");
                scanf("%s", name);
                search(table, name);
                break;
            case 2:
                printf("Digite o indice do bucket (0-72): ");
                scanf("%d", &bucketIndex);
                countElements(table, bucketIndex);
                break;
            case 3:
                printf("Digite o nome a ser removido: ");
                scanf("%s", name);
                removeName(table, name);
                break;
            case 4:
                printf("Digite o nome a ser inserido: ");
                scanf("%s", name);
                insert(table, name);
                printf("Nome '%s' inserido com sucesso.\n", name);
                break;
            case 5:
                displayBuckets(table);
                break;
            case 6:
                printStats(table);
                break;
            case 7:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (option != 7);

    freeHashTable(table);
    return 0;
}

