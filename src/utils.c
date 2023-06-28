#include "../headers/utils.h"
#include "../headers/git.h"
#include "../headers/hash_table.h"
#include "../headers/commit_list.h"
#include <openssl/sha.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_test() {
  Head *head;
  BranchList *branch_list;
  CommitsTable *commits_table;
  git_init(&head, &branch_list, &commits_table);
  printf("--Git init feito--\n");
  printf("Nome da branch: %s\n", head->branch->name);
  printf("Hash do commit: %s\n", get_hash_string(head->branch->commit->hash));
  printf("Mensagem do commit: %s\n", head->branch->commit->message);
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

bool hash_compare(unsigned char *hash1, unsigned char *hash2) {
  for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    if (hash1[i] != hash2[i])
      return false;
  return true;
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

void interactive_mode() {
  char args[100];
  Head *head;
  BranchList *branch_list;
  CommitsTable *commits_table;
  CommitList * commit_list = malloc(sizeof(CommitList));
  commit_list->commit_list_node = NULL;
  commit_list->number_nodes = 0;
  commit_list->tail = NULL;
    git_init(&head, &branch_list, &commits_table);
  do {
    fgets(args, 100, stdin);
    args[strlen(args) - 1] = '\0'; // Remove o \n (enter)
    char *main_command = get_main_command(args);
    if (!main_command)
      printf("Comando invalido\n");
    else {
      char *command_arguments = get_command_arguments(main_command, args);
      handle_command(main_command, command_arguments, head,branch_list, commits_table, &commit_list);
    }
  } while (strcmp(args, "quit") != 0);
}

void menu_mode() {}

void single_action_mode(char **argv) {}

bool handle_command(char *command, char *command_arguments, Head *head, BranchList *branch_list, CommitsTable *commits_table, CommitList **commit_list) {
  if (strcmp(command, "init") == 0) {
    return true;
  } else if (strcmp(command, "commit") == 0) {
    char *message = read_param("-m", command_arguments);
    if (head->branch == NULL && head->commit == NULL)
      first_commit(message, head, branch_list, commits_table, commit_list);
    else
      git_commit(message, head, commits_table, commit_list);
    return true;
  } else if (strcmp(command, "branch") == 0) {
    char *branch_name = read_param("git branch", command_arguments);
    if (!strcmp(branch_name, "\0"))
      git_branch(NULL, head, branch_list);
    else
      git_branch(branch_name, head, branch_list);
    return true;
  } else if (strcmp(command, "checkout") == 0) {
    char *checkout_location = read_param("git checkout", command_arguments);
	unsigned char* hash = convert_hash_string_to_hash(checkout_location);
	if(hash == NULL)
    	git_checkout(head, branch_list,NULL, checkout_location, commits_table);
	else
		git_checkout(head, branch_list, hash, checkout_location, commits_table);
    return true;
  } else if (strcmp(command, "merge") == 0) {
    char *checkout_location = read_param("git merge", command_arguments);
	unsigned char *hash = convert_hash_string_to_hash(checkout_location);
	if(hash == NULL)
		git_merge(head, branch_list, NULL, checkout_location, commits_table, commit_list);
	else
		git_merge(head, branch_list, hash, checkout_location, commits_table, commit_list);
    return true;
  } else if (strcmp(command, "log") == 0) {
    git_log(head, commits_table);
    return true;
  } 
  else if (strcmp(command, "push") == 0) {
	git_push(branch_list, *commit_list);
	return true;
  }
  else {
    return false;
  }
}

int hex_char_to_int(char hexChar) {
    if (hexChar >= '0' && hexChar <= '9') {
        return hexChar - '0';
    } else if (hexChar >= 'A' && hexChar <= 'F') {
        return hexChar - 'A' + 10;
    } else if (hexChar >= 'a' && hexChar <= 'f') {
        return hexChar - 'a' + 10;
    } else {
        return -1;
    }
}

unsigned char* convert_hash_string_to_hash(char *hash_string){
	unsigned char* hash = malloc(SHA256_DIGEST_LENGTH);
	int j = 0;
	for(int i=0;i < SHA256_DIGEST_LENGTH * 2; i+=2){
		int hex_value1 = hex_char_to_int(hash_string[i]);
		if(hex_value1 == -1)
			return NULL;
		int hex_value2 = hex_char_to_int(hash_string[i + 1]);
		if(hex_value2 == -1)
			return NULL;
		hash[j] = (hex_value1 << 4) | hex_value2;
		j++;
	}
	return hash;
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
  else if(strstr(args, "push"))
	  return "push";
  return NULL;
}

char *get_command_arguments(char *main_command, char *args) {
  char *commands_start = malloc(strlen(args) + 1);
  strcpy(commands_start, "git ");
  strcat(commands_start, main_command);
  return strstr(args, commands_start);
}

char *read_param(char *param, char *args) {
  char *param_start = strstr(args, param);
  if (!param_start)
    return NULL;
  char *param_content_start = param_start + strlen(param) + 1;
  char *next_param = strstr(param_content_start, "-");
  if (!next_param) {
    char *param_content_buffer = malloc(
        strlen(param_content_start)); // Only for free always work outside
    strcpy(param_content_buffer, param_content_start);
    return param_content_buffer;
  } else {
    int param_length = next_param - param_content_start -
                       1; //-1 for removing the space for the next param
    char *param_content = malloc(param_length + 1);
    memcpy(param_content, param_content_start, param_length);
    *(param_content + param_length) = '\0';
    return param_content;
  }
}

bool param_exist(char *param, char *args) {
  if (strstr(param, args))
    return true;
  else
    return false;
}

Branch *search_on_branch_list(BranchList *const branch_list,
                              char *branch_name) {
  BranchList *current_node = branch_list;
  while (current_node) {
    if (!strcmp(current_node->branch->name, branch_name))
      return current_node->branch;
    else
      current_node = current_node->next_branch;
  }
  return NULL;
}
