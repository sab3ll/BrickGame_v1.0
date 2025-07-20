#ifndef FRONTEND_H
#define FRONTEND_H

#include <stdio.h>

#include "defines.h"
#include "tetris.h"

/**
 * @brief Updates and returns the current state of the game.
 *
 * @return GameInfo_t Current game information.
 */
GameInfo_t updateCurrentState();

/**
 * @brief Initializes the overlay for the game display.
 */
void initOverlay(void);

/**
 * @brief Prints the borders of the game field.
 */
void printBorders(void);

/**
 * @brief Prints the current game information such as score, level, etc.
 */
void printGameInfo(void);

/**
 * @brief Prints the paused state overlay.
 */
void printPaused(void);

/**
 * @brief Prints the game over overlay.
 */
void printOver(void);

/**
 * @brief Prints the exit overlay.
 */
void printExit(void);

/**
 * @brief Terminates and clears the overlay.
 */
void terminateOverlay(void);

/**
 * @brief Clears the game state from the display.
 */
void clearGameState(void);

/**
 * @brief Prints the overlay based on the current game parameters.
 *
 * @param prms Pointer to the game parameters.
 */
void printOverlay(GameParams_t *prms);

/**
 * @brief Prints the game statistics such as high scores, current score, etc.
 *
 * @param prms Pointer to the game parameters.
 */
void printStats(GameParams_t *prms);

/**
 * @brief Prints the main menu.
 */
void printMenu();

/**
 * @brief Prints a rectangle on the screen with the specified coordinates.
 *
 * @param top_y Top y-coordinate of the rectangle.
 * @param bottom_y Bottom y-coordinate of the rectangle.
 * @param left_x Left x-coordinate of the rectangle.
 * @param right_x Right x-coordinate of the rectangle.
 */
void printRectangle(int top_y, int bottom_y, int left_x, int right_x);

#endif
