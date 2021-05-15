/**
 * @file main.c
 * @brief Main source file for step 1 in game-of-life
 */

#include "ansi.h"
#include "board.h"
#include <stdio.h>
#include <unistd.h>

#define BOARD_WIDTH (5)  /**< The width of the board */
#define BOARD_HEIGHT (5) /**< The height of the board */

int main() {
  setup_console();

  Board *board = B_new(BOARD_HEIGHT, BOARD_WIDTH);

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
