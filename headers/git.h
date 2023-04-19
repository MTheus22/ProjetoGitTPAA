#ifndef GIT_H
#define GIT_H

typedef struct list {
  unsigned char *hash;
  char message[100];
  struct list *next;
  struct list *previous;
} Commit;

typedef struct branch {
  char name[50];
  Commit *commit;
} Branch;

typedef struct branchList {
  Branch *branch;
  Branch *next_branch;
  Branch *previous_branch;
} BranchList;

typedef struct head {
  Branch *branch;
  Commit *commit;
} Head;

void git_init(Head ** head, BranchList **branch_list);

void git_branch(char *name, Head *head);

void git_commit(char *message, Head* const head);

void first_commit(char *message, Head* const head);

unsigned char *generate_hash(char *message);

unsigned char *generate_string_to_hash(char *message);

#endif
