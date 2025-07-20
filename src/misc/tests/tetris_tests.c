#include <check.h>
#include <stdlib.h>

#include "../../brick_game/tetris/inc/tetris.h"

#define SHOW_FAILED TRUE

START_TEST(s21_tetris_test_1) {
  GameParams_t params;
  GameInfo_t info;
  Figure_t figure;
  params.info = &info;
  params.figure = &figure;

  initParams(&params);
  updateParams(&params);
  spawnNextTetramino(&params);
  GameInfo_t dataCheck = updateCurrentState();

  ck_assert_ptr_eq(params.info->field, dataCheck.field);
  ck_assert_ptr_eq(params.info->next, dataCheck.next);
  ck_assert_int_eq(params.info->high_score, dataCheck.high_score);
  ck_assert_int_eq(params.info->score, dataCheck.score);
  ck_assert_int_eq(params.info->level, dataCheck.level);
  ck_assert_int_eq(params.info->pause, dataCheck.pause);
  ck_assert_int_eq(params.info->speed, dataCheck.speed);
  freeMemory(&params);
}
END_TEST

START_TEST(s21_tetris_test_2) {
  GameParams_t params;
  GameInfo_t info;
  Figure_t figure;
  params.info = &info;
  params.figure = &figure;

  initParams(&params);
  GameParams_t *paramsCheck1 = updateParams(&params);
  GameParams_t *paramsCheck2 = updateParams(NULL);

  ck_assert_ptr_eq(&params, paramsCheck1);
  ck_assert_ptr_eq(&params, paramsCheck2);
  freeMemory(&params);
}
END_TEST

START_TEST(s21_tetris_test_3) {
  GameParams_t params;
  GameInfo_t info;
  Figure_t figure;
  params.info = &info;
  params.figure = &figure;

  initParams(&params);

  ck_assert_int_eq(params.info->score, 0);
  ck_assert_int_eq(params.info->level, 1);
  ck_assert_int_eq(params.info->speed, 1);
  ck_assert_int_eq(params.info->pause, 0);
  ck_assert_int_ge(params.figure->typeNext, 0);
  ck_assert_int_le(params.figure->typeNext, 6);
  ck_assert_int_eq(params.state, Menu_main);
  ck_assert_int_eq(params.uact, Up);
  ck_assert_int_eq(params.ch, Play);
  freeMemory(&params);
}
END_TEST

START_TEST(s21_tetris_test_4) {
  GameParams_t params;
  GameInfo_t info;
  Figure_t figure;
  params.info = &info;
  params.figure = &figure;

  initParams(&params);
  freeMemory(&params);

  ck_assert_ptr_null(params.info->field);
  ck_assert_ptr_null(params.info->next);
}
END_TEST

START_TEST(s21_tetris_test_5) {
  GameParams_t params;
  GameInfo_t info;
  params.info = &info;
  params.info->field = NULL;
  params.info->next = NULL;

  freeMemory(&params);

  ck_assert_ptr_null(params.info->field);
  ck_assert_ptr_null(params.info->next);
}
END_TEST

START_TEST(s21_tetris_test_6) {
  GameParams_t params;
  GameInfo_t info;
  Figure_t figure;
  params.info = &info;
  params.figure = &figure;

  initParams(&params);
  initGame(&params);

  ck_assert_int_eq(params.info->score, 0);
  ck_assert_int_eq(params.info->level, 1);
  ck_assert_int_eq(params.info->speed, 1);
  ck_assert_int_eq(params.state, Menu_main);
  freeMemory(&params);
}
END_TEST

START_TEST(s21_tetris_test_7) {
  GameParams_t params;
  GameInfo_t info;
  Figure_t figure;
  params.info = &info;
  params.figure = &figure;

  initParams(&params);
  params.info->field[FIELD_HEIGHT / 2][FIELD_WIDTH / 2] = 1;
  resetField(&params);

  bool isFieldEqual = true;
  for (int row = 0; row < FIELD_HEIGHT && isFieldEqual; row++)
    for (int col = 0; col < FIELD_WIDTH && isFieldEqual; col++) {
      int checkValue = (row > 22 || col < 3 || col > 12) ? 1 : 0;
      isFieldEqual = params.info->field[row][col] == checkValue;
    }
  ck_assert_int_eq(isFieldEqual, true);
  freeMemory(&params);
}
END_TEST

