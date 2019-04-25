#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define NEW 4

typedef struct Turn{
    char arr[NEW];
    int first;
    int last;
}turn;

void initTurn(turn* tr){
    tr->first=-1;
    tr->last=-1;
}

int isEmpty(turn *tr){
    if (tr->first==tr->last) return 1;
    else return 0;
}

char pop(turn *tr){
        if (isEmpty(tr)) return '.';
        tr->first=(tr->first+1)%NEW;
        return tr->arr[tr->first];
}

void push(char b,turn *tr){
    tr->last=(tr->last+1)%NEW;
    tr->arr[tr->last]=b;
}

int count(turn *tr){
    return (NEW+tr->last-tr->first)%NEW;
}

char top(turn* tr){
        if (isEmpty(tr)) return '.';
        return tr->arr[(tr->first+1)%NEW];
}

int main(){
    turn tr;
    initTurn(&tr);
    push('a',&tr);
    push('b',&tr);
    printf("%c\n",pop(&tr));
    printf("%c\n",pop(&tr));
    push('c',&tr);
    push('d',&tr);
    push('e',&tr);
    printf("top is %c\ncount:%d\n",top(&tr),count(&tr));
    printf("%c\n",pop(&tr));
    push('f',&tr);
    printf("%c\n",pop(&tr));
    push('g',&tr);
    printf("%c\n",pop(&tr));
    printf("%c\n",pop(&tr));
    printf("%c\n",pop(&tr));
    return 0;}
