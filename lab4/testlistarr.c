#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define NOM 1000000

/* Не забудьте про следующие функции: */
typedef struct stacka{
    char arr[NOM];
    int top;
}stack;

// функция initStack
void initStacka(struct stacka* tr){
    tr->top=-1;
}

// функция pop
char popa(struct stacka *tr){
    if (isEmptya(tr)) return'.';
    tr->top--;
    return tr->arr[tr->top+1];
}
// функция push
void pusha(char b,struct stacka *tr){
    tr->top++;
    tr->arr[tr->top]=b;
}
// функция top
char topa(struct stacka *tr){
    if (isEmptya(tr)) return '.';
    return tr->arr[tr->top];
}

// функция isEmpty
int isEmptya(struct stacka *tr){
    if (tr->top==-1) return 1;
    else return 0;
}
// функция count
int counta(struct stacka *tr){
    return tr->top+1;
}

typedef struct list{
    char value;
    struct list *prev;
}list;

struct stackl{
    list* top;
};

// функция initStack
void initStackl(struct stackl* tr){
    tr->top=NULL;
}

// функция pop
char popl(struct stackl *tr){
    if (isEmptyl(tr)) return'.';
    list* tmp=tr->top->prev;
    char b=tr->top->value;
    free(tr->top);
    tr->top=tmp;
    return b;
}
// функция push
void pushl(char b,struct stackl *tr){
    list* tmp=(list*)malloc(sizeof(list));
    tmp->value=b;
    if (isEmptyl(tr)) tr->top=tmp;
    else{
        tmp->prev=tr->top;
        tr->top=tmp;}
}
// функция top
char topl(struct stackl *tr){
    if (isEmptyl(tr)) return '.';
    return tr->top->value;
}

// функция isEmpty
int isEmptyl(struct stackl *tr){
    if (tr->top==NULL) return 1;
    else return 0;
}
// функция count
int countl(struct stackl *tr){
    if (isEmptyl(tr)) return 0;
    list* tmp=tr->top;
    int count=1;
    while (tmp->prev){
        count++;
        tmp=tmp->prev;
    }
    return count;
}

int main(){
	long long unsigned int i;
	struct stacka arr;
	struct stackl tr;
	clock_t time=clock();
		initStacka(&arr);
		for(i=0;i<NOM;i++) pusha('a',&arr);
		for(i=0;i<NOM;i++) popa(&arr);
	time=clock()-time;
	printf("%Lg\n",(long double)time/CLOCKS_PER_SEC);
	time=clock();
		initStackl(&tr);
		for(i=0;i<NOM;i++) pushl('l',&tr);
		for(i=0;i<NOM;i++) popl(&tr);
	time=clock()-time;
	printf("%Lg\n",(long double)time/CLOCKS_PER_SEC);
	return 0;
}
