/**
 * @file main.c
 * @brief Main source file for step 1 in game-of-life
 */

#include <stdio.h>
#include "ansi.h"

#define BOARD_WIDTH (5) /**< The width of the board */
#define BOARD_HEIGHT (5) /**< The height of the board */

typedef enum { DEAD, ALIVE } Cell;

void update_board(Cell board[][BOARD_WIDTH]);
void print_board(Cell board[][BOARD_WIDTH]);
int count_alive_neighbours(Cell board[][BOARD_WIDTH], int i, int j);
int is_alive(Cell c);
void reset_board(Cell board[][BOARD_WIDTH]);
void copy_board(Cell dest_board[][BOARD_WIDTH], Cell src_board[][BOARD_WIDTH]);

int main() {
  setup_console();

  Cell board[BOARD_HEIGHT][BOARD_WIDTH];
  reset_board(board);

  // Example of cell at (2, 2) with 3 neighbours.  
  board[1][1] = ALIVE;
  board[1][3] = ALIVE;
  board[2][2] = ALIVE;
  board[3][3] = ALIVE;

  for (int i = 0; i < 5; i++) {
    printf("(t : %d)\n", i);
    print_board(board);
    printf("\n");
    update_board(board);
  }

  restore_console();

  return 0;
}

/**
 * Updates the board to the next time unit t + 1
 * @param board 2D array of cells that needs to be updated
 */
void update_board(Cell board[][BOARD_WIDTH]) {
  int alive_neighbours;
  Cell new_board[BOARD_HEIGHT][BOARD_WIDTH];
  reset_board(new_board);
  for (int i = 0; i < BOARD_HEIGHT; i++) {
    for (int j = 0; j < BOARD_WIDTH; j++) {
      alive_neighbours = count_alive_neighbours(board, i, j);
      // Dead cell becomes alive if it has 3 alive neighbours
      if (alive_neighbours == 3)
        new_board[i][j] = ALIVE;
      // Alive cell is still alive if it has 2 alive neighbours
      else if (alive_neighbours == 2 && is_alive(board[i][j]))
        new_board[i][j] = ALIVE;
      else
        new_board[i][j] = DEAD;
    }
  }
  copy_board(board, new_board);
}

/**
 * Prints the cell values in board to the terminal as a grid with rows and
 * columns.
 * @param board The 2D array of cells
 */
void print_board(Cell board[][BOARD_WIDTH]) {
  for (int i = 0; i < BOARD_HEIGHT; i++) {
    for (int j = 0; j < BOARD_WIDTH; j++) {
      if (is_alive(board[i][j]))
        set_backgound_color(RED_BKG);
      else
        set_backgound_color(WHITE_BKG);

      // Print cell and reset color
      printf("  ");
      reset_color();
    }
    printf("\n");
  }
}

/**
 * Counts the alive cells that are neighbouring with provided cell
 * @param board The board of the cell defined as 2D array
 * @param i The row (x) coordinate of the cell
 * @param j The column (y) coordinate of the cell
 * @return The number of alive neighbouring cells
 */
int count_alive_neighbours(Cell board[][BOARD_WIDTH], int i, int j) {
  int count = 0;

  // We consider that the grid is infinite
  // If we check the border cell, we need to check the opposite edge too.
  if (i == 0)
    i = BOARD_HEIGHT;
  if (j == 0)
    j = BOARD_WIDTH;

  // List of neighbours of the given cell
  Cell neighbours[] = {
    board[i - 1][j - 1],
    board[i - 1][j % BOARD_WIDTH],
    board[i - 1][(j + 1) % BOARD_WIDTH],
    board[i % BOARD_HEIGHT][j - 1],
    board[i % BOARD_HEIGHT][(j + 1) % BOARD_WIDTH],
    board[(i + 1) % BOARD_HEIGHT][j - 1],
    board[(i + 1) % BOARD_HEIGHT][j % BOARD_WIDTH],
    board[(i + 1) % BOARD_HEIGHT][(j + 1) % BOARD_WIDTH]
  };

  // Iterate through the neighbours and count alive ones
  for (int k = 0; k < 8; k++) {
    if(is_alive(neighbours[k]))
      count++;
  }

  return count;
}

/**
 * Checks if the cell is alive
 * @param c Cell type that can be either DEAD or ALIVE
 * @return 1 If the cell is alive. Otherwise return 0.
 */
int is_alive(Cell c) {
  return (c == ALIVE);
}

/**
 * Makes all the cells in the board DEAD
 * @param board The 2D array of cells that needs to be reset
 */
void reset_board(Cell board[][BOARD_WIDTH]) {
  for (int i = 0; i < BOARD_HEIGHT; i++)
    for (int j = 0; j < BOARD_WIDTH; j++)
      board[i][j] = DEAD;
}

/**
 * Copies the cell values from one board to another
 * @param dest_board 2D array where the values of src_board are copied
 * @param src_board 2D array. The values will be copied to the dest_board
 */
void copy_board(Cell dest_board[][BOARD_WIDTH], Cell src_board[][BOARD_WIDTH]) {
  for (int i = 0; i < BOARD_HEIGHT; i++)
    for (int j = 0; j < BOARD_WIDTH; j++)
      dest_board[i][j] = src_board[i][j];
}
