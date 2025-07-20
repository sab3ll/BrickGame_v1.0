#include "fsm.h"

#include "backend.h"

action_ptr fsm_table[8][8] = {
    {startGame, NULL, exitGame, NULL, NULL, NULL, NULL, NULL},  // Главное меню
    {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},  // Побочное меню
    {NULL, pauseGame, NULL, moveLeft, moveRight, NULL, moveDown,
     rotate},  // Управление тетрамино
    {NULL, pauseGame, endGame, NULL, NULL, NULL, NULL,
     NULL},  // Игра приостановлена
    {startGame, NULL, exitGame, NULL, NULL, NULL, NULL,
     switchMenu},  // Игра окончена
    {exitGame, exitGame, exitGame, exitGame, exitGame, exitGame, exitGame,
     exitGame},  // Выход из игры
    {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL}  // Ошибка
};

GameInfo_t updateCurrentState(void) {
  GameParams_t *prms = updateParams(NULL);
  shift(prms);
  return *prms->info;
}

GameParams_t *updateParams(GameParams_t *prms) {
  static GameParams_t *data;
  if (prms != NULL) data = prms;
  return data;
}

void sigact(UserAction_t sig, GameParams_t *params) {
  action_ptr act = NULL;
  params->uact = sig;
  if (params->state != Error_state) act = fsm_table[params->state][sig];
  if (act) act(params);
}

UserAction_t getSignal(int userInput) {
  UserAction_t rc = Up;
  if (userInput == KEY_ENTR)
    rc = Start;
  else if (userInput == P)
    rc = Pause;
  else if (userInput == ESCAPE)
    rc = Terminate;
  else if (userInput == KEY_LEFT)
    rc = Left;
  else if (userInput == KEY_RIGHT)
    rc = Right;
  else if (userInput == KEY_DOWN)
    rc = Down;
  else if (userInput == SPACE)
    rc = Action;
  return rc;
}

void startGame(GameParams_t *prms) {
  resetField(prms);
  initGame(prms);
  spawnNextTetramino(prms);
  prms->state = Game_proceeding;
}

void moveDown(GameParams_t *prms) {
  clearTetramino(prms);
  prms->figure->y++;
  if (isCollide(prms)) prms->figure->y--;
  updateTetramino(prms);
}

void moveRight(GameParams_t *prms) {
  clearTetramino(prms);
  prms->figure->x++;
  if (isCollide(prms)) prms->figure->x--;
  updateTetramino(prms);
}

void moveLeft(GameParams_t *prms) {
  clearTetramino(prms);
  prms->figure->x--;
  if (isCollide(prms)) prms->figure->x++;
  updateTetramino(prms);
}

void rotate(GameParams_t *prms) {
  clearTetramino(prms);
  prms->figure->rotation = (prms->figure->rotation + 1) % (ROTATION_MAX + 1);
  if (isCollide(prms))
    prms->figure->rotation =
        (prms->figure->rotation - 1 + (ROTATION_MAX + 1)) % (ROTATION_MAX + 1);
  updateTetramino(prms);
}

void shift(GameParams_t *prms) {
  clearTetramino(prms);
  prms->figure->y++;
  bool notShifting = isCollide(prms);
  if (notShifting) {
    prms->figure->y--;
  }
  updateTetramino(prms);
  if (notShifting) {
    addScore(prms);
    increaseSpeed(prms);
    spawnNextTetramino(prms);
    clearTetramino(prms);
    prms->figure->y++;
    bool notShifting_2 = isCollide(prms);
    if (notShifting_2) {
      prms->figure->y--;
      prms->state = Game_over;
    }
    updateTetramino(prms);
  }
}

void pauseGame(GameParams_t *prms) {
  if (prms->state == Game_paused)
    prms->state = Game_proceeding;
  else
    prms->state = Game_paused;
}

void endGame(GameParams_t *prms) { prms->state = Game_over; }

void switchMenu(GameParams_t *prms) { prms->state = Menu_main; }

void exitGame(GameParams_t *prms) { prms->state = Exit_state; }
