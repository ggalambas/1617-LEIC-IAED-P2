#include "main.h"

void command_a(link* head, Product *max, int *total) {

	Product *node, new;

	scanf("%s", new.key);
	scanf("%d", &new.value);

	/* Atribui ao node o endereco do elemento por adicionar,
	se ja existir na arvore */
	node = STsearch(*head, new.key);

	if( node == NULL) {	// SE NAO EXISTE NA ARVORE

		STinsert(head, new);

		if( *total == 0 )
			*max = new;
		else if( need_new_max(new,(*max)) )
			*max = new;

		(*total)++;
	}

	else if( new.value != 0 ) {	// SE JA EXISTE NA ARVORE

		/* Adiciona-se 'a chave da arvore o novo valor introduzido */
		node->value += new.value;
		if( node->value < 0) node->value = 0;

		/* Caso se incremente o maximo ou o novo no' seja maior
		que o maximo, atribui-se novo valor ao maximo */
		if( new.value > 0 && need_new_max((*node),(*max)) )
			*max = *node;
		/* Caso se decremente o maximo, percorre-se a arvore
		para se encontrar um novo */
		else if( new.value < 0 && eq(new.key, max->key) ) {
			*max = *node;
			STtraverse(*head, max);
		}
	}
}

void command_m(Product *max, int *total) {
	if( *total != 0 )
		printf("%s %d\n", max->key, max->value);
}

void command_r(link* head, Product *max, int *total) {

	char del[MAX_CHAR+1];
	scanf("%s", del);

	STdelete(head, del, total);
	/* Caso o se elimine o maximo, percorre-se a arvore
	para se encontrar um novo */
	if( eq(max->key, del) && *head != NULL) {
		*max = (*head)->item;
		STtraverse(*head, max);
	}
}