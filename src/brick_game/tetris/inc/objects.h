#ifndef BACKEND_OBJECTS_H
#define BACKEND_OBJECTS_H

#include "defines.h"

/**
 * @file objects.h
 * @brief This file contains type definitions and enumerations for the game
 * objects and states.
 */

/**
 * @enum GameState
 * @brief Represents the different states of the game.
 */
typedef enum {
  Menu_main,       /**< The main menu state. */
  Menu_secondary,  /**< The secondary menu state. */
  Game_proceeding, /**< The state when the game is in progress. */
  Game_paused,     /**< The state when the game is paused. */
  Game_over,       /**< The state when the game is over. */
  Exit_state,      /**< The state when exiting the game. */
  Error_state      /**< The state when an error has occurred. */
} GameState;

/**
 * @enum UserAction_t
 * @brief Represents the different actions a user can take.
 */
typedef enum {
  Start,     /**< Action to start the game. */
  Pause,     /**< Action to pause the game. */
  Terminate, /**< Action to terminate the game. */
  Left,      /**< Action to move left. */
  Right,     /**< Action to move right. */
  Up,        /**< Action to move up. */
  Down,      /**< Action to move down. */
  Action     /**< Action to perform a generic action. */
} UserAction_t;

/**
 * @enum Choice_t
 * @brief Represents the different menu choices.
 */
typedef enum {
  Play,      /**< Choice to play the game. */
  Controls,  /**< Choice to view controls. */
  Hi_scores, /**< Choice to view high scores. */
  Setting,   /**< Choice to view settings. */
  Exit       /**< Choice to exit the game. */
} Choice_t;

/**
 * @struct GameInfo_t
 * @brief Contains information about the current game state.
 */
typedef struct {
  int **field;    /**< The game field matrix. */
  int **next;     /**< The next Tetramino matrix. */
  int score;      /**< The current score. */
  int high_score; /**< The high score. */
  int level;      /**< The current level. */
  int speed;      /**< The current speed. */
  int pause;      /**< The pause state. */
} GameInfo_t;

/**
 * @struct Figure_t
 * @brief Represents a Tetramino figure.
 */
typedef struct {
  int typeNext; /**< The type of the next Tetramino. */
  int type;     /**< The type of the current Tetramino. */
  int rotation; /**< The rotation state of the Tetramino. */
  int x;        /**< The x-coordinate of the Tetramino. */
  int y;        /**< The y-coordinate of the Tetramino. */
} Figure_t;

/**
 * @struct GameParams_t
 * @brief Contains the parameters for the current game.
 */
typedef struct {
  GameInfo_t *info;  /**< Pointer to the game information. */
  GameState state;   /**< The current state of the game. */
  UserAction_t uact; /**< The current user action. */
  Choice_t ch;       /**< The current menu choice. */
  Figure_t *figure;  /**< Pointer to the current Tetramino figure. */
} GameParams_t;

#endif /* BACKEND_OBJECTS_H */
