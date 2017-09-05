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
    printf("\n saporra");
}
 
/* Returns queue size */
void queuesize()
{
    printf("\n Queue size : %d", count);
}


/* Enqueing the queue */
void enq(struct node *data)
{
    if (rear == NULL) {
        printf("Nulo\n");
        rear = (struct node *)malloc(1*sizeof(struct node));
        rear->ptr = NULL;
        rear->info = data->info;
        rear->id = data->id;
        front = rear;
    }
    else
    {
        printf("não nullo\n");
        check(data);
    }
    count++;
}

void check(struct node *data) {
    struct node *current, *prev, *new;
    current = rear;
    prev = NULL;
    new = (struct node *)malloc(1*sizeof(struct node));
    new->info = data->info;
    new->id = data->id;
    while(current != NULL && current->info >= new->info) {
        printf("No laço \n");
        prev = current;
        current = current->ptr;
    }
    if(prev == NULL) {
        printf("Era NULL\n");
        new->ptr = front;
        front = new;
        printf("Tem no rear agr: %d\n", front->id);
    }
    else {
        printf("Novo\n");
        prev->ptr = new;
    }
    new->ptr = current;
    return;
}


/*void check(struct node *data)
{
    struct node *current = rear;
    struct node *prev = NULL;
    printf("Merda---\n");
    fflush(stdout);
    while (current != NULL) {
        printf("Fuçando\n");
        if (current->info < data->info) {
            printf("andou\n");
            prev = current;
            current = current->ptr;
        }
        else {
            printf("Inseriu: %d", data->id);
            fflush(stdout);
            prev->ptr = data;
            data->ptr = current;
        }
        printf("Saiu: ");
        fflush(stdout);
    }
    return;
}*/

/* Displaying the queue elements */

void display()
{
    front1 = front;
    if ((front1 == NULL) && (rear == NULL))
    {
        printf("Queue is empty");
        return;
    }
    while (front1 != rear)
    {
        printf("%d ", front1->id);
        front1 = front1->ptr;
    }
    if (front1 == rear)
        printf("%d", front1->id);
}
 
/* Dequeing the queue */
/*int deq()
{
    int id;
    front1 = front;
    printf("Tem atualmente : %d\n", count);
    if (front1 == NULL)
    {
        printf("\n Error: Trying to display elements from empty queue");
        return -1;
    }
    else {
        if (front1->ptr != NULL) //tem gente na frente, remove o de tras
        {
            front1 = front1->ptr;
            id = front->id;
            free(front);
            front = front1;
        }
        else //n tem ninguém na frente, remove ele mesmo
        {
            id = front->id;
            free(front);
            front = NULL;
            rear = NULL;
        }
        count--;
        return id;
        
    }
}*/

/*int deq() {
    int id;
    struct node *tmp;
    if(rear == NULL) {
        printf("\n Error: Trying to display elements from empty queue");
        return -1;
    }
    else {
        id = rear->id;
        if (rear->ptr != NULL) {
            rear = rear->ptr;
        }
        else {
            rear = NULL;
        }
        count--;
        return id;
    }
}*/

int deq() {
    int id;
    struct node *current, *prev;
    current = front;
    while(current->ptr != NULL) {
        prev = current;
        current = current->ptr;
    }
    if(current != NULL) {
        id = current->id;
        free(current);
        prev->ptr = NULL;
        count--;
        return id;
    }
    else {
        printf("Ta vazio\n");
        return -1;
    }
}

/*int deq() {
    if (!rear)
        return -1;
    int id = rear->id;
    struct node *old = rear;
    rear = rear->ptr;
    free (old);
    return id;
}*/

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
 
// int main()
// {
//     // int no, ch, e;
 
//     // printf("\n 1 - Enque");
//     // printf("\n 2 - Deque");
//     // printf("\n 3 - Front element");
//     // printf("\n 4 - Empty");
//     // printf("\n 5 - Exit");
//     // printf("\n 6 - Display");
//     // printf("\n 7 - Queue size");
//     // create();
//     // while (1)
//     // {
//     //     printf("\n Enter choice : ");
//     //     scanf("%d", &ch);
//     //     switch (ch)
//     //     {
//     //     case 1:
//     //         printf("Enter data : ");
//     //         scanf("%d", &no);
//     //         enq(no);
//     //         break;
//     //     case 2:
//     //         deq();
//     //         break;
//     //     case 3:
//     //         e = frontelement();
//     //         if (e != 0)
//     //             printf("Front element : %d", e);
//     //         else
//     //             printf("\n No front element in Queue as queue is empty");
//     //         break;
//     //     case 4:
//     //         empty();
//     //         break;
//     //     case 5:
//     //         exit(0);
//     //     case 6:
//     //         display();
//     //         break;
//     //     case 7:
//     //         queuesize();
//     //         break;
//     //     default:
//     //         printf("Wrong choice, Please enter correct choice  ");
//     //         break;
//     //     }
//     // }
//     return 0;
// }

