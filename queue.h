#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include "structs.h"

void create();
void enq(struct node *data);
int deq();
void empty();
void display();
int queuesize();
int frontelement();
//int main();
void check(struct node *data);
void removeAll();

#endif