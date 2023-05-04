#include "../headers/git.h"
#include <stdbool.h>
#ifndef UTILS_H
#define UTILS_H

void print_test(Head *const head, BranchList *const branch_list);

char *get_hash_string(unsigned char *hash);

bool is_interactive_mode(char **argv);

bool is_menu_mode(char **argv);

void menu_mode(Head *const head, BranchList *const branch_list);

void interactive_mode(char **argv, Head *const head,
                      BranchList *const branch_list);

void single_action_mode(char **argv, Head *const head,
                        BranchList *const branch_list);

Branch * search_on_branch_list(BranchList *const branch_list ,char* branch_name);

char *read_param(char *param, char *argv);

char *get_main_command(char *args);

char *get_command_arguments(char *main_command, char * args);

bool handle_command(char *command, char *command_arguments, Head *const head,
                    BranchList *const branch_list);

#endif // !UTILS_H
