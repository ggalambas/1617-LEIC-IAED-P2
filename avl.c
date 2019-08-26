#include "main.h"

// INICIALIZACAO

void STinit(link* head) {
	*head = NULL;
}

// BALANCEAMENTO

/* Retorna altura de um elemento */
int height(link h) {

	if(h == NULL)
		return 0; /* 0 se nao existir */

	return h->height;
}

/* Rotacao simples 'a esquerda */
link rotL(link h) {

	int height_left, height_right;
	link x = h->r;
	h->r = x->l;
	x->l = h;

	height_left = height(h->l);
	height_right = height(h->r);
	h->height = height_left > height_right ? height_left + 1 : height_right + 1;

	height_left = height(h->l);
	height_right = height(x->r);
	x->height = height_left > height_right ? height_left + 1 : height_right + 1;

	return x;
}

/* Rotacao simples 'a direita */
link rotR(link h) {

	int height_left, height_right;
	link x = h->l;
	h->l = x->r;
	x->r = h;

	height_left = height(h->l);
	height_right = height(h->r);
	h->height = height_left > height_right ? height_left + 1 : height_right + 1;

	height_left = height(x->l);
	height_right = height(h->r);
	x->height = height_left > height_right ? height_left + 1 : height_right + 1;

	return x;
}

/* Rotacao dupla esquerda-direita */
link rotLR(link h) {

	if(h == NULL)
		return h;

	h->l = rotL(h->l);
	return rotR(h);
}

/* Rotacao dupla direita-esquerda */
link rotRL(link h) {

	if(h == NULL)
		return h;

	h->r = rotR(h->r);
	return rotL(h);
}

/* Verifica se a arvore esta balanceada */
int balance(link h) {

	if(h == NULL)
		return 0;

	return height(h->l) - height(h->r);
}

/* Balanceia a arvore */
link AVLbalance(link h) {

	int balanceFactor, height_left, height_right;

	if(h == NULL)
		return h;

	balanceFactor = balance(h); 

	/* Se o ramo esquerdo for maior */
	if(balanceFactor > 1) {
		if(balance(h->l) > 0)
			h = rotR(h);
		else
			h = rotLR(h);
	}
	/* Se o ramo direito for maior */
	else if(balanceFactor < -1) {
		if(balance(h->r) < 0)
			h = rotL(h);
		else
			h = rotRL(h); 
	}
	/* Se estiver balanceada */
	else {
		height_left = height(h->l);
		height_right = height(h->r);
		h->height = height_left > height_right ? height_left + 1 : height_right + 1;
	}

	return h;
} 

// PROCURA

/* Procura um elemento, e devolve o seu endereco */
Product* STsearch(link h, Key v) {
	Key t = h->item.key;
	if(h == NULL)
		return NULL;
	/* Se encontrar, retorna o endereco */
	if eq(v, t)
		return &(h->item);
	/* Se for menor, porcura no ramo esquerdo */
	if less(v, t)
		return STsearch(h->l, v);
	/* Se for maior, porcura no ramo direito */
	else
		return STsearch(h->r, v);
}
 
/* Percorre a arvore da direita para a esquerda,
'a procura do elemento com maior valor */
void STtraverse(link h, Product* max) {
	if (h == NULL) return;

	STtraverse(h->r, max);
	if(h->item.value >= max->value)
		*max = h->item;
	STtraverse(h->l, max);
}

/* Percorre a arvore da esquerda para a direita,
imprimindo todos os elementos */
void STsort(link h) {
	if (h == NULL) return;

	STsort(h->l);
	printf("%s %d\n", h->item.key, h->item.value);
	STsort(h->r);
}

/* Insere um novo elemento */
link new(Product item, link l, link r) {

	link x = (link) malloc(sizeof(struct STnode));
	x->item = item;
	x->l = l;
	x->r = r;
	x->height = 1;

	return x;
}

/* Procura a posicao correta para inserir um novo elemento */
link insertR(link h, Product item) {

	if(h == NULL)
		return new(item, NULL, NULL);
	/* Se for menor, procura no ramo esquerdo */
	if( less(item.key, h->item.key) )
		h->l = insertR(h->l, item);
	/* Se for maior, procura o ramo direito */
	else
		h->r = insertR(h->r, item);
	/* Balanceia a arvore */
	h = AVLbalance(h);

	return h;
}

/* Depois de inserir um novo elemento e balancear a arvore,
da um novo endereco 'a cabeca */
void STinsert(link* head, Product item) {
	*head = insertR(*head, item);
}

// REMOCAO

/* Encontra o elemento mais a direita */
link max(link h) {
    if( h==NULL || h->r==NULL )
    	return h;
    else
    	return max(h->r);
}

/* Retira um elemento da arvore */
link deleteR(link h, Key k, int* total) {

	Product x;

	if( h == NULL ) return h;
	/* Se for menor, procura no ramo esquerdo */
	else if( less(k, h->item.key) )
		h->l = deleteR(h->l, k, total);
	/* Se for maior, procura no ramo direito */
	else if( less(h->item.key, k) )
		h->r = deleteR(h->r,k, total);
	/* Se encontrar */
	else {
		/* Se tiver dois filhos, liga o pai ao filhos */
		if( h->l != NULL && h->r != NULL ){
			link aux = max(h->l);
			x = h->item;
			h->item = aux->item;
			aux->item=x;
			h->l = deleteR(h->l, aux->item.key, total);
		}
		else {
			link aux=h;
			/* Se nao tiver filhos, apaga */
			if( h->l == NULL && h->r == NULL ){
				h = NULL;}
			/* Se so tiver o filho  direito, liga o pai
			ao filho direito */
			else if( h->l == NULL )
				h = h->r;
			/* Se so tiver o filho  esquerdo, liga o pai
			ao filho esquerdo */
			else
				h = h->l;

			/* Liberta a posicao de memoria do elemento a eliminar */
			free(aux);
			(*total)--;
		}
	}

	h = AVLbalance(h);
	return h;
}

/* Depois de remover um elemento e balancear a arvore,
da um novo endereco 'a cabeca */
void STdelete(link* head, Key k, int* total) {   
    *head = deleteR(*head, k, total);
}

/* Liberta as posicoes de memoria associadas 'a arvore */
link freeR(link h, int* total) {

	if (h==NULL)
		return h;

	h->l=freeR(h->l, total);
	h->r=freeR(h->r, total);

	return deleteR(h,h->item.key, total);
}

void STfree(link* head, int* total) {
	*head=freeR(*head, total);
	free(head);
}