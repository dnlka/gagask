#include <stdio.h>
#include <stdlib.h>

int tre(int a){
	return a;}

int fre(int a){
	return 2*a;}

int dre(int a){
	return a*a;}

int gre(int a){
	return a*a*a;}

int vre(int a){
	return a%2;}\

int callfunc(int(*cur)(int),int a){
	return cur(a);
}

int main(){
	int (*arrfunc[5])(int)={tre,fre,dre,gre,vre};
	int n,dec;
	printf("Введите номер функции: ");
	scanf("%d",&n);
	printf("Введите число: ");
	scanf("%d",&dec);
	printf("%d\n",callfunc(arrfunc[n],dec));
	return 0;
}

