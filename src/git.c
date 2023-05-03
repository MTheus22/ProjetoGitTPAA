#include "../headers/git.h"
#include "../headers/utils.h"
#include <openssl/sha.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void git_branch(char *name, Head *const head, BranchList *const branch_list) {
  if (!name)
    list_branches(head, branch_list);
  Branch *new_branch = malloc(sizeof(Branch));
  strcpy(new_branch->name, name);
  new_branch->commit = head->commit;
  if (branch_list->branch == NULL){
    branch_list->branch = new_branch;

  }
}

void initialize_branch_list(BranchList *const branch_list, Branch *new_branch){
	branch_list->next_branch = NULL;
	branch_list->branch = new_branch;
}

void insert_branch_list(BranchList *const branch_list, Branch *new_branch){
	branch_list->next_branch = malloc(sizeof(BranchList));
	branch_list->next_branch->branch = new_branch;
	branch_list->next_branch->next_branch = NULL;
}

void git_init(Head **head, BranchList **branch_list) {
  *head = malloc(sizeof(Head));
  *branch_list = malloc(sizeof(BranchList));

  (*head)->commit = NULL;
  (*head)->branch = NULL;

  (*branch_list)->branch = NULL;
  (*branch_list)->next_branch = NULL;
}

void git_checkout(Head *const head, BranchList *const branch_list) {}

void git_log(Head *const head) {
  Commit *current = head->commit;
  if (head->branch == NULL)
    printf("Commit: %s\n", get_hash_string(current->hash));
  else
    printf("Branch: %s\n", head->branch->name);
  while (current != NULL) {
    printf("Message: %s\n", current->message);
    printf("Hash: %s\n", get_hash_string(current->hash));
    current = current->next;
  }
  printf("\n");
}

void git_commit(char *message, Head *const head) {
  Commit *new_commit = malloc(sizeof(Commit));

  strcpy(new_commit->message, message);
  new_commit->hash = generate_hash(message);
  new_commit->next = NULL;
  new_commit->previous = head->commit;

  head->commit->next = new_commit;

  head->branch->commit = new_commit; // Branch se move para o comimt novo
  head->commit = new_commit;         // Head muda para o commit novo
}

void first_commit(char *message, Head *const head,
                  BranchList *const branch_list) {
  head->commit = malloc(sizeof(Commit));
  head->commit->hash = generate_hash(message);
  strcpy(head->commit->message, message);
  head->commit->previous = NULL;
  head->commit->next = NULL;
  git_branch("main", head, branch_list);
  head->branch = branch_list->branch;
}

unsigned char *generate_hash(char *message) {
  unsigned char *hash = malloc(SHA256_DIGEST_LENGTH);
  unsigned char *string_to_hash = generate_string_to_hash(message);
  SHA256(string_to_hash, strlen((char *)string_to_hash), hash);
  return hash;
}

unsigned char *generate_string_to_hash(char *message) {
  time_t current_date;
  time(&current_date);
  unsigned char *string_to_hash =
      malloc(strlen(message) + strlen(ctime(&current_date)) + 1);
  strcpy((char *)string_to_hash, message);
  strcat((char *)string_to_hash, ctime(&current_date));
  return string_to_hash;
}

void list_branches(Head *const head, BranchList *const branch_list) {
  BranchList *current_branch = branch_list;
  while (current_branch) {
    if (head->branch == current_branch->branch)
      printf("* %s\n", current_branch->branch->name);
    else
      printf("%s", current_branch->branch->name);
    current_branch = current_branch->next_branch;
  }
}
