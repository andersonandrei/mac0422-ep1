/*
 * C Program to Implement Queue Data Structure using Linked List
 */
/*
 * C Program to Implement Queue Data Structure using Linked List
 */
#include "queue.h"

int count = 0;

/* Create an empty queue */
void create (struct node **rear, struct node **front) {
    front = rear = NULL;
}
 
/* Returns queue size */
int queuesize() {
    return count;
}

/* Enqueing the queue */
void enq(struct node *data, struct node **rear, struct node **front)
{
    printf("front entrou: #%08x\n " , front);
    if (rear == NULL) {
        printf("Colocou no inicio\n");
        *rear = (struct node *)malloc(1*sizeof(struct node));
        (*rear)->ptr = NULL;
        (*rear)->info = data->info;
        (*rear)->id = data->id;
        *front = *rear;
        printf("Saiu com front: #%08x \n", front);
    }
    else {
        printf("Colocou depois\n");
        check(data, rear, front);
        printf("Saiu com front depois: #%08x \n", front);
    }
    count++;
    return ;
}

void check(struct node *data, struct node **rear, struct node **front) {
    struct node *current, *prev, *new;
    current = *front;
    prev = NULL;
    new = (struct node *)malloc(1*sizeof(struct node));
    new->info = data->info;
    new->id = data->id;
    while(current != NULL && current->info >= new->info) {
        prev = current;
        current = current->ptr;
    }
    if(prev == NULL) {
        printf("Na cabeça\n");
        new->ptr = *front;
        *front = new;
    }
    else {
        printf("No else\n");
        prev->ptr = new;
        *rear = new;
    }
    new->ptr = current;
    return;
}


/* Dequeing the queue */
int deq(struct node **rear, struct node **front)
{
    int id;
    struct node *current, *prev;
    current = *front;
    prev = NULL;
    while(current->ptr != NULL) {
        prev = current;
        current = current->ptr;
    }
    if (current == NULL) {
        return -1;
    }
    else {
        id = current->id;
        if(prev == NULL) {
            current = NULL;
        }
        else {
            prev->ptr = NULL;
        }
        count--;
        return id;
    }
}
