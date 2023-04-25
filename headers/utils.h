#include "../headers/git.h"
#include <stdbool.h>
#ifndef UTILS_H
#define UTILS_H

void print_test(Head *const head, BranchList *const branch_list);

void print_hash_string(Head *const head);

char *get_hash_string(unsigned char *hash);

bool is_interactive_mode(char **argv);

bool is_menu_mode(char **argv);

void menu_mode(Head *const head, BranchList *const branch_list);

void interactive_mode(Head *const head, BranchList *const branch_list);

void single_action_mode(char **argv, Head *const head,
                        BranchList *const branch_list);

bool perform_command(Head *const head, BranchList *const branch_list,
                     char *main_command, char **sub_args);

char **get_sub_args(char *command);

char *get_main_command(char *command);

char **read_param(int argc, char *argv[]);

#endif // !UTILS_H
