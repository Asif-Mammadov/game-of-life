/**
 * @file gui.c
 * @brief Source file for configuration of gui 
*/
#include <SDL2/SDL.h>
#include <assert.h>
#include <board.h>
#include <gui.h>
#include <unistd.h>

#define GLOBAL_HEIGHT 500
#define GLOBAL_WIDTH 500

#define COLOR_ALIVE 0, 0, 0, 255
#define COLOR_DEAD 255, 255, 255, 255

void gui_display(Board *board) {

  SDL_Event event;
  SDL_Window *window = SDL_CreateWindow(
      "Conway's Game of Life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
      GLOBAL_HEIGHT, GLOBAL_WIDTH, SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);

  SDL_Renderer *renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  assert(renderer != NULL);
  int quit = 0;
  while (!quit) {
    for (int i = 0; i < board->height; i++) {
      for (int j = 0; j < board->width; j++) {
        // set cell color depending on its status
        if (B_is_alive(board->cell[i][j]))
          SDL_SetRenderDrawColor(renderer, COLOR_ALIVE);
        else
          SDL_SetRenderDrawColor(renderer, COLOR_DEAD);
        // create rectangle representing cell
        SDL_Rect rect = {
            GLOBAL_HEIGHT / board->height * i, GLOBAL_WIDTH / board->width * j,
            GLOBAL_HEIGHT / board->height, GLOBAL_WIDTH / board->width};
        SDL_RenderFillRect(renderer, &rect);
      }
    }
    SDL_RenderPresent(renderer);
    board = B_update(board);
    sleep(1);
    while (!quit && SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_QUIT:
        quit = 1;
        break;
      }
    }
  }
  SDL_DestroyWindow(window);
  SDL_Quit();
}
