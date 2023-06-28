#ifndef GIT_H
#define GIT_H

#include <stdbool.h>

#define BUFFER_TEXT_LENGTH 100

typedef struct commitsTable CommitsTable;

typedef struct commitList CommitList;

typedef struct commit {
  unsigned char *hash;
  char message[BUFFER_TEXT_LENGTH];
  int commits_pointed; // numero de commits apontados pelo nó
  struct commit **previous_commits;
} Commit;

typedef struct branch {
  char name[BUFFER_TEXT_LENGTH];
  Commit *commit;
} Branch;

typedef struct branchList {
  Branch *branch;
  struct branchList *next_branch;
  int number_branches;
} BranchList;

typedef struct head {
  Branch *branch;
  Commit *commit;
} Head;

typedef struct error {
  bool is_error;
  char error_log[BUFFER_TEXT_LENGTH];
} Status;

void git_init(Head **head, BranchList **branch_list,
              CommitsTable **commits_table);

void git_branch(char *name, Head *const head, BranchList *const branch_list);

void insert_branch_list(BranchList *const branch_list, Branch *new_branch);

void initialize_branch_list(BranchList *const branch_list, Branch *new_branch);

void git_commit(char *message, Head *const head, CommitsTable *commits_table, CommitList **commit_list);

Status git_merge(Head *head, BranchList *branch_list, unsigned char *hash,
                 char *branch_name, CommitsTable *commits_table, CommitList **commit_list); 

Commit *create_commit_and_point_to_two_others(Commit *commit1,
                                              Commit *commit2); 

Status git_checkout(Head *const head, BranchList *const branch_list,
                  unsigned char *hash, char *branch_name,
                  CommitsTable *commits_table);

void git_log(Head *const head, CommitsTable *commits_table);

void print_commit(Commit *commit, CommitsTable *commits_table);

void first_commit(char *message, Head *const head,
                  BranchList *const branch_list, CommitsTable *commits_table, CommitList **commit_list);

void git_push(BranchList *branch_list,CommitList *commit_list);

void insert_branch_data_on_buffer(char *buffer, BranchList *branch_list);

void insert_graph_data_on_buffer(char *buffer, CommitList *commit_list);

void insert_commit_data_on_buffer(char *buffer, CommitList *commit_list);

unsigned char *generate_hash(char *message);

unsigned char *generate_string_to_hash(char *message);

void list_branches(Head *const head, BranchList *const branch_list);

#endif
