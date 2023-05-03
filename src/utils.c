#include "../headers/utils.h"
#include "../headers/git.h"
#include <openssl/sha.h>
#include <stdbool.h>
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

bool is_interactive_mode(char **argv) {
  if (strcmp(*argv + 1, "-i") || strcmp(*argv + 1, "-I"))
    return true;
  else
    return false;
}

bool is_menu_mode(char **argv) {
  if (strcmp(*argv + 1, "-m") || strcmp(*argv + 1, "-M"))
    return true;
  else
    return false;
}

void interactive_mode(char **argv, Head *const head,
                      BranchList *const branch_list) {
  char args[100];
  do {
    scanf("%99s", args);
    printf("antes do main");
    char *main_command = get_main_command(args);
    printf("antes do handle");
    handle_command(main_command, args, head, branch_list);
  } while (strcmp(args, "quit") != 0);
}

void menu_mode(Head *const head, BranchList *const branch_list) {}

void single_action_mode(char **argv, Head *const head,
                        BranchList *const branch_list) {}

bool handle_command(char *command, char *command_arguments, Head *const head,
                    BranchList *const branch_list) {
  command_arguments = strstr(command_arguments, "-");
  printf("sapato");
  if (strcmp(command, "init") == 0) {
    return true;
  } else if (strcmp(command, "commit") == 0) {
    char *message = strstr(command_arguments, "-m ");
    if (!message) {
      message = strstr(command_arguments, "--message ");
      if (!message)
        return false;
      else
        message = message + strlen("--message ");
    } else
      message = message + 3;
    git_commit(message, head);
    return true;
  } else if (strcmp(command, "branch") == 0) {
    char *command_to_jump = "git branch ";
    char *branch_name = strstr(command_arguments, command_to_jump);
    branch_name = branch_name + strlen(command_to_jump);
    git_branch(branch_name, head, branch_list);
    return true;
  } else if (strcmp(command, "checkout") == 0) {
    return true;
  } else if (strcmp(command, "merge") == 0) {
    return true;
  } else if (strcmp(command, "log") == 0) {
    printf("entrei aqui");
    git_log(head);
    return true;
  } else {
    return false;
  }
}

char *get_main_command(char *args) {
  if (strstr(args, "init"))
    return "init";
  else if (strstr(args, "commit"))
    return "commit";
  else if (strstr(args, "branch"))
    return "branch";
  else if (strstr(args, "checkout"))
    return "checkout";
  else if (strstr(args, "merge"))
    return "merge";
  else if (strstr(args, "log"))
    return "log";
  return NULL;
}
