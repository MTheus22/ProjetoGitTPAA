#include "../headers/utils.h"
#include "../headers/git.h"
#include <stdbool.h>
#include <openssl/sha.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_test(Head *const head, BranchList *const branch_list) {
  printf("--Git init feito--\n");
  first_commit("Primeiro commit", head, branch_list);
  printf("Nome da branch: %s\n", head->branch->name);
  printf("Hash do commit: ");
  print_hash_string(head);
  printf("\n");
  printf("Mensagem do commit: %s\n", head->branch->commit->message);
  git_commit("Segundo commit", head);
  printf("\n--Depois de um commit--\n\n");
  printf("Nome da branch: %s\n", head->branch->name);
  printf("Hash do commit: ");
  print_hash_string(head);
  printf("\n");
  printf("Mensagem do commit: %s\n", head->branch->commit->message);
}

void print_hash_string(Head *const head) {
  char *hash_string = get_hash_string(head->commit->hash);
  printf("%s", hash_string);
  free(hash_string);
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

bool is_interactive_mode(char *argv[]) {
  if (strcmp(argv[1], "-i") || strcmp(argv[1], "-I"))
    return true;
  else
    return false;
}

char *get_main_command(char *args) {
  if (strstr(args, "init"))
    return "init";
  if (strstr(args, "commit"))
    return "commit";
  if (strstr(args, "branch"))
    return "branch";
  if (strstr(args, "checkout"))
    return "checkout";
  if (strstr(args, "merge"))
    return "merge";
  return NULL;
}

void interactive_mode(Head *const head, BranchList *const branch_list) {
  char *args;
  while (!strcmp(args, "quit")) {
    scanf("%s", args);
    char *main_command = get_main_command(args);
	char **sub_args = get_sub_args(args);
    perform_command(head, branch_list, main_command, sub_args);
  }
}
