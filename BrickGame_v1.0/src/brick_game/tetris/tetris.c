#include "tetris.h"

#include "../../brick_game/tetris/tetris.h"
#include "../../gui/cli/tetris_frontend.h"

void tetris_game();

/*!

    \brief Точка входа в игровую консоль
*/

tetris_state game_loop(GameInfo_t *gameInfo, UserAction_t sig) {
  static tetris_state state;
  static Tetramino current;
  static block nextBlock;
  static bool fallTime;
  static clock_t clock1;
  if (gameInfo == NULL) {
    fallTime = 0;
    clock1 = clock();
    nextBlock = rand() % 7;
    state = SPAWN;
    current.rotate_state = 0;
    current.type = 0;
    current.x1 = 0;
    current.x2 = 0;
    current.x3 = 0;
    current.x4 = 0;
    current.y1 = 0;
    current.y2 = 0;
    current.y3 = 0;
    current.y4 = 0;
    get_state(&state);
    get_current(&current);
    get_nextBlock(&nextBlock);
    get_fallTime(&fallTime);
  } else {
    get_gameInfo(gameInfo);
    if (state == START || state == MOVING || state == GAMEOVER ||
        state == PAUSE) {
    }
    clock_t clock2 = clock();
    if (clock2 - clock1 >= 12000 - ((clock_t)gameInfo->speed * 150 + 10000)) {
      clock1 = clock2;
      fallTime = 1;
      get_fallTime(&fallTime);
    }
    userInput(sig, 1);
    fallTime = 0;
    get_fallTime(&fallTime);
  }
  return state;
}

/*!

    \brief Вход в игру Тетрис
*/
void tetris_game() {
  GameInfo_t gameInfo;
  infoInit(&gameInfo);
  change_GameInfo_t(&gameInfo);
  int state = -1;
  UserAction_t sig = -1;
  game_loop(NULL, sig);

  while (state != EXIT_STATE && state != GAMEOVER) {
    if (state == START || state == MOVING || state == PAUSE) {
      sig = get_signal(getch());
    }

    state = game_loop(&gameInfo, sig);
    updateCurrentState();
  }
  if (state == GAMEOVER) {
    print_banner(&gameInfo);
    while (1) {
      sig = get_signal(getch());
      if (sig == Terminate) {
        break;
      }
    }
  }

  infoFree(&gameInfo);
}

int main() {
  initscr();
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);
  timeout(40);
  srand((unsigned int)time(NULL));
  int selectedGame = 0;
  while (1) {
    select_game(selectedGame);
    UserAction_t sig = get_signal(getch());
    if (sig == Down && selectedGame < 2) {
      selectedGame++;
    }

    if (sig == Up && selectedGame > 0) {
      selectedGame--;
    }

    if (sig == Action && selectedGame == 0) {
      break;
    }
    if (sig == Terminate) {
      selectedGame = -1;
      break;
    }
  }
  clear_select_game_screen();
  print_overlay();
  while (1) {
    UserAction_t sig = get_signal(getch());
    if (sig == Action) {
      break;
    }
  }
  if (selectedGame == 0) {
    tetris_game();
  }
  endwin();
  return 0;
}