START_TEST(s21_tetris_test_8) {
  GameParams_t params;
  GameInfo_t info;
  Figure_t figure;
  params.info = &info;
  params.figure = &figure;

  initParams(&params);
  params.figure->typeNext = genTetramino(params.info->next);

  ck_assert_int_ge(params.figure->typeNext, 0);
  ck_assert_int_le(params.figure->typeNext, 6);
  freeMemory(&params);
}
END_TEST

START_TEST(s21_tetris_test_9) {
  GameParams_t params;
  GameInfo_t info;
  Figure_t figure;
  params.info = &info;
  params.figure = &figure;

  initParams(&params);
  params.figure->typeNext = 0;
  spawnNextTetramino(&params);

  ck_assert_int_eq(params.figure->type, 0);
  ck_assert_int_eq(params.figure->y, 2);
  ck_assert_int_eq(params.figure->x, FIELD_WIDTH / 2);
  ck_assert_int_eq(params.figure->rotation, 0);
  freeMemory(&params);
}
END_TEST

START_TEST(s21_tetris_test_10) {
  GameParams_t params;
  GameInfo_t info;
  Figure_t figure;
  params.info = &info;
  params.figure = &figure;

  initParams(&params);
  params.figure->y = FIELD_HEIGHT / 2;
  params.figure->x = FIELD_WIDTH / 2;
  int previousX = params.figure->x;
  params.figure->type = 0;
  params.figure->rotation = 0;
  moveLeft(&params);

  ck_assert_int_ne(params.figure->x, previousX);
  freeMemory(&params);
}
END_TEST

START_TEST(s21_tetris_test_11) {
  GameParams_t params;
  GameInfo_t info;
  Figure_t figure;
  params.info = &info;
  params.figure = &figure;

  initParams(&params);
  params.figure->y = FIELD_HEIGHT / 2;
  params.figure->x = 4;
  int previousX = params.figure->x;
  params.figure->type = 0;
  params.figure->rotation = 0;
  moveLeft(&params);

  ck_assert_int_eq(params.figure->x, previousX);
  freeMemory(&params);
}
END_TEST

START_TEST(s21_tetris_test_12) {
  GameParams_t params;
  GameInfo_t info;
  Figure_t figure;
  params.info = &info;
  params.figure = &figure;

  initParams(&params);
  params.figure->y = FIELD_HEIGHT / 2;
  params.figure->x = FIELD_WIDTH / 2;
  int previousX = params.figure->x;
  params.figure->type = 0;
  params.figure->rotation = 0;
  moveRight(&params);

  ck_assert_int_ne(params.figure->x, previousX);
  freeMemory(&params);
}
END_TEST

START_TEST(s21_tetris_test_13) {
  GameParams_t params;
  GameInfo_t info;
  Figure_t figure;
  params.info = &info;
  params.figure = &figure;

  initParams(&params);
  params.figure->y = FIELD_HEIGHT / 2;
  params.figure->x = FIELD_WIDTH - 6;
  int previousX = params.figure->x;
  params.figure->type = 0;
  params.figure->rotation = 0;
  moveRight(&params);

  ck_assert_int_eq(params.figure->x, previousX);
  freeMemory(&params);
}
END_TEST

START_TEST(s21_tetris_test_14) {
  GameParams_t params;
  GameInfo_t info;
  Figure_t figure;
  params.info = &info;
  params.figure = &figure;

  initParams(&params);
  params.figure->y = FIELD_HEIGHT / 2;
  params.figure->x = FIELD_WIDTH / 2;
  params.figure->rotation = 0;
  params.figure->type = 0;
  int previousRotation = params.figure->rotation;
  rotate(&params);

  ck_assert_int_ne(params.figure->rotation, previousRotation);
  freeMemory(&params);
}
END_TEST

START_TEST(s21_tetris_test_15) {
  GameParams_t params;
  GameInfo_t info;
  Figure_t figure;
  params.info = &info;
  params.figure = &figure;

  initParams(&params);
  params.figure->y = FIELD_HEIGHT / 2;
  params.figure->x = FIELD_WIDTH - 3;
  params.figure->type = 0;
  params.figure->rotation = 0;
  int previousRotation = params.figure->rotation;
  rotate(&params);

  ck_assert_int_eq(params.figure->rotation, previousRotation);
  freeMemory(&params);
}
END_TEST

