#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/git.h"
#include "../headers/utils.h"
#include "../headers/hash_table.h"

#define TESTMODE false

int main(int argc, char *argv[]) {
  if (TESTMODE)
    print_test();
  else if (is_interactive_mode(argv)){
    interactive_mode();
  }
  else if (is_menu_mode(argv))
    menu_mode();
  else
    single_action_mode(argv);
  return EXIT_SUCCESS;
}
