#ifndef FSM_H
#define FSM_H

#include <ncurses.h>

#include "defines.h"
#include "objects.h"

/**
 * @file fsm.h
 * @brief This file contains declarations for the finite state machine (FSM)
 * functions used in the game.
 */

/**
 * @typedef action_ptr
 * @brief Defines a pointer to a function that takes a GameParams_t pointer as a
 * parameter.
 */
typedef void (*action_ptr)(GameParams_t *prms);

/**
 * @brief Updates the current state of the game.
 * @return The updated game information.
 */
GameInfo_t updateCurrentState(void);

/**
 * @brief Updates the game parameters.
 * @param prms A pointer to the game parameters to be updated.
 * @return A pointer to the updated game parameters.
 */
GameParams_t *updateParams(GameParams_t *prms);

/**
 * @brief Gets the user action signal based on the user input.
 * @param userInput The input from the user.
 * @return The user action corresponding to the input.
 */
UserAction_t getSignal(int userInput);

/**
 * @brief Handles the user input.
 * @param action The action to be performed based on the user input.
 * @param hold A boolean indicating whether to hold the action.
 */
void userInput(UserAction_t action, bool hold);

/**
 * @brief Starts the game with the given parameters.
 * @param prms A pointer to the game parameters.
 */
void startGame(GameParams_t *prms);

/**
 * @brief Performs an action based on the user signal.
 * @param sig The user action signal.
 * @param params A pointer to the game parameters.
 */
void sigact(UserAction_t sig, GameParams_t *params);

/**
 * @brief Moves the figure down.
 * @param prms A pointer to the game parameters.
 */
void moveDown(GameParams_t *prms);

/**
 * @brief Moves the figure to the right.
 * @param prms A pointer to the game parameters.
 */
void moveRight(GameParams_t *prms);

/**
 * @brief Moves the figure to the left.
 * @param prms A pointer to the game parameters.
 */
void moveLeft(GameParams_t *prms);

/**
 * @brief Rotates the figure.
 * @param prms A pointer to the game parameters.
 */
void rotate(GameParams_t *prms);

/**
 * @brief Shifts the figure down by one unit.
 * @param prms A pointer to the game parameters.
 */
void shift(GameParams_t *prms);

/**
 * @brief Pauses the game.
 * @param prms A pointer to the game parameters.
 */
void pauseGame(GameParams_t *prms);

/**
 * @brief Ends the game.
 * @param prms A pointer to the game parameters.
 */
void endGame(GameParams_t *prms);

/**
 * @brief Switches the menu.
 * @param prms A pointer to the game parameters.
 */
void switchMenu(GameParams_t *prms);

/**
 * @brief Exits the game.
 * @param prms A pointer to the game parameters.
 */
void exitGame(GameParams_t *prms);

#endif
