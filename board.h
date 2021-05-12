/**
 * @file board.h
 * @brief Header file for data types and function prototypes for the Board
 */
#ifndef BOARD_H
#define BOARD_H

/** Cell can be represented either as DEAD or ALIVE */
typedef enum { DEAD, ALIVE } Cell;

/** Board sturct containing height, width and the 2D array of cells*/
typedef struct {
  int height;  /**< Represents height of the board */
  int width;   /**< Represents width of the board */
  Cell **cell; /**< 2D array of cells that are layed on the board and
                  represented either DEAD or ALIVE*/
} Board;

Board *B_new(int height, int width);
Board *B_update(Board *board);
Board *B_reset(Board *board);
void B_destroy(Board *board);
void B_print(Board *board);
static int _count_alive_neighbours(Board *board, int i, int j);
static int _is_alive(Cell c);
void copy_board(Board *dest, Board *src);

#endif