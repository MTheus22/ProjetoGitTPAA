#include <stdio.h>
#include <stdlib.h>
#include "branch.h"
#include <string.h>
#define ERRO -1
#define CORRETO 1
#define ATIVADO 2

struct gancho
{
  lista *primeiro;
};

struct lista
{
  char hash[10];
  char mensagem[50];
  lista *anterior;
  lista *proximo;
  lista *ramificacao;
};

struct head
{
  lista *repos_head;
  branch *branch_atual;
};

struct branch
{
  char nome[50];
  lista *repos_branch;
  char hash[10];
};

lista *inicia_lista(void)
{
  lista *Lista = (lista *)malloc(sizeof(lista));
  Lista->proximo = NULL;
  Lista->anterior = NULL;
  return Lista;
}

head *inicia_head(void)
{
  head *Lista = (head *)malloc(sizeof(head));
  Lista->repos_head = NULL;
  Lista->branch_atual = NULL;
  return Lista;
}

branch *inicia_branch(void)
{
  branch *Lista = (branch *)malloc(sizeof(branch));
  Lista->repos_branch = NULL;
  strcpy(Lista->nome, "MASTER");
  return Lista;
}

gancho *inicia_cabeca(void)
{
  gancho *Lista = (gancho *)malloc(sizeof(gancho));
  Lista->primeiro = NULL;
  return Lista;
}

void git_branch(lista *atual, char *nome_branch)
{
  branch *novo = (branch *)malloc(sizeof(branch));
  novo->repos_branch = atual;
  strcpy(novo->hash, atual->hash);
  strcpy(novo->nome, nome_branch);
}

void git_commit(gancho *cabeca, branch *repos_atual, head *repositorio, char *text)
{
  char string[10];
  lista *novo = (lista *)malloc(sizeof(lista));
  if (cabeca->primeiro == NULL)
  {
    cabeca->primeiro = novo;
    strcpy(novo->mensagem, text);
    novo->proximo = NULL;
    novo->anterior = NULL;
    repos_atual->repos_branch = novo;
    repositorio->repos_head = novo;
    novo->ramificacao = NULL;
    repositorio->branch_atual = repos_atual;
    strcpy(novo->hash, gera_hash(cabeca));
  }
  else
  {
    if (repositorio->repos_head->proximo == NULL)
    {
      repos_atual->repos_branch = novo;
      novo->anterior = repositorio->repos_head;
      novo->ramificacao = NULL;
      repositorio->repos_head->proximo = novo;
      repositorio->repos_head = novo;
      novo->proximo = NULL;
      strcpy(novo->mensagem, text);
      repositorio->branch_atual = repos_atual;
      strcpy(novo->hash, gera_hash(cabeca))
    }
    else
    {
      repos_atual->repos_branch = novo;
      repositorio->repos_head->ramificacao = novo;
      novo->anterior = repositorio->repos_head;
      repositorio->repos_head = novo;
      novo->proximo = NULL;
      strcpy(novo->mensagem, text);
      repositorio->branch_atual = repos_atual;
      strcpy(novo->hash, gera_hash(cabeca))
    }
  }
}

void git_log(head *repositorio)
{
  lista *atual = repositorio->repos_head;
  while (atual->anterior != NULL)
  {
    printf("Mensagem: %s", atual->mensagem);
    atual = atual->anterior;
  }
}

head *git_checkout(head *repositorio, char *nome_branch, gancho *cabeca)
{
  lista *atual = cabeca->primeiro;
}

char *gera_hash(gancho *cabeca)
{
  char hash[10];
  char string[50];
  int resultado = 0;
  for (int i = 0; i < 5; i++)
  {
    string[2 * i] = 48 + (rand() % 9);
    string[2 * i + 1] = 65 + (rand() % 6);
  }
  resultado = verifica_combinacao(string, cabeca);
  if (resultado == ERRO)
    strcpy(hash, hash = gera_hash(cabeca));
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

int verificia_comando(gancho *cabeca,char *primeiro, char *segundo, char *terceiro)
{
  int erro = 0;
  if (strcmp(primeiro, "git") != 0)
  {
    printf("Comando nao reconhecido.\n");
    return ERRO;
  }
  else
  {
    if (strcmp(segundo, "commit") == 0)
    {
    }
    else if (strcmp(segundo, "log") == 0)
    {
    }
    else if (strcmp(segundo, "checkout") == 0)
    {
    }
    else if (strcmp(segundo, "branch") == 0)
    {
    }
    else
    {
      return ERRO;
    }
  }
  erro = verifica_terceiro(terceiro, cabeca);
}

int verifica_terceiro(gancho *cabeca,char *terceiro)
{
  lista *aux = cabeca->primeiro;
  while (aux != NULL)
  {
    
  }
}