#ifndef COMMIT_LIST_H
#define COMMIT_LIST_H

#include "../headers/git.h"

typedef struct commitListNode{
	Commit * commit;
	struct commitListNode *next;
} CommitListNode;

typedef struct commitList{
	CommitListNode *commit_list_node;
	int number_nodes;
	CommitListNode *tail;
} CommitList;


void insert_on_commit_list(CommitList **commit_list, Commit *commit); 

#endif // !DEBUG
