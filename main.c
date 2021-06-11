/**
 * @file main.c
 * @brief Main source file for step 1 in game-of-life
 */

#include "board.h"
#include <ansi.h>
#include <bits/getopt_core.h>
#include <board.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define BOARD_WIDTH (5)  /**< The width of the board */
#define BOARD_HEIGHT (5) /**< The height of the board */

void usageError(char *progName);

int main(int argc, char **argv) {
  int opt;
  int vflag = 0;
  Version v;

  char *version_names[2] = {"circular", "clipped"};
  // if no arguments are given
  if (argc == 1)
    usageError(argv[0]);

  // check for -v 
  while ((opt = getopt(argc, argv, "v:")) != -1) {
    switch (opt) {
    case 'v':
      // Set version to circular
      if (strcmp(version_names[0], optarg) == 0 &&
          strlen(optarg) == strlen(version_names[0])) {
        v = CIRCULAR;
        vflag = 1;
      }
      // Set version to clipped
      else if (strcmp(version_names[1], optarg) == 0 &&
               strlen(optarg) == strlen(version_names[1])) {
        v = CLIPPED;
        vflag = 1;
      }
      // Print error message
      else
        fprintf(stderr, "Wrong option value for %c. Use either %s or %s.\n",
                opt, version_names[0], version_names[1]);
      break;
    default:
      usageError(argv[0]);
      break;
    }
  }
  // check if -v was included
  if (!vflag) {
    usageError(argv[0]);
  }
  setup_console();

  Board *board = B_new(BOARD_HEIGHT, BOARD_WIDTH, v);

  // Generate board with 33% probability of cells being alive
  board = B_generate(board, 33);

  Board *new_board;
  int i = 0;
  while (1) {
    clean();
    printf("(t : %d)\n", i++);
    B_print(board);
    printf("\n");
    new_board = B_update(board);
    B_destroy(board);
    board = new_board;
    sleep(1);
  }
  B_destroy(new_board);

  restore_console();

  return 0;
}

void usageError(char *progName) {
  fprintf(stderr, "Usage: %s -v <version>\n", progName);
  exit(EXIT_FAILURE);
}
