#ifndef BACKEND_H
#define BACKEND_H

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "defines.h"
#include "objects.h"

/**
 * @file backend.h
 * @brief This file contains declarations for the backend functions used in the
 * game.
 */

/**
 * @brief Initializes the game parameters.
 * @param prms A pointer to the game parameters to be initialized.
 */
void initParams(GameParams_t *prms);

/**
 * @brief Generates a high score for the game.
 * @param prms A pointer to the game parameters.
 */
void genHighScore(GameParams_t *prms);

/**
 * @brief Resets the game field.
 * @param prms A pointer to the game parameters.
 */
void resetField(GameParams_t *prms);

/**
 * @brief Generates a new Tetramino.
 * @param next A pointer to the next Tetramino matrix.
 * @return The type of the generated Tetramino.
 */
int genTetramino(int **next);

/**
 * @brief Initializes the game.
 * @param prms A pointer to the game parameters.
 */
void initGame(GameParams_t *prms);

/**
 * @brief Spawns the next Tetramino.
 * @param prms A pointer to the game parameters.
 */
void spawnNextTetramino(GameParams_t *prms);

/**
 * @brief Updates the current Tetramino's position on the field.
 * @param prms A pointer to the game parameters.
 */
void updateTetramino(GameParams_t *prms);

/**
 * @brief Clears the current Tetramino from the field.
 * @param prms A pointer to the game parameters.
 */
void clearTetramino(GameParams_t *prms);

/**
 * @brief Checks if the current Tetramino collides with the field or other
 * Tetraminos.
 * @param prms A pointer to the game parameters.
 * @return True if there is a collision, false otherwise.
 */
bool isCollide(GameParams_t *prms);

/**
 * @brief Counts the number of full rows in the field.
 * @param prms A pointer to the game parameters.
 * @return The number of full rows.
 */
int countFullRows(GameParams_t *prms);

/**
 * @brief Increases the game speed based on the current level.
 * @param prms A pointer to the game parameters.
 */
void increaseSpeed(GameParams_t *prms);

/**
 * @brief Adds score to the game.
 * @param prms A pointer to the game parameters.
 */
void addScore(GameParams_t *prms);

/**
 * @brief Updates the high score.
 * @param prms A pointer to the game parameters.
 * @param score The new score to be updated.
 */
void updateHiScore(GameParams_t *prms, int score);

/**
 * @brief Initializes a matrix with the given number of rows and columns.
 * @param rows The number of rows in the matrix.
 * @param cols The number of columns in the matrix.
 * @return A pointer to the initialized matrix.
 */
int **initMatrix(int rows, int cols);

/**
 * @brief Frees the memory allocated for the matrix.
 * @param matrix A pointer to the matrix to be freed.
 * @param rows The number of rows in the matrix.
 */
void freeMatrix(int **matrix, int rows);

/**
 * @brief Frees the memory allocated for the game parameters.
 * @param prms A pointer to the game parameters.
 */
void freeMemory(GameParams_t *prms);

#endif
