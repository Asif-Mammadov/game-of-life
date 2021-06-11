/**
 * @file ansi.c
 * @brief Source file for configuration of console for different OS and
 * ANSI coloring functions
 */

#ifdef _WIN32
#define  _CRT_SECURE_NO_WARNINGS 1
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
// Some old MinGW/CYGWIN distributions don't define this:
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING  0x0004
#endif

static HANDLE stdoutHandle, stdinHandle;
static DWORD outModeInit, inModeInit;

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

/**
 * Setup the console to be able to use ANSI escape codes in Windows
 */
void setup_console() {
    DWORD outMode = 0, inMode = 0;
    stdoutHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    stdinHandle = GetStdHandle(STD_INPUT_HANDLE);

    if(stdoutHandle == INVALID_HANDLE_VALUE || stdinHandle == INVALID_HANDLE_VALUE) {
        exit(GetLastError());
    }
    
    if(!GetConsoleMode(stdoutHandle, &outMode) || !GetConsoleMode(stdinHandle, &inMode)) {
        exit(GetLastError());
    }

    outModeInit = outMode;
    inModeInit = inMode;
    
    // Enable ANSI escape codes
    outMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

    // Set stdin as no echo and unbuffered
    inMode &= ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT);

    if(!SetConsoleMode(stdoutHandle, outMode) || !SetConsoleMode(stdinHandle, inMode)) {
        exit(GetLastError());
    }    
}

/**
 * Set console config to default for Windows
 */
void restore_console() {
    // Reset colors
    printf("\x1b[0m");    
    
    // Reset console mode
    if(!SetConsoleMode(stdoutHandle, outModeInit) || !SetConsoleMode(stdinHandle, inModeInit)) {
        exit(GetLastError());
    }
}
#else

static struct termios orig_term;
static struct termios new_term;

/**
 * Setup console for MacOS and Linux
 */
void setup_console() {
    tcgetattr(STDIN_FILENO, &orig_term);
    new_term = orig_term;

    new_term.c_lflag &= ~(ICANON | ECHO);

    tcsetattr(STDIN_FILENO, TCSANOW, &new_term);
}

/**
 * Set console config to default for MacOS and Linux
 */
void restore_console() {
    // Reset colors
    printf("\x1b[0m");

    // Reset console mode
    tcsetattr(STDIN_FILENO, TCSANOW, &orig_term);
}
#endif