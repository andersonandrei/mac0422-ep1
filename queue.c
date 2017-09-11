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

/*void enqEnd (struct node *data, struct node **rear, struct node **front)
{
    //printf("Entrou pra empilhar : %d #%08x\n e #%08x , %d\n",data->id, rear, front, queuesize(*rear, *front));
    fflush(stdout);
    if (front == 0) {
        printf("Rear NULL \n");
        fflush(stdout);
        *front = (struct node *)malloc(1*sizeof(struct node));
        (*front)->ptr = NULL;
        (*front)->info = data->info;
        (*front)->id = data->id;
        *front = *rear;
    }
    else {
        printf("Check \n");
        fflush(stdout);
        checkEnd(data, rear, front);
    }
    count++;
    return ;
}

void checkEnd (struct node *data, struct node **rear, struct node **front) {
    struct node *current, *prev, *new;
    current = *rear;
    prev = NULL;
    new = (struct node *)malloc(1*sizeof(struct node));
    new->info = data->info;
    new->id = data->id;
    printf("Vai Checkar \n");
    fflush(stdout);
    while(current != NULL) {
        printf("Andou \n");
        fflush(stdout);
        prev = current;
        current = current->ptr;
    }
    -if(prev == NULL) {
        new->ptr = *front;
        *front = new;
    }
    printf("Vai setar prev \n");
    fflush(stdout);

    prev->ptr = new;
    *rear = new;

    new->ptr = NULL;
    return;
}*/



/* Enqueing the queue */
/*void enqEnd(struct node *data, struct node **rear, struct node **front)
{   
    //printf("Entrou pra empilhar : %d #%08x\n e #%08x , %d\n",data->id, rear, front, queuesize(*rear, *front));
    if (rear == NULL) {
        printf("\n Rear ta null");
        *rear = (struct node *)malloc(1*sizeof(struct node));
        (*rear)->ptr = NULL;
        (*rear)->info = data->info;
        (*rear)->id = data->id;
        *front = *rear;
    }
    else {
        checkEnd(data, rear, front);
    }
    count++;
    return ;
}

void checkEnd(struct node *data, struct node **rear, struct node **front) {
    struct node *current, *prev, *new;
    current = *front;
    prev = NULL;
    new = (struct node *)malloc(1*sizeof(struct node));
    new->info = data->info;
    new->id = data->id;
    while(current != NULL) {
        prev = current;
        current = current->ptr;
    }
    if(prev == NULL) {
        new->ptr = NULL;
        *front = *rear = new;
    }
    else {
        prev->ptr = new;
        new->ptr = NULL;
        *rear = new;
    }
    return;
}*/


void enqEnd(struct node *data, struct node **rear, struct node **front)
{   
    //printf("Entrou pra empilhar : %d #%08x\n e #%08x , %d\n",data->id, rear, front, queuesize(*rear, *front));
    struct node *current;
    current = *front;
    while(current!=NULL)
        current = current -> ptr;
    current = malloc(sizeof(struct node *));
    current = data;
    current -> ptr = NULL;
    return ;
}

/*void enqEnd(struct node *data, struct node **rear, struct node **front)
{   
    //printf("Entrou pra empilhar : %d #%08x\n e #%08x , %d\n",data->id, rear, front, queuesize(*rear, *front));
    struct node *current, *prev;
    current = *front;
    while(current!=NULL) {
        prev = current;
        current = current -> ptr;
    }
    if(*front == NULL) *front = data;
    else current->ptr = data;
    return ;
}*/

/* Enqueing the queue */
void enq(struct node *data, struct node **rear, struct node **front)
{   
    //printf("Entrou pra empilhar : %d #%08x\n e #%08x , %d\n",data->id, rear, front, queuesize(*rear, *front));
    if (rear == NULL) {
        printf("\n Rear ta null");
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

/*void enqEnd(struct node *data, struct node **rear, struct node **front)
{
    struct node *new;
    new = (struct node *)malloc(1*sizeof(struct node));
    new->info = data->info;
    new->id = data->id;
    if (front == NULL) {
        *front = (struct node *)malloc(1*sizeof(struct node));
        (*front)->ptr = NULL;
        (*front)->info = data->info;
        (*front)->id = data->id;
        *rear = *front;
    }
    else {
        new->ptr = NULL;
        (*front) = new;
    }
    return;
}*/

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
            *front = *rear = NULL;
        }
        else {
            current = NULL;
            prev->ptr = NULL;
            //*rear = prev;
        }
        count--;
        printf("Desepilhando %d\n", id);
        return id;
    }
}