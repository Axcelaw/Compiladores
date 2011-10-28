#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

struct tac* create_inst_tac(const char* res, const char* arg1, const char* op, const char* arg2) {
   struct tac* i = (struct tac*) malloc(sizeof(struct tac));

   i->res = (char*) malloc(sizeof(char) * (1+strlen(res)));
   i->arg1 = (char*) malloc(sizeof(char) * (1+strlen(arg1)));
   i->op = (char*) malloc(sizeof(char) * (1+strlen(op)));
   i->arg2 = (char*) malloc(sizeof(char) * (1+strlen(arg2)));

   strcpy(i->res, res);
   strcpy(i->arg1, arg1);
   strcpy(i->op, op);
   strcpy(i->arg2, arg2);
   return i;
}

/** \brief Funcao que imprime o conteudo de uma instrucao TAC 
 *
 * @param out um ponteiro sobre um arquivo (aberto) aonde ira ser escrita a instrucao.
 * @param i a instrucao a ser impressa.
 */
void print_inst_tac(FILE* out, struct tac i) {
    if (!strcmp(i.op, ":="))
        fprintf(out, "%s := %s\n", i.res, i.arg1);
    else
        fprintf(out, "%s := %s %s %s\n", i.res, i.arg1, i.op, i.arg2);

/*

   char *rotulo = malloc(sizeof(char)*4);
  if(i.type == TACTYPE_LABEL) {
    fprintf(out, "%s:\n", i.arg1);
  }
  else {
    if(ordem < 10)
        sprintf(rotulo, "00%d", ordem);
    else if(ordem < 100)
        sprintf(rotulo, "0%d", ordem);
    else 
        sprintf(rotulo, "%d", ordem);
    fprintf(out, "%s:   ", rotulo);
    if(i.type == TACTYPE_FPRINT) {
        fprintf(out, "FPRINT %s\n", i.res);
    }
    if(i.type == TACTYPE_PRINT) {
        fprintf(out, "PRINT %s\n", i.res);
    }
    if(i.type == TACTYPE_ATTRIB) {
        if(strcmp(i.op, ":=") == 0)
            fprintf(out, "%s := %s\n", i.res, i.arg1);
        else
            fprintf(out, "%s := %s %s %s\n", i.res, i.arg1, i.op, i.arg2);
    }

    if(i.type == TACTYPE_GOTO) {
      fprintf(out, "GOTO %s\n", i.arg1);
    }
    if(i.type == TACTYPE_RELOP) {
      fprintf(out, "IF %s %s %s GOTO %s\n", i.arg1, i.op, i.arg2, i.res);
    }
  }*/
}

/** \brief Imprime no arquivo apontado por 'out' o conteudo da lista apontada
 * por 'code'.
 *
 * @param out um ponteiro sobre um arquivo (aberto) aonde ira ser escrita a lista (uma linha por elemento).
 * @param code o ponteiro para a lista a ser impressa.
 *
 * Obs.: cada linha impressa no arquivo deve comecar por um numero inteiro
 * (3 digitos) seguido de ':'. O numero deve ser o numero da linha.
 * Exemplo:
 *   001:  instrucao_qualquer
 *   002:  outra_instrucao
 *    .....
 *   999:  ultima_instrucao
 *   000:  agora_tem_instrucao_demais
 */
void print_tac(FILE* out, struct node_tac * code) {
    while (code) {
        fprintf(out, "%03d:   ", code->number);
        print_inst_tac(out, *code->inst);
        code = code->next;
    }
}

void append_inst_tac(struct node_tac ** code, struct tac * inst) {
    struct node_tac *new = (struct node_tac *) malloc(sizeof(struct node_tac));
    new->number = 0;
    new->inst = inst;
    cat_tac(code, &new);
}

void cat_tac(struct node_tac ** code_a, struct node_tac ** code_b) {
    int i = 1;
    struct node_tac *temp = *code_a;

    if (* code_b) {
        if (* code_a) {
            while (temp->next) {
               temp = temp->next;
               i++;
            }
            temp->next = *code_b;
            (*code_b)->prev = temp;
            temp = *code_b;
            do {
                temp->number = i++;
            } while (temp->next);
        } else {
           * code_a = * code_b;
        }
    }
}