START_TEST(s21_tetris_test_16) {
  GameParams_t params;
  GameInfo_t info;
  Figure_t figure;
  params.info = &info;
  params.figure = &figure;

  initParams(&params);
  params.figure->y = FIELD_HEIGHT / 2;
  params.figure->x = FIELD_WIDTH / 2;
  int previousY = params.figure->y;
  params.figure->type = 0;
  params.figure->rotation = 0;
  moveDown(&params);

  ck_assert_int_ne(params.figure->y, previousY);
  freeMemory(&params);
}
END_TEST

START_TEST(s21_tetris_test_17) {
  GameParams_t params;
  GameInfo_t info;
  Figure_t figure;
  params.info = &info;
  params.figure = &figure;

  initParams(&params);
  params.figure->y = FIELD_HEIGHT - 3;
  params.figure->x = FIELD_WIDTH / 2;
  int previousY = params.figure->y;
  params.figure->type = 0;
  params.figure->rotation = 0;
  moveDown(&params);

  ck_assert_int_eq(params.figure->y, previousY);
  freeMemory(&params);
}
END_TEST

START_TEST(s21_tetris_test_18) {
  GameParams_t params;
  GameInfo_t info;
  Figure_t figure;
  params.info = &info;
  params.figure = &figure;

  initParams(&params);
  params.figure->y = FIELD_HEIGHT / 2;
  params.figure->x = FIELD_WIDTH / 2;
  int previousY = params.figure->y;
  params.figure->type = 0;
  params.figure->rotation = 0;
  shift(&params);

  ck_assert_int_ne(params.figure->y, previousY);
  freeMemory(&params);
}
END_TEST

START_TEST(s21_tetris_test_19) {
  GameParams_t params;
  GameInfo_t info;
  Figure_t figure;
  params.info = &info;
  params.figure = &figure;

  initParams(&params);
  params.figure->y = FIELD_HEIGHT - 4;
  params.figure->x = FIELD_WIDTH / 2;
  int previousY = params.figure->y;
  params.figure->type = 0;
  params.figure->rotation = 0;
  shift(&params);

  ck_assert_int_ne(params.figure->y, previousY);
  freeMemory(&params);
}
END_TEST

START_TEST(s21_tetris_test_20) {
  GameParams_t params;
  GameInfo_t info;
  Figure_t figure;
  int signal = KEY_ENTR;
  params.info = &info;
  params.figure = &figure;

  initParams(&params);
  sigact(getSignal(signal), &params);

  ck_assert_int_eq(params.state, Game_proceeding);
  freeMemory(&params);
}
END_TEST

START_TEST(s21_tetris_test_21) {
  GameParams_t params;
  GameInfo_t info;
  Figure_t figure;
  int signal = P;
  params.info = &info;
  params.figure = &figure;

  initParams(&params);
  params.state = Game_proceeding;
  sigact(getSignal(signal), &params);

  ck_assert_int_eq(params.state, Game_paused);
  freeMemory(&params);
}
END_TEST

START_TEST(s21_tetris_test_22) {
  GameParams_t params;
  GameInfo_t info;
  Figure_t figure;
  int signal = P;
  params.info = &info;
  params.figure = &figure;

  initParams(&params);
  params.state = Game_paused;
  sigact(getSignal(signal), &params);

  ck_assert_int_eq(params.state, Game_proceeding);
  freeMemory(&params);
}
END_TEST

START_TEST(s21_tetris_test_23) {
  GameParams_t params;
  GameInfo_t info;
  Figure_t figure;
  int signal = ESCAPE;
  params.info = &info;
  params.figure = &figure;

  initParams(&params);
  sigact(getSignal(signal), &params);

  ck_assert_int_eq(params.state, Exit_state);
  freeMemory(&params);
}
END_TEST

START_TEST(s21_tetris_test_24) {
  GameParams_t params;
  GameInfo_t info;
  Figure_t figure;
  int signal = KEY_LEFT;
  params.info = &info;
  params.figure = &figure;

  initParams(&params);
  startGame(&params);
  params.figure->y = FIELD_HEIGHT / 2;
  params.figure->x = FIELD_WIDTH / 2;
  int previousX = params.figure->x;
  int previousY = params.figure->y;
  sigact(getSignal(signal), &params);
  ck_assert_int_eq(params.state, Game_proceeding);
  ck_assert_int_eq(params.figure->x, previousX - 1);
  ck_assert_int_eq(params.figure->y, previousY);
  freeMemory(&params);
}
END_TEST

