/*  EP1 - MAC0422 - Anderson Andrei da Silva
    Shell + Gerenciador de processos */


#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include "mainData.h"

/* Create an empty queue */
void create (struct node **rear, struct node **front);
 
/* Returns queue size */
int queuesize(struct node *rear, struct node *front);

/* Enqueing the queue */
void enq(struct node *data, struct node **rear, struct node **front);

/* Help the enq() */
void check(struct node *data, struct node **rear, struct node **front);

/* Enqueing in the end of queue */
void enqEnd(struct node *data, struct node **rear, struct node **front);

/* Dequeing the queue */
int deq(struct node **rear, struct node **front);

#endif