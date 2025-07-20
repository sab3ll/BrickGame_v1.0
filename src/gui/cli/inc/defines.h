#ifndef FRONTEND_DEFINES_H
#define FRONTEND_DEFINES_H

#define TICK 50
#define GET_USER_INPUT getch()
#define OFFSET_X 3
#define OFFSET_Y 3
#define HUD_WIDTH 12
#define BOARD_HEIGHT 20
#define BOARD_WIDTH 10

#define MVPRINTW(y, x, ...) \
  mvprintw(OFFSET_Y + (y), OFFSET_X * 2 + (x), __VA_ARGS__)
#define MVADDCH(y, x, c) mvaddch(OFFSET_Y + (y), OFFSET_X * 2 + (x), c)

#define SUCCESS 0
#define ERROR 1

#endif
