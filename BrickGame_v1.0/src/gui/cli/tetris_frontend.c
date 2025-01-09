#include "tetris_frontend.h"

UserAction_t get_signal(int user_input) {
  UserAction_t rc = -1;

  if (user_input == KEY_UP) rc = Up;
  if (user_input == KEY_DOWN)
    rc = Down;
  else if (user_input == KEY_LEFT)
    rc = Left;
  else if (user_input == KEY_RIGHT)
    rc = Right;
  else if (user_input == ESCAPE)
    rc = Terminate;
  else if (user_input == ENTER_KEY)
    rc = Action;
  else if (user_input == KEY_BACKSPACE)
    rc = Pause;

  return rc;
}

void print_overlay(void) {
  print_rectangle(TOP_Y, BOT_Y, LEFT_X, RIGHT_X);
  print_rectangle(NEXT_TOP_Y, NEXT_BOT_Y, NEXT_LEFT_X, NEXT_RIGHT_X);

  mvprintw(0, 24, "NEXT");
  mvprintw(5, 27, "LEVEL");
  mvprintw(8, 24, "SPEED");
  mvprintw(11, 24, "SCORE");
  mvprintw(14, 24, "HIGH SCORE");

  mvprintw(17, 24, "ESC - EXIT");
  mvprintw(18, 24, "BACKSPACE - PAUSE");
  mvprintw(19, 24, "ARROWS - MOVE");
  mvprintw(20, 24, "ENTER - ROTATE");

  mvprintw(10, 1, "PRESS ENTER TO START");
}
void print_rectangle(int top_y, int bottom_y, int left_x, int right_x) {
  for (int y = top_y; y < bottom_y + 1; y++) {
    mvprintw(y, left_x, "|");
    mvprintw(y, right_x, "|");
  }
  for (int y = top_y; y < bottom_y + 1; y++) {
    for (int x = left_x; x < right_x; x++) {
      if (x % 2 == 1) {
        mvaddch(y, x + 1, '.');
      }
    }
  }
  for (int x = left_x; x < right_x + 1; x++) {
    mvaddch(bottom_y, x, '-');
  }
}
void print_stats(GameInfo_t *stats) {
  mvprintw(6, 29, "%d", stats->level);
  mvprintw(9, 24, "%d", stats->speed);
  mvprintw(12, 24, "%d", stats->score);
  mvprintw(15, 24, "%d", stats->high_score);
}
void print_board(GameInfo_t *board) {
  for (int x = 0; x < 10; x++) {
    for (int y = 0; y < 20; y++) {
      if (board->field[x][y] == 1) {
        mvaddch(y + TOP_Y, x * 2 + (LEFT_X + 1), '[');
        mvaddch(y + TOP_Y, x * 2 + 1 + (LEFT_X + 1), ']');
      } else {
        mvaddch(y + TOP_Y, x * 2 + (LEFT_X + 1), ' ');
        mvaddch(y + TOP_Y, x * 2 + 1 + (LEFT_X + 1), '.');
      }
    }
  }
}
void print_banner(GameInfo_t *stats) {
  mvprintw(6, 4, "            ");
  mvprintw(7, 4, "  GAMEOVER  ");
  mvprintw(8, 4, "            ");
  mvprintw(9, 4, "  Level: %d  ", stats->level);
  mvprintw(10, 4, "              ");
  mvprintw(11, 3, "  Score: %d  ", stats->score);
  mvprintw(12, 3, "                 ");
  mvprintw(13, 2, "  High Score: %d  ", stats->high_score);
  mvprintw(14, 2, "                      ");
  mvprintw(15, 1, "  Press ESC to Quit  ");
  mvprintw(16, 1, "                     ");
}
void print_next_section(GameInfo_t *stats) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (stats->next[j][i] == 1) {
        mvprintw(NEXT_TOP_Y + j, NEXT_LEFT_X + 1 + i * 2, "[]");
      } else {
        mvprintw(NEXT_TOP_Y + j, NEXT_LEFT_X + 1 + i * 2, " .");
      }
    }
  }
}

void print_pause() { mvprintw(10, 4, " GAME PAUSED "); }

GameInfo_t updateCurrentState() {
  GameInfo_t *gameInfo = change_GameInfo_t(NULL);
  if (gameInfo->pause == 1) {
    print_pause(gameInfo);
  } else {
    print_board(gameInfo);
    print_next_section(gameInfo);
    print_stats(gameInfo);
  }
  return *gameInfo;
}

GameInfo_t *change_GameInfo_t(GameInfo_t *gameInfo) {
  static GameInfo_t *Info;
  if (gameInfo == NULL) return Info;
  Info = gameInfo;
  return Info;
}

void select_game(int selectedGame) {
  mvprintw(4, 7, "Stephenj TETRIS:");
  mvprintw(5, 4, "   PreSS Enter To Start");
  switch (selectedGame) {
    case 0:
      mvprintw(5, 4, "[]");
      break;
    default:
      break;
  }
}

void clear_select_game_screen() {
  mvprintw(4, 7, "                ");
  mvprintw(5, 4, "                          ");
  mvprintw(8, 4, "                       ");
  mvprintw(10, 4, "                       ");
}