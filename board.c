/**
 * @file board.c
 * @brief Contains functions related to interactions with the Board
 */
#include "board.h"
#include "ansi.h"
#include <stdlib.h>
/**
 * Creates new reset (all cells are dead) board
 * @param height Heigth of the board
 * @param width Width of the board
 * @return Pointer to the board structure
 */
Board *B_new(int height, int width) {
  Board *board = (Board *)malloc(sizeof(Board));
  board->height = height;
  board->width = width;
  board->cell = (Cell **)malloc(height * sizeof(Cell *));
  for (int i = 0; i < height; i++) {
    board->cell[i] = (Cell *)malloc(width * sizeof(Cell));
  }
  return B_reset(board);
}

/**
 * Updates the board to the next time unit t + 1
 * @param board Pointer to the struct Board to be updated
 * @return Pointer to the new struct Board with updated cell values
 */
Board *B_update(Board *board) {
  int alive_neighbours;
  Board *new_board = B_new(board->height, board->width);
  for (int i = 0; i < board->height; i++) {
    for (int j = 0; j < board->width; j++) {
      alive_neighbours = _count_alive_neighbours(board, i, j);
      // Dead cell becomes alive if it has 3 alive neighbours
      if (alive_neighbours == 3)
        new_board->cell[i][j] = ALIVE;
      // Alive cell is still alive if it has 2 alive neighbours
      else if (alive_neighbours == 2 && _is_alive(board->cell[i][j]))
        new_board->cell[i][j] = ALIVE;
      else
        new_board->cell[i][j] = DEAD;
    }
  }
  return new_board;
}

/**
 * Makes all the cells in the board DEAD
 * @param board pointer to Board structure
 * @return poitner to Board structure with reset cells (all cells are DEAD)
 */
Board *B_reset(Board *board) {
  for (int i = 0; i < board->height; i++)
    for (int j = 0; j < board->width; j++)
      board->cell[i][j] = DEAD;
  return board;
}

/**
 * Counts the alive cells that are neighbouring with provided cell
 * @param board Pointer to the Board structure
 * @param i The row (x) coordinate of the cell
 * @param j The column (y) coordinate of the cell
 * @return The number of alive neighbouring cells
 */
static int _count_alive_neighbours(Board *board, int i, int j) {
  int height = board->height;
  int width = board->width;
  int count = 0;

  // We consider that the grid is infinite
  // If we check the border cell, we need to check the opposite edge too.
  if (i == 0)
    i = height;
  if (j == 0)
    j = width;

  // List of neighbours of the given cell
  Cell neighbours[] = {board->cell[i - 1][j - 1],
                       board->cell[i - 1][j % width],
                       board->cell[i - 1][(j + 1) % width],
                       board->cell[i % height][j - 1],
                       board->cell[i % height][(j + 1) % width],
                       board->cell[(i + 1) % height][j - 1],
                       board->cell[(i + 1) % height][j % width],
                       board->cell[(i + 1) % height][(j + 1) % width]};

  // Iterate through the neighbours and count alive ones
  for (int k = 0; k < 8; k++) {
    if (_is_alive(neighbours[k]))
      count++;
  }

  return count;
}

/**
 * Checks if the cell is alive
 * @param c Cell type that can be either DEAD or ALIVE
 * @return 1 If the cell is alive. Otherwise return 0.
 */
static int _is_alive(Cell c) { return (c == ALIVE); }

/**
 * Prints the cell values in board to the terminal as a grid with rows and
 * columns.
 * @param board The 2D array of cells
 */
void B_print(Board *board) {
  for (int i = 0; i < board->height; i++) {
    for (int j = 0; j < board->width; j++) {
      if (_is_alive(board->cell[i][j]))
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
 * Frees the memory allocated by the given board.
 * @param Pointer to struct board
 */
void B_destroy(Board *board) {
  if (board == NULL) {
    printf("B_destroy: Passed value is NULL\nExiting...\n");
    exit(1);
  }
  for (int i = 0; i < board->height; i++) {
    free(board->cell[i]);
  }
  free(board->cell);
  free(board);
}