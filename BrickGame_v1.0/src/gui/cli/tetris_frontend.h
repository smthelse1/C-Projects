#ifndef BRICK_GAME_FRONTEND_H_
#define BRICK_GAME_FRONTEND_H_

#include <ncurses.h>
#include <string.h>

#include "../../brick_game/tetris/defines.h"
#include "../../brick_game/tetris/objects.h"

UserAction_t get_signal(int user_input);
void print_overlay(void);
void print_rectangle(int top_y, int bottom_y, int left_x, int right_x);
void print_stats(GameInfo_t *stats);
void print_board(GameInfo_t *board);
void print_banner(GameInfo_t *stats);
void print_next_section(GameInfo_t *stats);
void print_pause();
void select_game(int selectedGame);
void clear_select_game_screen();
GameInfo_t *change_GameInfo_t(GameInfo_t *gameInfo);
GameInfo_t updateCurrentState();

#endif