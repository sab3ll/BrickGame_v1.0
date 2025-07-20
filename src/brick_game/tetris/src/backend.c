#include "backend.h"

int figures[TETRAMINO_COUNT][COORDINATE_COUNT] = {
    {0, -1, 0, 0, 0, 1, 0, 2},    // I
    {-1, -1, 0, -1, 0, 0, 0, 1},  // J
    {0, -1, 0, 0, 0, 1, -1, 1},   // L
    {-1, 0, -1, 1, 0, 0, 0, 1},   // O
    {0, -1, 0, 0, -1, 0, -1, 1},  // S
    {0, -1, 0, 0, -1, 0, 0, 1},   // T
    {-1, -1, -1, 0, 0, 0, 0, 1},  // Z
};

void initParams(GameParams_t *prms) {
  prms->info->field = initMatrix(FIELD_HEIGHT, FIELD_WIDTH);
  resetField(prms);
  prms->info->next = initMatrix(TETRAMINO_HEIGHT, TETRAMINO_WIDTH);
  genTetramino(prms->info->next);
  genHighScore(prms);
  prms->info->score = 0;
  prms->info->level = MIN_LEVEL;
  prms->info->speed = MIN_SPEED;
  prms->info->pause = 0;
  prms->figure->typeNext = genTetramino(prms->info->next);
  prms->state = Menu_main;
  prms->uact = Up;
  prms->ch = Play;
}

void genHighScore(GameParams_t *prms) {
  FILE *fp = fopen(DATAFILE_PATH, "r");
  if (!fp) {
    prms->info->high_score = 0;
    fp = fopen(DATAFILE_PATH, "w");
    fprintf(fp, "0\n");
  } else {
    int getHighScore;
    fscanf(fp, "%d\n", &getHighScore);
    prms->info->high_score = getHighScore;
  }
  fclose(fp);
}

void resetField(GameParams_t *prms) {
  for (int i = 0; i < FIELD_HEIGHT; i++)
    for (int j = 0; j < FIELD_WIDTH; j++)
      prms->info->field[i][j] =
          (i > FIELD_HEIGHT - BORDER_SIZE - 1 || j < BORDER_SIZE ||
           j > FIELD_WIDTH - BORDER_SIZE - 1)
              ? 1
              : 0;
}

int genTetramino(int **next) {
  int type = rand() % TETRAMINO_COUNT;
  for (int row = 0; row < TETRAMINO_HEIGHT; row++)
    for (int col = 0; col < TETRAMINO_WIDTH; col++) next[row][col] = 0;
  for (int i = 1; i < 8; i += 2)
    next[figures[type][i - 1] + 1][figures[type][i] + 1] = type + 1;
  return type;
}

void initGame(GameParams_t *prms) {
  FILE *fp = fopen(DATAFILE_PATH, "r");
  int highScore;
  fscanf(fp, "%d\n", &highScore);
  prms->info->high_score = highScore;
  fclose(fp);
  prms->info->score = 0;
  prms->info->level = MIN_LEVEL;
  prms->info->speed = MIN_SPEED;
}

void spawnNextTetramino(GameParams_t *prms) {
  prms->figure->type = prms->figure->typeNext;
  prms->figure->x = FIELD_WIDTH / 2;
  prms->figure->y = 2;
  prms->figure->rotation = 0;
  prms->figure->typeNext = genTetramino(prms->info->next);
  updateTetramino(prms);
}

void updateTetramino(GameParams_t *prms) {
  int figure_x = prms->figure->x;
  int figure_y = prms->figure->y;
  int type = prms->figure->type;
  int rotation = prms->figure->rotation;
  for (int i = 1; i < 8; i += 2) {
    int field_x = (int)round(figures[type][i] * cos(PI_2 * rotation) +
                             figures[type][i - 1] * sin(PI_2 * rotation));
    int field_y = (int)round(-figures[type][i] * sin(PI_2 * rotation) +
                             figures[type][i - 1] * cos(PI_2 * rotation));
    prms->info->field[field_y + figure_y][field_x + figure_x] = type + 1;
  }
}

