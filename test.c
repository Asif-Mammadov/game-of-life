#include "CUnit/Basic.h"
#include "board/board.h"
#include <CUnit/CUError.h>
#include <CUnit/TestDB.h>
#include <board.h>

#define BOARD_HEIGHT (6)
#define BOARD_WIDTH (6)

/**
 * Compares the cell values of two boards. If equal returns 1.
 * @param b1 First board
 * @param b2 Second board
 */
int board_compare(Board *b1, Board *b2) {
  if (b1->height != b2->height || b1->width != b2->width)
    return 0;
  for (int i = 0; i < b1->height; i++) {
    for (int j = 0; j < b1->width; j++) {
      if (b1->cell[i][j] != b2->cell[i][j])
        return 0;
    }
  }
  return 1;
}

/** Test only one cell without any neighbours */
void test_lone_cell(void){
  Board *b_actual = B_new(BOARD_HEIGHT, BOARD_WIDTH, CIRCULAR);
  B_set_alive(b_actual, 2, 2);
  b_actual =  B_update(b_actual);

  CU_ASSERT_FALSE(B_is_alive(b_actual->cell[2][2]))
}

// Test the block position 
void test_still_block(void) {
  Board *b_actual = B_new(BOARD_HEIGHT, BOARD_WIDTH, CIRCULAR);
  Board *b_expect = B_new(BOARD_HEIGHT, BOARD_WIDTH, CIRCULAR);

  B_set_alive(b_actual, 1, 1);
  B_set_alive(b_actual, 1, 2);
  B_set_alive(b_actual, 2, 1);
  B_set_alive(b_actual, 2, 2);

  b_actual = B_update(b_actual);

  B_set_alive(b_expect, 1, 1);
  B_set_alive(b_expect, 1, 2);
  B_set_alive(b_expect, 2, 1);
  B_set_alive(b_expect, 2, 2);

  CU_ASSERT(board_compare(b_actual, b_expect));
  b_actual = B_update(b_actual);
  CU_ASSERT(board_compare(b_actual, b_expect));
}

/** Test the blinker oscillation */
void test_blinker(void) {
  Board *b_actual = B_new(BOARD_HEIGHT, BOARD_WIDTH, CIRCULAR);
  Board *b_expect = B_new(BOARD_HEIGHT, BOARD_WIDTH, CIRCULAR);

  B_set_alive(b_actual, 2, 1);
  B_set_alive(b_actual, 2, 2);
  B_set_alive(b_actual, 2, 3);

  b_actual = B_update(b_actual);

  B_set_alive(b_expect, 1, 2);
  B_set_alive(b_expect, 2, 2);
  B_set_alive(b_expect, 3, 2);

  CU_ASSERT(board_compare(b_actual, b_expect));

  // Make one period
  b_actual = B_update(b_actual);
  b_actual = B_update(b_actual);
  CU_ASSERT(board_compare(b_actual, b_expect));
}

/** test the toad oscillation */
void test_toad (){
  Board *b_actual = B_new(BOARD_HEIGHT, BOARD_WIDTH, CIRCULAR);
  Board *b_expect = B_new(BOARD_HEIGHT, BOARD_WIDTH, CIRCULAR);

  B_set_alive(b_actual, 2, 1);
  B_set_alive(b_actual, 2, 2);
  B_set_alive(b_actual, 2, 3);
  B_set_alive(b_actual, 3, 0);
  B_set_alive(b_actual, 3, 1);
  B_set_alive(b_actual, 3, 2);

  b_actual = B_update(b_actual);

  B_set_alive(b_expect, 2, 1);
  B_set_alive(b_expect, 3, 1);
  B_set_alive(b_expect, 4, 2);
  B_set_alive(b_expect, 1, 3);
  B_set_alive(b_expect, 2, 4);
  B_set_alive(b_expect, 3, 4);
  CU_ASSERT(board_compare(b_actual, b_expect));

  // Make one period
  b_actual = B_update(b_actual);
  b_actual = B_update(b_actual);
  CU_ASSERT(board_compare(b_actual, b_expect));

}
void test_circular_box(){
  Board *b_actual = B_new(BOARD_HEIGHT, BOARD_WIDTH, CIRCULAR);
  Board *b_expect = B_new(BOARD_HEIGHT, BOARD_WIDTH, CIRCULAR);

  B_set_alive(b_actual, 0, 0);
  B_set_alive(b_actual, 0, 1);
  B_set_alive(b_actual, b_actual->height - 1, 0);
  B_set_alive(b_actual, b_actual->height - 1, 1);

  b_actual = B_update(b_actual);
  
  B_set_alive(b_expect, 0, 0);
  B_set_alive(b_expect, 0, 1);
  B_set_alive(b_expect, b_expect->height - 1, 0);
  B_set_alive(b_expect, b_expect->height - 1, 1);

  CU_ASSERT(board_compare(b_actual, b_expect));
}

int main(int argc, char **argv) {

  if (CU_initialize_registry() != CUE_SUCCESS)
    return CU_get_error();

  // Add suite
  CU_pSuite suite1 = CU_add_suite("board", NULL, NULL);
  if (suite1 == NULL) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (CU_add_test(suite1, "Testing if lone cell dies", test_lone_cell) == NULL) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (CU_add_test(suite1, "Testing if still block", test_still_block) == NULL) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if(CU_add_test(suite1, "Testing if blinker works", test_blinker) == NULL) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if(CU_add_test(suite1, "Testing if toad works", test_blinker) == NULL) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if(CU_add_test(suite1, "Testing if box in circular works", test_circular_box) == NULL) {
    CU_cleanup_registry();
    return CU_get_error();
  }
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();  
  CU_cleanup_registry(); 
  return CU_get_number_of_failures();
}