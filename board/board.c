/**
 * @file board.c
 * @brief Contains functions related to interactions with the Board
 */
#include <ansi.h>
#include <board.h>
#include <stdlib.h>
#include <time.h>
/**
 * Creates new reset (all cells are dead) board
 * @param height Heigth of the board
 * @param width Width of the board
 * @return Pointer to the board structure
 */
Board *B_new(int height, int width, Version version) {
  Board *board = (Board *)malloc(sizeof(Board));
  board->height = height;
  board->width = width;
  board->version = version;
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
  int alive_neighbours[board->height][board->width];
  Board *new_board = B_new(board->height, board->width, board->version);

  for (int i = 0; i < board->height; i++) {
    for (int j = 0; j < board->width; j++) {
      alive_neighbours[i][j] = _count_alive_neighbours(board, i, j);
    }
  }
  for (int i = 0; i < board->height; i++) {
    for (int j = 0; j < board->width; j++) {
      // Dead cell becomes alive if it has 3 alive neighbours
      if (alive_neighbours[i][j] == 3)
        B_set_alive(new_board, i, j);
      // Alive cell is still alive if it has 2 alive neighbours
      else if (alive_neighbours[i][j] == 2 && B_is_alive(board->cell[i][j]))
        B_set_alive(new_board, i, j);
      else
        B_set_dead(new_board, i, j);
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
      B_set_dead(board, i, j);
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

  // List of neighbours of the given cell

  if (board->version == CIRCULAR) {
    if (i == 0)
      i = height;
    if (j == 0)
      j = width;
    Cell neighbours_circle[] = {board->cell[i - 1][j - 1],
                                board->cell[i - 1][j % width],
                                board->cell[i - 1][(j + 1) % width],
                                board->cell[i % height][j - 1],
                                board->cell[i % height][(j + 1) % width],
                                board->cell[(i + 1) % height][j - 1],
                                board->cell[(i + 1) % height][j % width],
                                board->cell[(i + 1) % height][(j + 1) % width]};

    // We consider that the grid is infinite
    // If we check the border cell, we need to check the opposite edge too.

    // Iterate through the neighbours and count alive ones
    for (int k = 0; k < 8; k++) {
      if (B_is_alive(neighbours_circle[k]))
        count++;
    }
  } else if (board->version == CLIPPED) {
    // CLIPPED version
    if (i != 0) {
      if (j != 0)
        if (B_is_alive(board->cell[i - 1][j - 1]))
          count++;
      if (B_is_alive(board->cell[i - 1][j]))
        count++;
      if (j != width - 1)
        if (B_is_alive(board->cell[i - 1][j + 1]))
          count++;
    }
    if (j != 0)
      if (board->cell[i][j - 1])
        count++;
    if (j != width - 1)
      if (B_is_alive(board->cell[i][j + 1]))
        count++;

    if (i != height - 1) {
      if (j != 0)
        if (B_is_alive(board->cell[i + 1][j - 1]))
          count++;

      if (B_is_alive(board->cell[i + 1][j]))
        count++;
      if (j != width - 1)
        if (B_is_alive(board->cell[i + 1][j + 1]))
          count++;
    }
  }
  return count;
}

/**
 * Checks if the cell is alive
 * @param c Cell type that can be either DEAD or ALIVE
 * @return 1 If the cell is alive. Otherwise return 0.
 */
int B_is_alive(Cell c) { return (c == ALIVE); }

/**
 * Prints the cell values in board to the terminal as a grid with rows and
 * columns.
 * @param board The 2D array of cells
 */
void B_print(Board *board) {
  for (int i = 0; i < board->height; i++) {
    for (int j = 0; j < board->width; j++) {
      if (B_is_alive(board->cell[i][j]))
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
 * @param board Pointer to struct board
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

/**
 * Generates random arrangement of dead and alive cells of given board.
 * @param board Pointer to struct board
 * @param p Probability of cell being alive. Range of p is [0; 100]. Otherwise
 * print error to console and terminate the execution.
 * @return Pointer to struct board
 */
Board *B_generate(Board *board, int p) {
  if (p < 0 || p > 100) {
    printf("Probability should be between 0 and 100");
    exit(1);
  }
  srand((unsigned)time(NULL));
  int d;
  for (int i = 0; i < board->height; i++) {
    for (int j = 0; j < board->width; j++) {
      d = rand() % 100;
      if (d < p)
        B_set_alive(board, i, j);
      else
        B_set_dead(board, i, j);
    }
  }
  return board;
}

/**
 * Makes the cell at given coordinates dead
 * @param board Pointer to struct board
 * @param row integer representing the row coordinate of the cell
 * @param col integer representing the column coordinate of the cell
 */
void B_set_dead(Board *board, int row, int col) {
  board->cell[row][col] = DEAD;
}

/**
 * Makes the cell at given coordinates alive
 * @param board Pointer to struct board
 * @param row integer representing the row coordinate of the cell
 * @param col integer representing the column coordinate of the cell
 */
void B_set_alive(Board *board, int row, int col) {
  board->cell[row][col] = ALIVE;
}