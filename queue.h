struct node
{
    int id;
    float info;
    struct node *ptr;
} *front,*rear,*temp,*front1;
 
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