#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/utils.h"
#include "../headers/git.h"

void print_test(Head* const head) {
  printf("--Git init feito--\n");
  git_commit("Primeiro commit", head);
  printf("salada");
  printf("Nome da branch: %s\n", head->branch->name);
  printf("Hash do commit: %s\n", head->branch->commit->hash);
  printf("Mensagem do commit: %s\n", head->branch->commit->message);
  git_commit("Segundo commit", head);
  printf("\n--Depois de um commit--\n\n");
  printf("Nome da branch: %s\n", head->branch->name);
  printf("Hash do commit: %s\n", head->branch->commit->hash);
  printf("Mensagem do commit: %s\n", head->branch->commit->message);
}

int is_interactive_mode(char *argv[]) {
  if (strcmp(argv[1], "-i") || strcmp(argv[1], "-I"))
    return 1;
  else
    return 0;
}

char **read_next_param(int argc, char *argv[]) {
  
}