START_TEST(s21_tetris_test_25) {
  GameParams_t params;
  GameInfo_t info;
  Figure_t figure;
  int signal = KEY_RIGHT;
  params.info = &info;
  params.figure = &figure;

  initParams(&params);
  startGame(&params);
  params.figure->y = FIELD_HEIGHT / 2;
  params.figure->x = FIELD_WIDTH / 2;
  int previousX = params.figure->x;
  int previousY = params.figure->y;
  sigact(getSignal(signal), &params);
  ck_assert_int_eq(params.state, Game_proceeding);
  ck_assert_int_eq(params.figure->x, previousX + 1);
  ck_assert_int_eq(params.figure->y, previousY);
  freeMemory(&params);
}
END_TEST

START_TEST(s21_tetris_test_26) {
  GameParams_t params;
  GameInfo_t info;
  Figure_t figure;
  int signal = KEY_DOWN;
  params.info = &info;
  params.figure = &figure;

  initParams(&params);
  startGame(&params);
  params.figure->y = FIELD_HEIGHT / 2;
  params.figure->x = FIELD_WIDTH / 2;
  int previousX = params.figure->x;
  int previousY = params.figure->y;
  sigact(getSignal(signal), &params);
  ck_assert_int_eq(params.state, Game_proceeding);
  ck_assert_int_eq(params.figure->x, previousX);
  ck_assert_int_eq(params.figure->y, previousY + 1);
  freeMemory(&params);
}
END_TEST

START_TEST(s21_tetris_test_27) {
  GameParams_t params;
  GameInfo_t info;
  Figure_t figure;
  int signal = SPACE;
  params.info = &info;
  params.figure = &figure;

  initParams(&params);
  startGame(&params);
  params.figure->y = FIELD_HEIGHT / 2;
  params.figure->x = FIELD_WIDTH / 2;
  int previousX = params.figure->x;
  int previousY = params.figure->y;
  int previousRotation = params.figure->rotation;
  sigact(getSignal(signal), &params);
  ck_assert_int_eq(params.state, Game_proceeding);
  ck_assert_int_eq(params.figure->x, previousX);
  ck_assert_int_eq(params.figure->y, previousY);
  ck_assert_int_eq(params.figure->rotation, previousRotation + 1);
  freeMemory(&params);
}
END_TEST

START_TEST(s21_tetris_test_28) {
  GameParams_t params;
  GameInfo_t info;
  Figure_t figure;
  params.info = &info;
  params.figure = &figure;

  initParams(&params);
  startGame(&params);
  params.figure->y = FIELD_HEIGHT / 2;
  params.figure->x = FIELD_WIDTH / 2;
  for (int i = FIELD_HEIGHT / 2 + 1; i < FIELD_HEIGHT / 2 + 2; i++)
    for (int j = 3; j < FIELD_WIDTH - 3; j++) params.info->field[i][j] = 1;
  shift(&params);
  ck_assert_int_eq(params.info->score, 100);
  freeMemory(&params);
}
END_TEST

START_TEST(s21_tetris_test_29) {
  GameParams_t params;
  GameInfo_t info;
  Figure_t figure;
  params.info = &info;
  params.figure = &figure;

  initParams(&params);
  startGame(&params);
  params.figure->y = FIELD_HEIGHT / 2;
  params.figure->x = FIELD_WIDTH / 2;
  for (int i = FIELD_HEIGHT / 2 + 1; i < FIELD_HEIGHT / 2 + 3; i++)
    for (int j = 3; j < FIELD_WIDTH - 3; j++) params.info->field[i][j] = 1;
  shift(&params);
  ck_assert_int_eq(params.info->score, 300);
  freeMemory(&params);
}
END_TEST

START_TEST(s21_tetris_test_30) {
  GameParams_t params;
  GameInfo_t info;
  Figure_t figure;
  params.info = &info;
  params.figure = &figure;

  initParams(&params);
  startGame(&params);
  params.figure->y = FIELD_HEIGHT / 2;
  params.figure->x = FIELD_WIDTH / 2;
  for (int i = FIELD_HEIGHT / 2 + 1; i < FIELD_HEIGHT / 2 + 4; i++)
    for (int j = 3; j < FIELD_WIDTH - 3; j++) params.info->field[i][j] = 1;
  shift(&params);
  ck_assert_int_eq(params.info->score, 700);
  freeMemory(&params);
}
END_TEST

