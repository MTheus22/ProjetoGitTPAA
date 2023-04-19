#include "../headers/git.h"
#include <openssl/sha.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void git_branch(char *name, Head *const head) {
  Branch *branch = malloc(sizeof(Branch));
  strcpy(branch->name, name);
  if(head->commit == NULL && head ->branch == NULL)
	  return;
  branch->commit = head->commit; // a nova branch aponta para o commit para o
                                 // qual a head esta apontando
}

void git_init(Head **head, BranchList **branch_list) {
  *head = malloc(sizeof(Head));
  *branch_list = malloc(sizeof(Branch));

  (*head)->commit = NULL;
  (*head)->branch = NULL;

  (*branch_list)->branch = NULL;
  (*branch_list)->next_branch = NULL;
  (*branch_list)->previous_branch = NULL;
}

void git_commit(char *message, Head *const head) {
  if (head->commit == NULL && head->branch == NULL) {
	  printf("Manjericão");
    git_branch("main", head);
	printf("cu");
    first_commit(message, head);
  } else {
    Commit *new_commit = malloc(sizeof(Commit));

    strcpy(new_commit->message, message);
    new_commit->hash = generate_hash(message);
    new_commit->next = NULL;
    new_commit->previous = head->commit;

    head->commit->next = new_commit;

    head->commit = new_commit; // Head muda para o commit novo
  }
}

void first_commit(char *message, Head *const head) {
  head->commit = malloc(sizeof(Commit));
  head->commit->hash = generate_hash(message);
  strcpy(head->commit->message, message);
  head->commit->previous = NULL;
  head->commit->next = NULL;
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
  return (unsigned char *)strcat(message, ctime(&current_date));
}
