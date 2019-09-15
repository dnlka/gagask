#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct List {
    int field;
    struct List *next;
}list;

typedef struct Queue {
     list* frnt;
     list* rear;
}queue;

queue* init(){
    queue* q = malloc(sizeof(queue));
    q->frnt = NULL;
    q->rear = NULL;
    return q;
}


int isEmpty(queue *q) {
    if(q->frnt==NULL)
        return 1;
    else
        return 0;
}

void push(queue **q, int x) {

    list* new = malloc(sizeof(list));
    new->next = NULL;
    new->field = x;

    if(((*q)->rear == NULL) && ((*q)->frnt == NULL)){
        (*q)->rear = new;
        (*q)->frnt = (*q)->rear;
    }
    else {
        (*q)->rear->next = new;
        (*q)->rear = (*q)->rear->next;
    }
}

int pop(queue** q) {
    list* temp;
    int x;
    if(isEmpty(*q)==1) {
        printf("Empty!\n");
        return 0;
    }
    x = (*q)->frnt->field;
    temp = (*q)->frnt;
    (*q)->frnt = (*q)->frnt->next;
    free(temp);
    return x;
}

int main() {
    queue* q = init();
    clock_t time = clock();
    for(int i = 0;i<100000;i++){
        push(&q, i);
    }
    for(int i = 0;i<100000;i++){
        pop(&q);
    }
    time = clock() - time;
    printf("%lf\n", (double)time/CLOCKS_PER_SEC);
    return 0;
}
