/* INTRODUCAO AOS ALGORITMOS E ESTRUTURAS DE DADOS
2016/2017 - 2 SEMESTRE
PROJETO 2

86372 ALEXANDRE GALAMBAS
86430 GUILHERME GALAMBAS */

#include "main.h"

int main() {

	link *head;
	head = (link*) malloc(sizeof(link));
	STinit(head);
	
	Product largest_stock;
	int num_keys = 0;

	while(1) {
		switch(getchar()) {
			case 'a':
				getchar();
				command_a(head, &largest_stock, &num_keys);
				break;
			case 'l':
				STsort(*head);
				break;
			case 'm':
				getchar();
				command_m(&largest_stock, &num_keys);
				break;
			case 'r':
				getchar();
				command_r(head, &largest_stock, &num_keys);
				break;
			case 'x':
				getchar();
				printf("%d\n", num_keys);
				STfree(head, &num_keys);
				return EXIT_SUCCESS;
		}
	}

	return EXIT_FAILURE;
}