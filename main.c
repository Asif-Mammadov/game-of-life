/**
 * @file main.c
 * @brief Main source file for step 1 in game-of-life
 */

#include "board.h"
#include "gui.h"
#include <ansi.h>
#include <bits/getopt_core.h>
#include <board.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define BOARD_WIDTH_TERM (10) /**< The default width of the board in           \
                                 terminal*/
#define BOARD_HEIGHT_TERM                                                      \
  (10) /**< The default height of the board in terminal*/

#define BOARD_WIDTH_GUI (100)  /**< The default width of the board in gui */
#define BOARD_HEIGHT_GUI (100) /**< The default height of the board in gui */

/**
 * Types of the game that can be played.
 */
typedef enum {
  TERM, /**< The terminal typ */
  GUI   /**< The gui type */
} Type;

void ansi_display(Board *board);
void usageError(char *progName);
int main(int argc, char **argv) {
  int opt;
  int vflag = 0;
  Version v;
  // set terminal type by default
  Type type = TERM;

  char *version_names[2] = {"circular", "clipped"};
  // if no arguments are given
  if (argc == 1)
    usageError(argv[0]);

  // check for -v
  while ((opt = getopt(argc, argv, "v:t:")) != -1) {
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
    case 't':
      if (strcmp("gui", optarg) == 0 && strlen(optarg) == strlen("gui")) {
        type = GUI;
      } else if (strcmp("terminal", optarg) == 0 &&
                 strlen(optarg) == strlen("terminal")) {
        type = TERM;
      } else
        fprintf(stderr, "Wrong option value for %c. Use either %s or %s.\n",
                opt, "terminal", "gui");
      break;
    default:
      usageError(argv[0]);
      break;
    }
  }
  // check if -v was not included
  if (!vflag) {
    usageError(argv[0]);
  }

  if (type == TERM) {
    Board *board = B_new(BOARD_HEIGHT_TERM, BOARD_WIDTH_TERM, v);
    board = B_generate(board, 33);
    ansi_display(board);
  } else if(type == GUI){
    Board *board = B_new(BOARD_HEIGHT_GUI, BOARD_WIDTH_GUI, v);
    board = B_generate(board, 33);
    gui_display(board);
  }

  // Generate board with 33% probability of cells being alive
  return 0;
}

void usageError(char *progName) {
  fprintf(stderr, "Usage: %s -v <version>\n", progName);
  exit(EXIT_FAILURE);
}

/** 
 * Displays the board on the terminal
 * @param board pointer to Board structure
 */
void ansi_display(Board *board) {
  setup_console();

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
}
