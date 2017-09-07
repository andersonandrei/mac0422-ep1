/*
 * C Program to Implement Queue Data Structure using Linked List
 */
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int count = 0;

/* Create an empty queue */
void create() {
    front = rear = NULL;
}
 
/* Returns queue size */
int queuesize()
{
    return count;
}

/* Enqueing the queue */
void enq(struct node *data)
{
    if (rear == NULL) {
        printf("Colocou no inicio\n");
        rear = (struct node *)malloc(1*sizeof(struct node));
        rear->ptr = NULL;
        rear->info = data->info;
        rear->id = data->id;
        front = rear;
    }
    else
    {
        printf("Colocou depois\n");
        check(data);
    }
    count++;
}

void check(struct node *data) {
    struct node *current, *prev, *new;
    current = front;
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
        new->ptr = front;
        front = new;
    }
    else {
        printf("No else\n");
        prev->ptr = new;
        rear = new;
    }
    new->ptr = current;
    return;
}

/* Displaying the queue elements */
void display()
{
    printf("Qnt: %d\n", queuesize());
    front1 = front;
    if ((front1 == NULL) && (rear == NULL))
    {
        printf("Queue is empty\n");
        return;
    }
    while (front1->ptr != NULL)
    {
        printf("%d \n", front1->id);
        front1 = front1->ptr;
    }
    if (front1->ptr == NULL) {
        printf("ultimo ");
        printf("%d\n\n", front1->id);
    }
}

/* Dequeing the queue */
/*int deq() {
    int id;
    struct node *current, *prev;
    current = front;
    prev = NULL;
    printf("current: #%08x\n", current);
    while(current->ptr != NULL) {
        prev = current;
        current = current->ptr;
    }
    printf("prev: #%08x\n", prev);
    if(current != NULL) {
        printf("\n ta no if");
        fflush(stdout);
        id = current->id;
        printf("\n ta no if 2");
        fflush(stdout);
        //current = NULL;
        printf("\n ta no if 3");
        fflush(stdout);
        count--;
        prev->ptr = NULL;
        
        return id;
    }
    else {
        fflush(stdout);
        printf("Ta vazio\n");
        return -1;
    }
}*/

/* Dequeing the queue */
int deq()
{
    int id;
    struct node *current, *prev;
    current = front;
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

void removeAll() {
    while(queuesize > 0) {
        printf("Desempilhou: %d\n", deq());
    }
}

/* Returns the front element of queue */
int frontelement()
{
    if ((front != NULL) && (rear != NULL))
        return(front->info);
    else
        return 0;
}
 
/* Display if queue is empty or not */
void empty()
{
     if ((front == NULL) && (rear == NULL))
        printf("\n Queue empty");
    else
       printf("Queue not empty");
}
