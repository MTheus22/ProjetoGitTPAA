#ifndef GIT_H
#define GIT_H

#include <stdbool.h>

typedef struct commitsTable CommitsTable;

typedef struct commit {
  unsigned char *hash;
  char message[100];
  int commits_pointed; // numero de commits apontados pelo nó
  struct commit **previous_commits;
} Commit;

typedef struct branch {
  char name[50];
  Commit *commit;
} Branch;

typedef struct branchList {
  Branch *branch;
  struct branchList *next_branch;
} BranchList;

typedef struct head {
  Branch *branch;
  Commit *commit;
} Head;

typedef struct error {
  bool is_error;
  char error_log[100];
} Status;

void git_init(Head **head, BranchList **branch_list,
              CommitsTable **commits_table);

void git_branch(char *name, Head *const head, BranchList *const branch_list);

void insert_branch_list(BranchList *const branch_list, Branch *new_branch);

void initialize_branch_list(BranchList *const branch_list, Branch *new_branch);

void git_commit(char *message, Head *const head, CommitsTable *commits_table);

Status git_checkout(Head *const head, BranchList *const branch_list,
                  unsigned char *hash, char *branch_name,
                  CommitsTable *commits_table);

void git_log(Head *const head, CommitsTable *commits_table);

void print_commit(Commit *commit, CommitsTable *commits_table);

void first_commit(char *message, Head *const head,
                  BranchList *const branch_list, CommitsTable *commits_table);

unsigned char *generate_hash(char *message);

unsigned char *generate_string_to_hash(char *message);

void list_branches(Head *const head, BranchList *const branch_list);

#endif
