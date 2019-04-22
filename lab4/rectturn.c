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

char pop(turn *tr){
    tr->first=(tr->first+1)%NEW;
    return tr->arr[tr->first];
}

void push(char b,turn *tr){
    tr->last=(tr->last+1)%NEW;
    tr->arr[tr->last]=b;
    //tr->last=(tr->last+1)%NEW;
}

int isEmpty(turn *tr){
    if (tr->last==-1) return 1;
    if (tr->first==tr->last) return 1;
    else return 0;
}

int count(turn *tr){ 
    return (NEW+tr->last-tr->first)%NEW;
}

char top(turn* tr){
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
    printf("top is %c\n",top(&tr));
    printf("%c\n",pop(&tr));
    push('f',&tr);
    printf("%c\n",pop(&tr));
    push('g',&tr);
    printf("%c\n",pop(&tr));
    printf("%c\n",pop(&tr));
    printf("%c\n",pop(&tr));
    return 0;}
