/*  EP1 - MAC0422 - Anderson Andrei da Silva
    Shell + Gerenciador de processos */

#include "queue.h"

int count = 0;

/* Create an empty queue */
void create (struct node **rear, struct node **front) {
    front = rear = NULL;
}
 
/* Returns queue size */
int queuesize(struct node *rear, struct node *front) {
    int qnt = 0;
    struct node *current, *prev;
    current = front;
    prev = NULL;
    while(current != NULL) {
        prev = current;
        current = current->ptr;
        qnt++;
    }
    return qnt;
}

/* Enqueing the queue */
void enq(struct node *data, struct node **rear, struct node **front)
{   
    if (rear == NULL) {
        *rear = (struct node *)malloc(1*sizeof(struct node));
        (*rear)->ptr = NULL;
        (*rear)->info = data->info;
        (*rear)->id = data->id;
        *front = *rear;
    }
    else {
        check(data, rear, front);
    }
    count++;
    return ;
}

/* Help the enq() */
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
        new->ptr = *front;
        *front = new;
    }
    else {
        prev->ptr = new;
        *rear = new;
    }
    new->ptr = current;
    return;
}

/* Enqueing in the end of queue */
void enqEnd(struct node *data, struct node **rear, struct node **front)
{
    if (front == NULL) {
        *rear = data;

        *front = data;

    }
    else {
        data->ptr = NULL;
        (*rear) = data;
    }
    return;
}

/* Dequeing the queue */
int deq(struct node **rear, struct node **front)
{
    int id;
    struct node *current, *prev;
    current = *front;
    prev = NULL;
    while(current != NULL && current->ptr != NULL) {
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
            *front = NULL;
            *rear = NULL;
        }
        else {
            current = NULL;
            prev->ptr = NULL;
            //*rear = prev;
        }
        count--;
        return id;
    }
}