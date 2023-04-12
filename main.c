#include <stdio.h>
#include <stdlib.h>
#include "branch.h"

int main(void) {
  head* h;
  branch* master;
  commit* first;

  git_init(&h, &master, &first);

  printf("\n%c", h->nome);
  printf("\n%c", h->b->nome);
  printf("\n%c",h->b->c->mensagem);

  git_commit(1, 'B', h);

  printf("\n%d banana", h->b->c->proximos->endereco);

  printf("\n%c", h->b->c->proximos->mensagem);
  
  return 0;
}