#include "../headers/git.h"
#ifndef UTILS_H
#define UTILS_H

char ** read_param(int argc, char * argv[]);

int is_interactive_mode(char * argv[]);

void print_test(Head* const head, BranchList* const branch_list);

char * get_hash_string(unsigned char * hash);

#endif // !UTILS_H

