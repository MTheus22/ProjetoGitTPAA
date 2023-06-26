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
  else{
  Branch *new_branch = malloc(sizeof(Branch));
  strcpy(new_branch->name, name);
  new_branch->commit = head->commit;
  if (branch_list->branch == NULL)
    initialize_branch_list(branch_list, new_branch);
  else
    insert_branch_list(branch_list, new_branch);
  }
}

void list_branches(Head *const head, BranchList *const branch_list) {
  if(!branch_list->branch)
	  return;
  BranchList *current_branch = branch_list;
  while (current_branch) {
    if (head->branch == current_branch->branch)
      printf("* %s\n", current_branch->branch->name);
    else
      printf("%s\n", current_branch->branch->name);
    current_branch = current_branch->next_branch;
  }
}

void initialize_branch_list(BranchList *const branch_list, Branch *new_branch) {
  branch_list->next_branch = NULL;
  branch_list->branch = new_branch;
}

void insert_branch_list(BranchList *const branch_list, Branch *new_branch) {
  BranchList *last_node = branch_list;
  while (last_node->next_branch)
    last_node = last_node->next_branch;
  last_node->next_branch = malloc(sizeof(BranchList));
  last_node->next_branch->branch = new_branch;
  last_node->next_branch->next_branch = NULL;
}

void git_init(Head **head, BranchList **branch_list) {
  *head = malloc(sizeof(Head));
  *branch_list = malloc(sizeof(BranchList));

  (*head)->commit = NULL;
  (*head)->branch = NULL;

  (*branch_list)->branch = NULL;
  (*branch_list)->next_branch = NULL;
}

void git_checkout(Head *const head, BranchList *const branch_list, char* branch_name, CommitsTable *commits_table) {
	Branch *branch_searched = search_on_branch_list(branch_list,branch_name);
	if(branch_searched){
		head->branch = branch_searched;
		head->commit = branch_searched->commit;
	}
}

void git_log(Head *const head, CommitsTable *commits_table) {
  if(head->branch->commit == NULL && head->commit == NULL){
	  printf("Não existe nenhum commit, faça um commit antes de usar o git log");
	  return;
  }
  Commit *current = head->commit;
  if (head->branch == NULL)
    printf("--- Deatached state ---\n");
  else
    printf("--- Branch: %s ---\n", head->branch->name);
  print_commit(head->commit, commits_table);
}

void print_commit(Commit *commit, CommitsTable *commits_table){
	CommitsListNode *node = get_node_from_commits_list_table(commits_table, commit->hash);
	if(node->visited)
		return;
    printf("Message: %s\n", commit->message);
    printf("Hash: %s\n", get_hash_string(commit->hash));
	node->visited = true;
	for(int i=0; i < commit->commits_pointed; i++)
		print_commit(*(commit->previous_commits + i), commits_table);
	node->visited = false;
}

void git_commit(char *message, Head *const head, CommitsTable *commits_table) {
  Commit *new_commit = malloc(sizeof(Commit));
  new_commit->commits_pointed = 1;
  new_commit->previous_commits = malloc(sizeof(Commit *) * new_commit->commits_pointed);
  strcpy(new_commit->message, message);
  new_commit->hash = generate_hash(message);
  *new_commit->previous_commits = head->commit;
  insert_commit_in_table(commits_table, new_commit);

  head->branch->commit = new_commit; // Branch se move para o comimt novo
  head->commit = new_commit;         // Head muda para o commit novo
}

void first_commit(char *message, Head *const head,
                  BranchList *const branch_list, CommitsTable *commits_table) {
  head->commit = malloc(sizeof(Commit));
  head->commit->hash = generate_hash(message);
  strcpy(head->commit->message, message);
  head->commit->previous_commits = NULL;
  head->commit->commits_pointed = 0;
  git_branch("main", head, branch_list);
  head->branch = branch_list->branch;
  insert_commit_in_table(commits_table, head->commit);
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
