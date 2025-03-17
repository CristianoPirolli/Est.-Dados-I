#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NAME_LENGTH 100

typedef struct Node {
    char name[MAX_NAME_LENGTH];
    struct Node *next;
} Node;

typedef struct Stack {
    Node *top;
    int size;
} Stack;

void initializeStack(Stack *stack) {
    stack->top = NULL;
    stack->size = 0;
}

int isEmpty(Stack *stack) {
    return stack->size == 0;
}

void push(Stack *stack, const char *name) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    
    if (newNode == NULL) {
        printf("Erro na alocacao de memoria.\n");
        exit(1);
    }
    
    strncpy(newNode->name, name, MAX_NAME_LENGTH - 1);
    newNode->name[MAX_NAME_LENGTH - 1] = '\0';
    newNode->next = stack->top;
    stack->top = newNode;
    stack->size++;
}

char* pop(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Pilha vazia, sem valor no topo.\n");
        return NULL;
    }
    
    Node *temp = stack->top;
    char *poppedName = strdup(temp->name);
    stack->top = stack->top->next;
    stack->size--;
    
    free(temp);
    
    return poppedName;
}

char* peek(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Pilha vazia.\n");
        return NULL;
    }
    return stack->top->name;
}

const char* consult(Stack *stack, int position) {
    if (position < 1 || position > stack->size) {
        printf("Posicao invalida.\n");
        return NULL;
    }
    
    Node *current = stack->top;
    for (int i = 1; i < position; i++) {
        current = current->next;
    }
    return current->name;
}

void clearStack(Stack *stack) {
    while (!isEmpty(stack)) {
        free(pop(stack));
    }
}

void displayStack(Stack *stack) {
    system("cls");
    
    if (isEmpty(stack)) {
        printf("Pilha vazia.\n");
        return;
    }
    
    Node *current = stack->top;
    printf("\n------ TOPO DA PILHA ------\n");
    printf("                            \n");
    while (current != NULL) {
        printf("|   %s     \n", current->name);
        current = current->next;
    }
    printf("                           \n");
    printf("------ BASE DA PILHA ------\n");

    printf("\nPressione Enter para voltar ao menu...");
    getchar(); 
}

int main() {
    Stack stack;
    initializeStack(&stack);
    
    int option, position;
    char name[MAX_NAME_LENGTH];
    
    do {
        printf("\n ------- MENUZINHO -------\n");
        printf(" |                       |\n");
        printf(" | 1. EMPILHAR NOME      |\n");
        printf(" | 2. DESEMPILHAR NOME   |\n");
        printf(" | 3. VERIFICAR TOPO     |\n");
        printf(" | 4. CONSULTAR POSICAO  |\n");
        printf(" | 5. EXIBIR NOMES       |\n");
        printf(" | 6. SAIR               |\n");
        printf(" |                       |\n");
        printf(" |   ESCOLHA UMA OPCAO   |\n");
        printf(" -------------------------\n");
        scanf("%d", &option);
        getchar();
        
        switch (option) {
            case 1:
                system("cls");
                printf("DIGITE O NOME: ");
                fgets(name, MAX_NAME_LENGTH, stdin);
                name[strcspn(name, "\n")] = '\0';
                push(&stack, name);
                break;
                
            case 2: {
            	system ("cls");
                char *poppedName = pop(&stack);
                if (poppedName != NULL) {
                    printf("NOME DESEMPILHADO: %s\n", poppedName);
                    free(poppedName);
                }
                break;
            }
                
            case 3:
            	system ("cls");
                if (!isEmpty(&stack)) {
                    printf("TOPO DA PILHA: %s\n", peek(&stack));
                }
                break;
                
            case 4:
            	system ("cls");
                printf("DIGITE A POSICAO A SER CONSULTADA: ");
                scanf("%d", &position);
                getchar();
                {
                const char *consultedName = consult(&stack, position);
                	if (consultedName != NULL) {
                    	printf("NOME NA POSICAO %d: %s\n", position, consultedName);
                	}
                }
                break;
                
            case 5:
                displayStack(&stack);
                break;
                
            case 6:
                clearStack(&stack);
                printf("FINALIZANDO...\n");
                break;
                
            default:
                printf("OPCAO INVALIDA\n");
        }
    } while (option != 6);
    
    return 0;
}

