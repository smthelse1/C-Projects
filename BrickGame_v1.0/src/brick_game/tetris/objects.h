#ifndef OBJECTS_H
#define OBJECTS_H

#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

typedef enum { I = 0, J, L, O, S, T, Z } block;

typedef struct {
  int x1;
  int y1;

  int x2;
  int y2;

  int x3;
  int y3;

  int x4;
  int y4;

  block type;
  int rotate_state;
} Tetramino;

typedef enum { first = 0, second, third, fourth } rotateState;

typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

#endif