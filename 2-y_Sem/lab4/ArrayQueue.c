#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 100000

typedef struct Queue{
    int arr[SIZE];
    int rear;
    int frnt;
}queue;

queue init(){
    queue q = {{0}, -1, 0};
    return q;
}

void push(queue *q, int x) {
    if(q->rear < SIZE-1) {
        q->rear++;
        q->arr[q->rear] = x;
    }
    else
        printf("Full!\n");
}

int isEmpty(queue *q) {
    if(q->rear < q->frnt)
        return 1;
    else
        return 0;
}

int pop(queue *q) {
    int x;
    if(isEmpty(q)){
        printf("Empty!\n");
        return 0;
    }
    x = q->arr[q->frnt];
    q->frnt++;
    return x;
}

int removex(queue *q) {
    int x, h;
    if(isEmpty(q)) {
        printf("Empty!\n");
        return 0;
    }
    x = q->arr[q->frnt];
    for(h = q->frnt; h < q->rear; h++) {
        q->arr[h] = q->arr[h+1];
    }
    q->rear--;
    return(x);
}

int main(){
    queue q = init();
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