#ifndef _ARMAZEM_
#define _ARMAZEM_

// BIBLIOTECAS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ABSTRACOES

#define MAX_CHAR 8
#define less(a,b) (strcmp(a,b)<0)
#define eq(a,b) (strcmp(a,b)==0)
#define need_new_max(a,b) ( a.value > b.value || (a.value == b.value && less(a.key, b.key)) )

// TIPOS DE DADOS

typedef struct {
	char key[MAX_CHAR+1];
	int value;
} Product;

typedef struct STnode* link;

struct STnode {
	Product item;
	link l, r;
	int height;
};

typedef char* Key;

// COMMANDOS

void command_a(link*, Product*, int*);
void command_l(link*);
void command_m(Product*, int*);
void command_r(link*, Product*, int*);

// FUNCOES DA ARVORE

void STinit(link*);
Product* STsearch(link, Key);
void STinsert(link*, Product);
void STdelete(link*, Key, int*);
void STsort(link);
void STtraverse(link, Product*);
void STfree(link*, int*);

#endif