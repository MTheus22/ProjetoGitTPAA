#ifndef UTILS_H
#define UTILS_H
#include "../headers/git.h"
#include "../headers/hash_table.h"
#include <stdbool.h>

void print_test();

char *get_hash_string(unsigned char *hash);

bool hash_compare(unsigned char *hash1, unsigned char *hash2);

bool is_interactive_mode(char **argv);

bool is_menu_mode(char **argv);

void menu_mode();

void interactive_mode();

void single_action_mode(char **argv);

Branch *search_on_branch_list(BranchList *const branch_list, char *branch_name);

char *read_param(char *param, char *argv);

char *get_main_command(char *args);

char *get_command_arguments(char *main_command, char *args);

bool handle_command(char *command, char *command_arguments);

#endif // !UTILS_H
