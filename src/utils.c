#include "../headers/utils.h"
#include "../headers/git.h"
#include <openssl/sha.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_test(Head *const head, BranchList *const branch_list) {
  printf("--Git init feito--\n");
  first_commit("Primeiro commit", head, branch_list);
  printf("Nome da branch: %s\n", head->branch->name);
  printf("Hash do commit: %s\n", get_hash_string(head->branch->commit->hash));
  printf("Mensagem do commit: %s\n", head->branch->commit->message);
  git_commit("Segundo commit", head);
  printf("\n--Depois de um commit--\n\n");
  printf("Nome da branch: %s\n", head->branch->name);
  printf("Hash do commit: %s\n", get_hash_string(head->branch->commit->hash));
  printf("Mensagem do commit: %s\n", head->branch->commit->message);
}

char *get_hash_string(unsigned char *hash) {
  char *hash_string = malloc(SHA256_DIGEST_LENGTH * 2 + 1);
  int hash_byte_counter = 0;
  for (int i = 0; i < SHA256_DIGEST_LENGTH * 2; i += 2) {
    sprintf(hash_string + i, "%02x", hash[hash_byte_counter]);
    hash_byte_counter++;
  }
  *(hash_string + SHA256_DIGEST_LENGTH * 2) = '\0';
  return hash_string;
}

int is_interactive_mode(char *argv[]) {
  if (strcmp(argv[1], "-i") || strcmp(argv[1], "-I"))
    return 1;
  else
    return 0;
}

char **read_next_param(int argc, char *argv[]) {}
