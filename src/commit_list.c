#include "../headers/commit_list.h"
#include <stdio.h>
#include <stdlib.h>


void insert_on_commit_list(CommitList **commit_list, Commit *commit) {
    CommitListNode *new_node = (CommitListNode *)malloc(sizeof(CommitListNode));
    new_node->commit = commit;
    new_node->next = NULL;

    if ((*commit_list)->commit_list_node == NULL) {
        (*commit_list)->commit_list_node = new_node;
        (*commit_list)->tail = new_node;
    } else {
        (*commit_list)->tail->next = new_node;
        (*commit_list)->tail = new_node;
    }

    (*commit_list)->number_nodes++;
}


