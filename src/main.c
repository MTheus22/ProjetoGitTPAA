#include "../headers/git.h"
#include "../headers/utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TESTMODE true

int main(int argc, char *argv[]) {
  Head *temp_head;
  BranchList *temp_branch_list;

  git_init(&temp_head, &temp_branch_list);

  Head *const head = temp_head;
  BranchList *const branch_list = temp_branch_list;
  temp_head = NULL;
  temp_branch_list = NULL;

  if (TESTMODE)
    print_test(head, branch_list);
  else if (is_interactive_mode(argv))
    interactive_mode(head, branch_list);
  else if (is_menu_mode(argv))
    menu_mode(head, branch_list);
  else
    single_action_mode(argv, head, branch_list);

  return EXIT_SUCCESS;
}