bool isCollide(GameParams_t *prms) {
  int figure_x = prms->figure->x;
  int figure_y = prms->figure->y;
  int type = prms->figure->type;
  int rotation = prms->figure->rotation;
  bool isCollide = false;
  for (int i = 1; i < 8 && !isCollide; i += 2) {
    int field_x = (int)round(figures[type][i] * cos(PI_2 * rotation) +
                             figures[type][i - 1] * sin(PI_2 * rotation));
    int field_y = (int)round(-figures[type][i] * sin(PI_2 * rotation) +
                             figures[type][i - 1] * cos(PI_2 * rotation));
    if (prms->info->field[field_y + figure_y][field_x + figure_x])
      isCollide = true;
  }
  return isCollide;
}

void clearTetramino(GameParams_t *prms) {
  int figure_x = prms->figure->x;
  int figure_y = prms->figure->y;
  int type = prms->figure->type;
  int rotation = prms->figure->rotation;
  for (int i = 1; i < 8; i += 2) {
    int field_x = (int)round(figures[type][i] * cos(PI_2 * rotation) +
                             figures[type][i - 1] * sin(PI_2 * rotation));
    int field_y = (int)round(-figures[type][i] * sin(PI_2 * rotation) +
                             figures[type][i - 1] * cos(PI_2 * rotation));
    prms->info->field[field_y + figure_y][field_x + figure_x] = 0;
  }
}

int countFullRows(GameParams_t *prms) {
  int rows = 0;
  for (int row = FIELD_HEIGHT - BORDER_SIZE - 1; row > 2; row--) {
    bool fl = true;
    while (fl) {
      int rowBlocks = 0;
      for (int col = 3; col < FIELD_WIDTH - 3; col++)
        if (prms->info->field[row][col]) rowBlocks++;
      if (rowBlocks == FIELD_WIDTH - 6) {
        rows++;
        for (int i = row; i > 1; i--)
          for (int col = BORDER_SIZE; col < FIELD_WIDTH - BORDER_SIZE; col++)
            prms->info->field[i][col] = prms->info->field[i - 1][col];
      } else
        fl = false;
    }
  }
  return rows;
}

void increaseSpeed(GameParams_t *prms) {
  int newLevel = prms->info->score / THRESHOLD + 1;
  prms->info->level = (newLevel <= MAX_LEVEL) ? newLevel : MAX_LEVEL;
  prms->info->speed = prms->info->level;
}

void addScore(GameParams_t *prms) {
  int rows = 0;
  rows = countFullRows(prms);
  switch (rows) {
    case 0:
      break;
    case 1:
      prms->info->score += SCORE_1;
      break;
    case 2:
      prms->info->score += SCORE_2;
      break;
    case 3:
      prms->info->score += SCORE_3;
      break;
    default:
      prms->info->score += SCORE_4;
      break;
  }
  if (prms->info->score > prms->info->high_score)
    updateHiScore(prms, prms->info->score);
}

void updateHiScore(GameParams_t *prms, int score) {
  prms->info->high_score = score;
  FILE *fp = fopen(DATAFILE_PATH, "w");
  fprintf(fp, "%d\n", prms->info->high_score);
  fclose(fp);
}

int **initMatrix(int rows, int cols) {
  int **arr = (int **)calloc(rows, sizeof(int *));
  if (arr == NULL) {
    fprintf(stderr, "Memory allocation error\n");
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < rows; i++) {
    arr[i] = (int *)calloc(cols, sizeof(int));
    if (arr[i] == NULL) {
      fprintf(stderr, "Memory allocation error\n");
      for (int j = 0; j < i; j++) {
        free(arr[j]);
      }
      free(arr);
      exit(EXIT_FAILURE);
    }
    for (int j = 0; j < cols; j++) {
      arr[i][j] = 1;
    }
  }
  return arr;
}

void freeMatrix(int **matrix, int rows) {
  for (int i = 0; i < rows; i++) {
    free(matrix[i]);
  }
  free(matrix);
}

void freeMemory(GameParams_t *prms) {
  if (prms->info->field) {
    freeMatrix(prms->info->field, FIELD_HEIGHT);
    prms->info->field = NULL;
  }
  if (prms->info->next) {
    freeMatrix(prms->info->next, TETRAMINO_HEIGHT);
    prms->info->next = NULL;
  }
}