START_TEST(s21_tetris_test_31) {
  GameParams_t params;
  GameInfo_t info;
  Figure_t figure;
  params.info = &info;
  params.figure = &figure;

  initParams(&params);
  startGame(&params);
  params.figure->y = FIELD_HEIGHT / 2;
  params.figure->x = FIELD_WIDTH / 2;
  for (int i = FIELD_HEIGHT / 2 + 1; i < FIELD_HEIGHT / 2 + 5; i++)
    for (int j = 3; j < FIELD_WIDTH - 3; j++) params.info->field[i][j] = 1;
  shift(&params);
  ck_assert_int_eq(params.info->score, 1500);
  ck_assert_int_eq(params.state, Game_over);
  freeMemory(&params);
}
END_TEST

START_TEST(s21_tetris_test_32) {
  GameParams_t params;
  GameInfo_t info;
  Figure_t figure;
  int signal = ESCAPE;
  params.info = &info;
  params.figure = &figure;

  initParams(&params);
  params.state = Game_paused;
  sigact(getSignal(signal), &params);

  ck_assert_int_eq(params.state, Game_over);
  freeMemory(&params);
}
END_TEST

START_TEST(s21_tetris_test_33) {
  GameParams_t params;
  GameInfo_t info;
  Figure_t figure;
  int signal = SPACE;
  params.info = &info;
  params.figure = &figure;

  initParams(&params);
  params.state = Game_over;
  sigact(getSignal(signal), &params);

  ck_assert_int_eq(params.state, Menu_main);
  freeMemory(&params);
}
END_TEST

Suite *s21_tetris_suite_create() {
  Suite *suite = suite_create("s21_tetris_test");
  TCase *tc_core = tcase_create("tcase_core_s21_tetris_test");

  tcase_add_test(tc_core, s21_tetris_test_1);
  tcase_add_test(tc_core, s21_tetris_test_2);
  tcase_add_test(tc_core, s21_tetris_test_3);
  tcase_add_test(tc_core, s21_tetris_test_4);
  tcase_add_test(tc_core, s21_tetris_test_5);
  tcase_add_test(tc_core, s21_tetris_test_6);
  tcase_add_test(tc_core, s21_tetris_test_7);
  tcase_add_test(tc_core, s21_tetris_test_8);
  tcase_add_test(tc_core, s21_tetris_test_9);
  tcase_add_test(tc_core, s21_tetris_test_10);
  tcase_add_test(tc_core, s21_tetris_test_11);
  tcase_add_test(tc_core, s21_tetris_test_12);
  tcase_add_test(tc_core, s21_tetris_test_13);
  tcase_add_test(tc_core, s21_tetris_test_14);
  tcase_add_test(tc_core, s21_tetris_test_15);
  tcase_add_test(tc_core, s21_tetris_test_16);
  tcase_add_test(tc_core, s21_tetris_test_17);
  tcase_add_test(tc_core, s21_tetris_test_18);
  tcase_add_test(tc_core, s21_tetris_test_19);
  tcase_add_test(tc_core, s21_tetris_test_20);
  tcase_add_test(tc_core, s21_tetris_test_21);
  tcase_add_test(tc_core, s21_tetris_test_22);
  tcase_add_test(tc_core, s21_tetris_test_23);
  tcase_add_test(tc_core, s21_tetris_test_24);
  tcase_add_test(tc_core, s21_tetris_test_25);
  tcase_add_test(tc_core, s21_tetris_test_26);
  tcase_add_test(tc_core, s21_tetris_test_27);
  tcase_add_test(tc_core, s21_tetris_test_28);
  tcase_add_test(tc_core, s21_tetris_test_29);
  tcase_add_test(tc_core, s21_tetris_test_30);
  tcase_add_test(tc_core, s21_tetris_test_31);
  tcase_add_test(tc_core, s21_tetris_test_32);
  tcase_add_test(tc_core, s21_tetris_test_33);

  suite_add_tcase(suite, tc_core);

  return suite;
}

int main() {
  int failed_count = 0;

  Suite *suite = s21_tetris_suite_create();
  SRunner *suite_runner = srunner_create(suite);

  srunner_run_all(suite_runner, CK_NORMAL);
  failed_count = srunner_ntests_failed(suite_runner);
  srunner_free(suite_runner);

  return failed_count != 0 && !SHOW_FAILED ? EXIT_FAILURE : EXIT_SUCCESS;
}
