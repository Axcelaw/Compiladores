#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "node.h"
#include "nodelist.h"

#define ONULL  1
#define OWIDTH 2

void _error(int type){
	switch(type){
		case ONULL:
			printf("Argumento inv�lido, n�o pode ser NULL!\n"); break;
		case OWIDTH:
			printf("Argumento inv�lido, fora da faixa correta!\n"); break;
	}
	exit(-1);
}

//create_node
Node* create_node(int nl, Node_type t, char* lexeme, Node* child0, ...) {
	if(t < nodo_programa && t > nodo_coringa) _error(OWIDTH);
	Node * child, * n = (Node*) malloc(sizeof(Node));

	n->num_line = nl;
	n->lexeme = lexeme;
	n->type = t;
	n->children = NULL;

	va_list ap;
	va_start(ap, child0);
	for (child = child0; child != NULL; child = va_arg(ap, Node*))
	   listadd(&n->children, child);
	va_end(ap);
	return n;
}

Node* coringa(char* lexeme){
	return create_node(0, nodo_coringa, lexeme, NULL, NULL);
}

//nb_of_children
int nb_of_children(Node* n) {
	if(n == NULL) _error(ONULL);
	return listlenght(&n->children);
}

//is_leaf
int is_leaf(Node* n){
	if(n == NULL) _error(ONULL);
	return (n->children == NULL);
}

//child
Node* child(Node* n, int i){
	if(n == NULL) _error(ONULL);
	return listget(&n->children, i);
}

//deep_free_node
int deep_free_node(Node* n){
	int i;	
	if(n != NULL){
		for(i = 0; i < nb_of_children(n); i++)
			deep_free_node(child(n, i));
		free(n);
	}
	return 0;
}

//height
int height(Node *n){	
	int max = 0, i, h;
	if(n != NULL){
		for(i = 0; i < nb_of_children(n); i++){
			h = height(child(n, i));
			if(max < h)
				max = h;
		}
		max++;
	}
	return max;
}

//uncompile FILE* outfile,     outfile,
void uncompile(FILE* outfile, Node *n){
	int i;

	switch(n->type){
		case nodo_coringa:
		case nodo_tipounico:
		case nodo_tipolista:

		case nodo_idf:

		case nodo_int:
		case nodo_float:

		case nodo_if:
		case nodo_while:
		case nodo_end:
		case nodo_else:

		case nodo_true:
		case nodo_false:
			fprintf(outfile,"%s ",n->lexeme);
	}

	for (i = 0; i < nb_of_children(n); i++)
		uncompile(outfile, child(n, i));
}
