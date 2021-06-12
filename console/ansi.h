/**
 * @file ansi.h
 * @brief Header file for configuration of console for different OS and
 * ANSI coloring functions
 */

#pragma once

#include <stdio.h>
#include<board.h>
/*! Stores ANSI reset, background and text color codes */
enum Colors {
  RESET_COLOR,
  BLACK_TXT = 30,
  RED_TXT,
  GREEN_TXT,
  YELLOW_TXT,
  BLUE_TXT,
  MAGENTA_TXT,
  CYAN_TXT,
  WHITE_TXT,

  BLACK_BKG = 40,
  RED_BKG,
  GREEN_BKG,
  YELLOW_BKG,
  BLUE_BKG,
  MAGENTA_BKG,
  CYAN_BKG,
  WHITE_BKG
};

void setup_console();
void restore_console();
/**
 * Sets the text color of console to given color
 * @param code ANSI code of the color
 */
static inline void set_text_color(int code) { printf("\x1b[%dm", code); }

/**
 * Sets the background color of console to given color
 * @param code ANSI code of the color
 */
static inline void set_backgound_color(int code) { printf("\x1b[%dm", code); }

/**
 * Resets all the colors and styles of console to default
 */
static inline void reset_color() { printf("\x1b[%dm", RESET_COLOR); }

/**
 * Cleans the screen
 */
static inline void clean() { printf("\033c"); }