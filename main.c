#include "branch.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  head *h;
  branch *master;
  commit *first;

  git_init(&h, &master, &first);
  printf("--Git init feito--\n");
  printf("PS:Não haveria nenhum commit após o git init mas por fim de testes o git init realiza automaticamente um primeiro commit\n");
  printf("Nome da branch: %c\n", h->b->nome);
  printf("Hash do commit: %i\n", h->b->c->endereco);
  printf("Mensagem do commit: %c\n", h->b->c->mensagem);
  git_commit(1, 'B', h);
  printf("\n--Depois de um commit--\n\n");
  printf("Nome da branch: %c\n", h->b->nome);
  printf("Hash do commit: %d\n", h->b->c->endereco);
  printf("Mensagem do commit: %c\n", h->b->c->mensagem);

  return 0;
}
