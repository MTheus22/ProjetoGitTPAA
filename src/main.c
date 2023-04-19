#include <stdio.h>
#include <stdlib.h>
#include "../headers/utils.h"
#include "../headers/git.h"

#define TESTMODE 1

int main(int argc, char *argv[]) {
  Head* temp_head;
  BranchList* temp_branch_list;

  git_init(&temp_head,&temp_branch_list);

  Head* const head = temp_head;
  BranchList* const branch_list = temp_branch_list;
  temp_head = NULL;
  temp_branch_list = NULL;

  if(TESTMODE)
	  print_test(head);

  return EXIT_SUCCESS;
}
