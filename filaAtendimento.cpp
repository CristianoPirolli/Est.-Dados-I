#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char ticket[7];
    struct Node* next;
} Node;

typedef struct Queue {
    Node* head;
    Node* tail;
} Queue;

void initQueue(Queue* q) {
    q->head = q->tail = NULL;
}

int isEmpty(Queue* q) {
    return q->head == NULL;
}

void enqueue(Queue* q, const char* ticket) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) exit(1);
    strcpy(newNode->ticket, ticket);
    newNode->next = NULL;
    if (isEmpty(q)) {
        q->head = newNode;
    } else {
        q->tail->next = newNode;
    }
    q->tail = newNode;
}

char* dequeue(Queue* q) {
    if (isEmpty(q)) return NULL;
    Node* temp = q->head;
    char* ticket = (char*)malloc(7 * sizeof(char));
    strcpy(ticket, temp->ticket);
    q->head = q->head->next;
    if (q->head == NULL) q->tail = NULL;
    free(temp);
    return ticket;
}

void displayQueue(Queue* q) {
    Node* temp = q->head;
    while (temp) {
        printf("%s ", temp->ticket);
        temp = temp->next;
    }
    printf("\n");
}

int queueSize(Queue* q) {
    int count = 0;
    Node* temp = q->head;
    while (temp) {
        count++;
        temp = temp->next;
    }
    return count;
}

void serveTicket(Queue* priorityQueue, Queue* normalQueue) {
    char* ticket;
    if (!isEmpty(priorityQueue)) {
        ticket = dequeue(priorityQueue);
        printf("Serving priority ticket: %s\n", ticket);
        free(ticket);
    } else if (!isEmpty(normalQueue)) {
        ticket = dequeue(normalQueue);
        printf("Serving normal ticket: %s\n", ticket);
        free(ticket);
    } else {
        printf("No tickets to serve.\n");
    }
}

void generateTicket(char* buffer, const char* prefix, int ticketNumber) {
    sprintf(buffer, "%s%04d", prefix, ticketNumber);
}

void takeTicket(Queue* priorityQueue, Queue* normalQueue, int* priorityTicketNumber, int* normalTicketNumber) {
    int option;
    char ticket[7];
    printf("-------- Ticket Menu --------\n");
    printf("|                           |\n");
    printf("| 1. Priority ticket        |\n");
    printf("| 2. Normal ticket          |\n");
    printf("|                           |\n");
    printf("| Choose the type of ticket |\n");
    printf("-----------------------------\n");
    scanf("%d", &option);

    if (option == 1) {
        generateTicket(ticket, "PR", *priorityTicketNumber);
        (*priorityTicketNumber)++;
        enqueue(priorityQueue, ticket);
        printf("Priority ticket %s added.\n", ticket);
    } else if (option == 2) {
        generateTicket(ticket, "NL", *normalTicketNumber);
        (*normalTicketNumber)++;
        enqueue(normalQueue, ticket);
        printf("Normal ticket %s added.\n", ticket);
    } else {
        printf("Invalid option.\n");
    }
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void displayCombinedQueue(Queue* priorityQueue, Queue* normalQueue) {
    Node* temp = priorityQueue->head;
    printf("CUSTOMER SERVICE QUEUE: ");
    while (temp) {
        printf("%s ", temp->ticket);
        temp = temp->next;
    }
    temp = normalQueue->head;
    while (temp) {
        printf("%s ", temp->ticket);
        temp = temp->next;
    }
    printf("\n");
}

void cleanupQueue(Queue* q) {
    Node* temp;
    while (q->head) {
        temp = q->head;
        q->head = q->head->next;
        free(temp);
    }
    q->tail = NULL;
}

int main() {
    Queue priorityQueue, normalQueue;
    int choice;
    int priorityTicketNumber = 1;
    int normalTicketNumber = 1;

    initQueue(&priorityQueue);
    initQueue(&normalQueue);

    while (1) {
        clearScreen();
        printf("----------------------\n");
        printf("|      MENU          |\n");
        printf("| 1. Take ticket     |\n");
        printf("| 2. Display queues  |\n");
        printf("| 3. Serve ticket    |\n");
        printf("| 4. Count in queues |\n");
        printf("| 5. Service queue   |\n");
        printf("| 6. Exit            |\n");
        printf("----------------------\n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                takeTicket(&priorityQueue, &normalQueue, &priorityTicketNumber, &normalTicketNumber);
                break;
            case 2:
                printf("PRIORITY QUEUE: ");
                displayQueue(&priorityQueue);
                printf("NORMAL QUEUE: ");
                displayQueue(&normalQueue);
                printf("Press Enter to continue...");
                getchar();
                getchar();
                break;
            case 3:
                serveTicket(&priorityQueue, &normalQueue);
                printf("Press Enter to continue...");
                getchar();
                getchar();
                break;
            case 4:
                printf("Number of people in priority queue: %d\n", queueSize(&priorityQueue));
                printf("Number of people in normal queue: %d\n", queueSize(&normalQueue));
                printf("Press Enter to continue...");
                getchar();
                getchar();
                break;
            case 5:
                displayCombinedQueue(&priorityQueue, &normalQueue);
                printf("Press Enter to continue...");
                getchar();
                getchar();
                break;
            case 6:
                cleanupQueue(&priorityQueue);
                cleanupQueue(&normalQueue);
                exit(0);
            default:
                printf("Invalid choice.\n");
                printf("Press Enter to continue...");
                getchar();
                getchar();
        }
    }

    return 0;
}

