/**
 * @file board.h
 * @brief Header file for data types and function prototypes for the Board
 */
#ifndef BOARD_H
#define BOARD_H

/** Cell can be represented either as DEAD or ALIVE */
typedef enum { DEAD, ALIVE } Cell;

/** The board can work either by rules of version CLIPPED (the board is not
 * invinite and the are defined borders) or of version CIRCULAR (the board is
 * infinite and the are no actual borders)  */
typedef enum { CLIPPED, CIRCULAR } Version;

/** Board sturct containing height, width and the 2D array of cells*/
typedef struct {
  int height;      /**< Represents height of the board */
  int width;       /**< Represents width of the board */
  Version version; /**< Represents the rules of the board according to the
                      version as either CLIPPED or CIRCULAR */
  Cell **cell;     /**< 2D array of cells that are layed on the board and
                      represented either DEAD or ALIVE*/
} Board;

Board *B_new(int height, int width, Version version);
Board *B_update(Board *board);
Board *B_reset(Board *board);
Board *B_generate(Board *board, int p);
void B_destroy(Board *board);
void B_print(Board *board);
void B_set_dead(Board *board, int row, int col);
void B_set_alive(Board *board, int row, int col);
int B_is_alive(Cell c);
static int _count_alive_neighbours(Board *board, int i, int j);
#endif