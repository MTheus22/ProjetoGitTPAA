#include <stdbool.h>
#ifndef GIT_H
#define GIT_H

typedef struct commit {
  unsigned char *hash;
  char message[100];
  struct commit *next;
  struct commit *previous;
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

typedef struct error{
  bool is_error;
  char error_log[100];
} Error;

void git_init(Head **head, BranchList **branch_list);

void git_branch(char *name, Head *const head, BranchList *const branch_list);

void insert_branch_list(BranchList *const branch_list, Branch *new_branch);

void initialize_branch_list(BranchList *const branch_list, Branch *new_branch);

void git_commit(char *message, Head *const head);

void git_checkout(Head *const head, BranchList *const branch_list);

void git_log(Head *const head);

void first_commit(char *message, Head *const head,
                  BranchList *const branch_list);

unsigned char *generate_hash(char *message);

unsigned char *generate_string_to_hash(char *message);

void list_branches(Head *const head, BranchList *const branch_list);

#endif
