#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include "mainData.h"

void create (struct node **rear, struct node **front);
/* Returns queue size */
int queuesize();
/* Enqueing the queue */
void enq(struct node *data, struct node **rear, struct node **front);
void enqEnd(struct node *data, struct node **rear, struct node **front);
void check(struct node *data, struct node **rear, struct node **front);
void checkEnd (struct node *data, struct node **rear, struct node **front);
/* Dequeing the queue */
int deq(struct node **rear, struct node **front);


#endif