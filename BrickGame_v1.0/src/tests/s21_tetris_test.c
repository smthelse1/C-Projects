#include <check.h>

#include "../brick_game/tetris/fsm.h"

void clearInfo(GameInfo_t *gameInfo) {
  gameInfo->level = 0;
  gameInfo->score = 0;
  gameInfo->speed = 1;
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 10; j++) {
      gameInfo->field[i][j] = 0;
    }
  }
}

START_TEST(test_check_lines_field) {
  GameInfo_t *gameInfo = get_gameInfo(NULL);
  clearInfo(gameInfo);
  for (int i = 0; i < 20; i++) {
    gameInfo->field[10][i] = 1;
  }
  ck_assert_int_eq(gameInfo->field[10][0], 1);
  check_full_line(gameInfo);
  ck_assert_int_eq(gameInfo->field[10][0], 0);
}

int main(void) {
  Suite *s1 = suite_create("Core");
  TCase *tc1_1 = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  int nf;
  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, test_check_lines_field);
  srunner_run_all(sr, CK_NORMAL);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);
  return nf == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}