#include "../headers/git.h"
#ifndef UTILS_H
#define UTILS_H

void print_test(Head *const head, BranchList *const branch_list);

char *get_hash_string(unsigned char *hash);

int is_interactive_mode(char **argv);

int is_menu_mode(char **argv);

void menu_mode(Head *const head, BranchList *const branch_list);

void interactive_mode(char **argv, Head *const head,
                      BranchList *const branch_list);

void single_action_mode(char **argv, Head *const head,
                        BranchList *const branch_list);

char **read_param(int argc, char *argv[]);

#endif // !UTILS_H
