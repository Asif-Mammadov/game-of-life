/**
 * @file main.c
 * @brief Main source file for step 1 in game-of-life
 */

#include "ansi.h"
#include "board.h"
#include <stdio.h>

#define BOARD_WIDTH (5)  /**< The width of the board */
#define BOARD_HEIGHT (5) /**< The height of the board */

int main() {
  setup_console();

  Board *board = B_new(BOARD_HEIGHT, BOARD_WIDTH);

  // Example of cell at (2, 2) with 3 neighbours.
  board->cell[1][1] = ALIVE;
  board->cell[1][3] = ALIVE;
  board->cell[2][2] = ALIVE;
  board->cell[3][3] = ALIVE;

  Board *new_board;
  for (int i = 0; i < 5; i++) {
    printf("(t : %d)\n", i);
    B_print(board);
    printf("\n");
    new_board = B_update(board);
    B_destroy(board);
    board = new_board;
  }
  B_destroy(new_board);

  restore_console();

  return 0;
}
