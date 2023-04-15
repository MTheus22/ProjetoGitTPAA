#include "branch.h"
#include <stdio.h>
#include <stdlib.h>
char *gera_hash(gancho *cabeca, char *hash)
{
    char string[50];
    int resultado = 0;
    for (int i=0; i < 5; i++)
    {
        string[2 * i] = 48 + (rand() % 9);
        string[2 * i + 1] = 65 + (rand() % 6);
    }
    resultado = verifica_combinacao(string, cabeca);
    if (resultado == ERRO)
        hash = gera_hash(cabeca, hash);
    else
    {
        strcpy(hash, string);
        return hash;
    }
}

int verifica_combinacao(char *string, gancho *cabeca)
{
    lista *atual = cabeca->primeiro;
    int resultado = 0;
    if (cabeca->primeiro == NULL)
    {
        return CORRETO;
    }
    else
    {
        while (atual != NULL)
        {
            resultado = strcmp(atual->hash, string);
            if (resultado == 0)
            {
                return ERRO;
            }
            atual = atual->proximo;
        }
        return CORRETO;
    }
}
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
