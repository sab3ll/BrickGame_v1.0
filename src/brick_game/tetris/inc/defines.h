#ifndef BACKEND_DEFINES_H
#define BACKEND_DEFINES_H

#define PI_2 1.57079632679489661923

// Кол-во очков в зависимости от заполненных рядов
#define SCORE_1 100   // 1 ряд
#define SCORE_2 300   // 2 ряда
#define SCORE_3 700   // 3 ряда
#define SCORE_4 1500  // 4 ряда

// Путь к файлу с рекордом
#define DATAFILE_PATH "./highscores"

// Параметры игрового поля
#define FIELD_HEIGHT 26
#define FIELD_WIDTH 16
#define BORDER_SIZE 3

// Игровые параметры
#define MIN_LEVEL 1
#define MAX_LEVEL 10
#define MIN_SPEED 1
#define MAX_SPEED 10
#define SPEED_RATE 0.15
#define THRESHOLD 600

// Шаблоны тетрамино
#define TETRAMINO_COUNT 7  // Количество тетрамино
#define COORDINATE_COUNT 8  // Общее количество координат (4 пары)
#define TETRAMINO_HEIGHT 2  // Высота тетрамино
#define TETRAMINO_WIDTH 4   // Ширина тетрамино
#define ROTATION_MIN 0  // Минимальное положение вращения
#define ROTATION_MAX 3  // Максимальное положение вращения

// Макросы на клавиши
#define P 112
#define SPACE 32
#define ESCAPE 27
#define KEY_ENTR 10
#define NO_INPUT -1

#endif
