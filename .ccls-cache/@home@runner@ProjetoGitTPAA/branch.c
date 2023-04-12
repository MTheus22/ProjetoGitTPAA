#include <stdio.h>
#include <stdlib.h>
#include "branch.h"

void git_branch(char nome, head* h){
  branch* b = (branch*)malloc(sizeof(branch));
  b->nome = nome;
  b->c = h->b->c; // a nova branch aponta para o commit para o qual a head esta apontando
}

void git_init(head** h, branch** b, commit** c){             // inicializa a head, a master e o primeiro commit.
  head* Head = (head*)malloc(sizeof(head));
  branch* master = (branch*)malloc(sizeof(branch));
  commit* first = (commit*)malloc(sizeof(commit));

  first->endereco = 0;
  first->anterior = NULL;
  first->proximos = NULL;
  first->mensagem = 'A';

  master->nome = 'M';
  master->c = first;

  Head->b = master;
  Head->nome = 'h';

  *h = Head;
  *b = master;
  *c = first;

}

void git_commit(int endereco, char mensagem, head* h){
  commit* novo = (commit*)malloc(sizeof(commit));
  commit* aux = h->b->c;
  
  novo->endereco = endereco;
  novo->mensagem = mensagem;
  
  novo->proximos = NULL;
  novo->anterior = aux;  // o novo commit aponta para o commit anterior
  aux->proximos = novo; // o commit anterior aponta para o novo commit

  h->b->c = novo;    //movendo a head e a branch para o novo commit
}