#include "frontend.h"

void initOverlay(void) {
  setlocale(LC_ALL, "");
  initscr();
  start_color();
  init_pair(1, COLOR_RED, COLOR_RED);
  init_pair(2, COLOR_CYAN, COLOR_CYAN);
  init_pair(3, COLOR_YELLOW, COLOR_YELLOW);
  init_pair(4, COLOR_MAGENTA, COLOR_MAGENTA);
  init_pair(5, COLOR_GREEN, COLOR_GREEN);
  init_pair(6, COLOR_BLUE, COLOR_BLUE);
  init_pair(7, COLOR_RED, COLOR_BLUE);
  cbreak();
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);
  timeout(TICK);
}

void printBorders(void) {
  printRectangle(0, BOARD_HEIGHT + 1, 0, BOARD_WIDTH * 2 + 1);
  printRectangle(0, BOARD_HEIGHT + 1, BOARD_WIDTH * 2 + 2,
                 BOARD_WIDTH * 2 + HUD_WIDTH + 1);
}

void printGameInfo(void) {
  printRectangle(2, 4, BOARD_WIDTH * 2 + 3, BOARD_WIDTH * 2 + HUD_WIDTH);
  printRectangle(6, 8, BOARD_WIDTH * 2 + 3, BOARD_WIDTH * 2 + HUD_WIDTH);
  printRectangle(10, 12, BOARD_WIDTH * 2 + 3, BOARD_WIDTH * 2 + HUD_WIDTH);
  printRectangle(14, 17, BOARD_WIDTH * 2 + 3, BOARD_WIDTH * 2 + HUD_WIDTH);
  MVPRINTW(1, BOARD_WIDTH * 2 + 4, "HI-SCORE");
  MVPRINTW(5, BOARD_WIDTH * 2 + 4, "SCORE");
  MVPRINTW(9, BOARD_WIDTH * 2 + 4, "LEVEL");
  MVPRINTW(13, BOARD_WIDTH * 2 + 4, "NEXT");
}

void printPaused(void) {
  MVPRINTW(18, BOARD_WIDTH * 2 + 4, "%s", "Game is");
  MVPRINTW(19, BOARD_WIDTH * 2 + 4, "%s", "paused ");
}

void printOver(void) {
  MVPRINTW(18, BOARD_WIDTH * 2 + 4, "%s", "Game is");
  MVPRINTW(19, BOARD_WIDTH * 2 + 4, "%s", "over   ");
}

void printExit(void) {
  MVPRINTW(18, BOARD_WIDTH * 2 + 4, "%s", "Exiting ");
  MVPRINTW(19, BOARD_WIDTH * 2 + 4, "%s", "the game");
}

void clearGameState(void) {
  MVPRINTW(18, BOARD_WIDTH * 2 + 4, "%s", "       ");
  MVPRINTW(19, BOARD_WIDTH * 2 + 4, "%s", "       ");
}

void terminateOverlay(void) {
  refresh();
  sleep(1);
  clear();
  refresh();
  endwin();
}

void printStats(GameParams_t *prms) {
  MVPRINTW(3, BOARD_WIDTH * 2 + 4, "%d", prms->info->high_score);
  MVPRINTW(7, BOARD_WIDTH * 2 + 4, "%d", prms->info->score);
  MVPRINTW(11, BOARD_WIDTH * 2 + 4, "%d", prms->info->level);
  for (int row = 0; row < TETRAMINO_HEIGHT; row++)
    for (int col = 0; col < TETRAMINO_WIDTH; col++) {
      if (prms->info->next[row][col]) {
        attron(COLOR_PAIR(prms->info->next[row][col]));
        mvaddch(18 + row, BOARD_WIDTH * 2 + 5 * 2 + col * 2, ACS_CKBOARD);
        mvaddch(18 + row, BOARD_WIDTH * 2 + 5 * 2 + col * 2 + 1, ACS_CKBOARD);
        attroff(COLOR_PAIR(prms->info->next[row][col]));
      }
    }
}

void printMenu() {
  MVPRINTW(3, 4, "%s", "BrickGame v1.0");
  MVPRINTW(7, 4, "%s", "Play");
  MVPRINTW(9, 4, "%s", "Controls");
  MVPRINTW(11, 4, "%s", "Hi-scores");
  MVPRINTW(13, 4, "%s", "Settings");
  MVPRINTW(15, 4, "%s", "Exit");
}

void printField(int **field) {
  for (int i = 0; i < BOARD_HEIGHT; i++)
    for (int j = 0; j < BOARD_WIDTH; j++)
      if (field[i + OFFSET_Y][j + OFFSET_X]) {
        attron(COLOR_PAIR(field[i + OFFSET_Y][j + OFFSET_X]));
        mvaddch(i + OFFSET_Y + 1, j * 2 + OFFSET_X * 2 + 1, ACS_CKBOARD);
        mvaddch(i + OFFSET_Y + 1, j * 2 + OFFSET_X * 2 + 2, ACS_CKBOARD);
        attroff(COLOR_PAIR(field[i + OFFSET_Y][j + OFFSET_X]));
      }
}

void printOverlay(GameParams_t *prms) {
  clear();
  printBorders();
  printGameInfo();
  if (prms->state == Menu_main) {
    printMenu();
    clearGameState();
  } else if (prms->state == Game_proceeding) {
    printStats(prms);
    printField(prms->info->field);
    clearGameState();
    refresh();
  } else if (prms->state == Game_paused) {
    printStats(prms);
    printField(prms->info->field);
    printPaused();
  } else if (prms->state == Game_over) {
    printStats(prms);
    printOver();
  } else if (prms->state == Exit_state) {
    printMenu();
    printExit();
  }
}

void printRectangle(int top_y, int bottom_y, int left_x, int right_x) {
  MVADDCH(top_y, left_x, ACS_ULCORNER);

  int i = left_x + 1;

  for (; i < right_x; i++) MVADDCH(top_y, i, ACS_HLINE);
  MVADDCH(top_y, i, ACS_URCORNER);

  for (int j = top_y + 1; j < bottom_y; j++) {
    MVADDCH(j, left_x, ACS_VLINE);
    MVADDCH(j, right_x, ACS_VLINE);
  }

  MVADDCH(bottom_y, left_x, ACS_LLCORNER);
  i = left_x + 1;
  for (; i < right_x; i++) MVADDCH(bottom_y, i, ACS_HLINE);
  MVADDCH(bottom_y, i, ACS_LRCORNER);
}
