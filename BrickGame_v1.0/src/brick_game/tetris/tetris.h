#ifndef TETRIS_H_
#define TETRIS_H_

#include "backend_tetris.h"
#include "fsm.h"

tetris_state game_loop(GameInfo_t *gameInfo, UserAction_t sig);

#endif