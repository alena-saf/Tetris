#include "unit_test.h"

START_TEST(init_1) {
  GameInfo_t info;
  Figure_t current_figure;
  start_info(&info, &current_figure);

  ck_assert_int_eq(info.score, 0);

  free_matrix(FIELD_Y, info.field);
  free_matrix(NEXT_Y, info.next);
  free_matrix(NEXT_Y, current_figure.field);
}
END_TEST

START_TEST(init_2) {
  GameInfo_t info;
  Figure_t current_figure;
  start_info(&info, &current_figure);

  ck_assert_int_eq(info.level, 1);

  free_matrix(FIELD_Y, info.field);
  free_matrix(NEXT_Y, info.next);
  free_matrix(NEXT_Y, current_figure.field);
}
END_TEST

START_TEST(init_3) {
  GameInfo_t info;
  Figure_t current_figure;
  start_info(&info, &current_figure);

  ck_assert_int_eq(info.pause, 0);

  free_matrix(FIELD_Y, info.field);
  free_matrix(NEXT_Y, info.next);
  free_matrix(NEXT_Y, current_figure.field);
}
END_TEST

START_TEST(init_4) {
  GameInfo_t info;
  Figure_t current_figure;
  start_info(&info, &current_figure);

  UserAction_t action = userInput(TERMINATE_KEY);
  ck_assert_int_eq(action, Terminate);

  free_matrix(FIELD_Y, info.field);
  free_matrix(NEXT_Y, info.next);
  free_matrix(NEXT_Y, current_figure.field);
}
END_TEST

START_TEST(start_1) {
  GameInfo_t info;
  Figure_t current_figure;
  start_info(&info, &current_figure);

  UserAction_t action = userInput(ENTER_KEY);
  ck_assert_int_eq(action, Start);

  free_matrix(FIELD_Y, info.field);
  free_matrix(NEXT_Y, info.next);
  free_matrix(NEXT_Y, current_figure.field);
}
END_TEST

START_TEST(spawn_1) {
  GameInfo_t info;
  Figure_t current_figure;
  start_info(&info, &current_figure);

  UserAction_t action = userInput(ENTER_KEY);
  action = userInput(TERMINATE_KEY);
  ck_assert_int_eq(action, Terminate);

  free_matrix(FIELD_Y, info.field);
  free_matrix(NEXT_Y, info.next);
  free_matrix(NEXT_Y, current_figure.field);
}
END_TEST

START_TEST(moving_left) {
  GameInfo_t info;
  Figure_t current_figure;
  start_info(&info, &current_figure);

  UserAction_t action = userInput(ENTER_KEY);
  action = userInput(LEFT_KEY);
  ck_assert_int_eq(info.pause, 0);
  ck_assert_int_eq(action, Left);

  free_matrix(FIELD_Y, info.field);
  free_matrix(NEXT_Y, info.next);
  free_matrix(NEXT_Y, current_figure.field);
}
END_TEST

START_TEST(moving_right) {
  GameInfo_t info;
  Figure_t current_figure;
  start_info(&info, &current_figure);

  UserAction_t action = userInput(ENTER_KEY);
  action = userInput(RIGHT_KEY);
  ck_assert_int_eq(info.pause, 0);
  ck_assert_int_eq(action, Right);

  free_matrix(FIELD_Y, info.field);
  free_matrix(NEXT_Y, info.next);
  free_matrix(NEXT_Y, current_figure.field);
}
END_TEST

START_TEST(moving_down) {
  GameInfo_t info;
  Figure_t current_figure;
  start_info(&info, &current_figure);

  UserAction_t action = userInput(ENTER_KEY);
  action = userInput(DOWN_KEY);
  ck_assert_int_eq(info.pause, 0);
  ck_assert_int_eq(action, Down);

  free_matrix(FIELD_Y, info.field);
  free_matrix(NEXT_Y, info.next);
  free_matrix(NEXT_Y, current_figure.field);
}
END_TEST

START_TEST(moving_action) {
  GameInfo_t info;
  Figure_t current_figure;
  start_info(&info, &current_figure);

  UserAction_t action = userInput(ENTER_KEY);
  action = userInput(UP_KEY);
  ck_assert_int_eq(info.pause, 0);
  ck_assert_int_eq(action, Action);

  free_matrix(FIELD_Y, info.field);
  free_matrix(NEXT_Y, info.next);
  free_matrix(NEXT_Y, current_figure.field);
}
END_TEST

START_TEST(moving_pause) {
  GameInfo_t info;
  Figure_t current_figure;
  start_info(&info, &current_figure);

  UserAction_t action = userInput(ENTER_KEY);
  action = userInput(PAUSE_KEY);
  ck_assert_int_eq(action, Pause);

  free_matrix(FIELD_Y, info.field);
  free_matrix(NEXT_Y, info.next);
  free_matrix(NEXT_Y, current_figure.field);
}
END_TEST

START_TEST(fsm_1) {
  WINDOW *field = newwin(FIELD_Y + 2, FIELD_X + TEXT_X, 0, 0);
  GameInfo_t info;
  GameState_t state = MOVING;
  Figure_t current_figure;
  clock_t start_time = clock();
  clock_t curr_time = clock();
  int **game_field = create_matrix(FIELD_Y, FIELD_X);
  start_info(&info, &current_figure);

  UserAction_t action = userInput(TERMINATE_KEY);
  fsm(action, &state, &info, game_field, &current_figure, field, &curr_time,
      &start_time);
  ck_assert_int_eq(state, GAMEOVER);

  free_matrix(FIELD_Y, info.field);
  free_matrix(FIELD_Y, game_field);
  free_matrix(NEXT_Y, info.next);
  free_matrix(NEXT_Y, current_figure.field);
}
END_TEST

START_TEST(fsm_2) {
  WINDOW *field = newwin(FIELD_Y + 2, FIELD_X + TEXT_X, 0, 0);
  GameInfo_t info;
  GameState_t state = START;
  Figure_t current_figure;
  clock_t start_time = clock();
  clock_t curr_time = clock();
  int **game_field = create_matrix(FIELD_Y, FIELD_X);
  start_info(&info, &current_figure);

  UserAction_t action = userInput(TERMINATE_KEY);
  fsm(action, &state, &info, game_field, &current_figure, field, &curr_time,
      &start_time);
  ck_assert_int_eq(state, EXIT_STATE);

  free_matrix(FIELD_Y, info.field);
  free_matrix(FIELD_Y, game_field);
  free_matrix(NEXT_Y, info.next);
  free_matrix(NEXT_Y, current_figure.field);
}
END_TEST

START_TEST(fsm_3) {
  WINDOW *field = newwin(FIELD_Y + 2, FIELD_X + TEXT_X, 0, 0);
  GameInfo_t info;
  GameState_t state = MOVING;
  Figure_t current_figure;
  clock_t start_time = clock();
  clock_t curr_time = clock();
  int **game_field = create_matrix(FIELD_Y, FIELD_X);
  start_info(&info, &current_figure);

  UserAction_t action = userInput(LEFT_KEY);
  current_figure.x = STEP_X;
  fsm(action, &state, &info, game_field, &current_figure, field, &curr_time,
      &start_time);
  ck_assert_int_eq(current_figure.x, 0);
  gameover(action, &info, game_field, &current_figure);

  free_matrix(FIELD_Y, info.field);
  free_matrix(FIELD_Y, game_field);
  free_matrix(NEXT_Y, info.next);
  free_matrix(NEXT_Y, current_figure.field);
}
END_TEST

START_TEST(fsm_4) {
  WINDOW *field = newwin(FIELD_Y + 2, FIELD_X + TEXT_X, 0, 0);
  GameInfo_t info;
  GameState_t state = MOVING;
  Figure_t current_figure;
  clock_t start_time = clock();
  clock_t curr_time = clock();
  int **game_field = create_matrix(FIELD_Y, FIELD_X);
  start_info(&info, &current_figure);

  UserAction_t action = userInput(RIGHT_KEY);
  fsm(action, &state, &info, game_field, &current_figure, field, &curr_time,
      &start_time);
  ck_assert_int_eq(current_figure.x, STEP_X);
  gameover(action, &info, game_field, &current_figure);

  free_matrix(FIELD_Y, info.field);
  free_matrix(FIELD_Y, game_field);
  free_matrix(NEXT_Y, info.next);
  free_matrix(NEXT_Y, current_figure.field);
}
END_TEST

START_TEST(fsm_5) {
  WINDOW *field = newwin(FIELD_Y + 2, FIELD_X + TEXT_X, 0, 0);
  GameInfo_t info;
  GameState_t state = MOVING;
  Figure_t current_figure;
  clock_t start_time = clock();
  clock_t curr_time = clock();
  int **game_field = create_matrix(FIELD_Y, FIELD_X);
  start_info(&info, &current_figure);

  UserAction_t action = userInput(DOWN_KEY);
  fsm(action, &state, &info, game_field, &current_figure, field, &curr_time,
      &start_time);
  ck_assert_int_eq(current_figure.y, STEP_Y);
  gameover(action, &info, game_field, &current_figure);

  free_matrix(FIELD_Y, info.field);
  free_matrix(FIELD_Y, game_field);
  free_matrix(NEXT_Y, info.next);
  free_matrix(NEXT_Y, current_figure.field);
}
END_TEST

START_TEST(fsm_6) {
  WINDOW *field = newwin(FIELD_Y + 2, FIELD_X + TEXT_X, 0, 0);
  GameInfo_t info;
  GameState_t state = MOVING;
  Figure_t current_figure;
  clock_t start_time = clock();
  clock_t curr_time = clock();
  int **game_field = create_matrix(FIELD_Y, FIELD_X);
  start_info(&info, &current_figure);
  current_figure.type = 0;
  current_figure.x = current_figure.y = current_figure.rotate = 0;

  UserAction_t action = userInput(UP_KEY);
  fsm(action, &state, &info, game_field, &current_figure, field, &curr_time,
      &start_time);
  ck_assert_int_eq(current_figure.rotate, 1);
  gameover(action, &info, game_field, &current_figure);

  free_matrix(FIELD_Y, info.field);
  free_matrix(FIELD_Y, game_field);
  free_matrix(NEXT_Y, info.next);
  free_matrix(NEXT_Y, current_figure.field);
}
END_TEST

START_TEST(fsm_7) {
  WINDOW *field = newwin(FIELD_Y + 2, FIELD_X + TEXT_X, 0, 0);
  GameInfo_t info;
  GameState_t state = MOVING;
  Figure_t current_figure;
  clock_t start_time = clock();
  clock_t curr_time = clock();
  int **game_field = create_matrix(FIELD_Y, FIELD_X);
  start_info(&info, &current_figure);

  UserAction_t action = userInput(PAUSE_KEY);
  fsm(action, &state, &info, game_field, &current_figure, field, &curr_time,
      &start_time);
  ck_assert_int_eq(action, Pause);
  gameover(action, &info, game_field, &current_figure);

  free_matrix(FIELD_Y, info.field);
  free_matrix(FIELD_Y, game_field);
  free_matrix(NEXT_Y, info.next);
  free_matrix(NEXT_Y, current_figure.field);
}
END_TEST

START_TEST(fsm_8) {
  WINDOW *field = newwin(FIELD_Y + 2, FIELD_X + TEXT_X, 0, 0);
  GameInfo_t info;
  GameState_t state = MOVING;
  Figure_t current_figure;
  clock_t start_time = clock();
  clock_t curr_time = clock();
  int **game_field = create_matrix(FIELD_Y, FIELD_X);
  start_info(&info, &current_figure);

  UserAction_t action = userInput(ERR);
  fsm(action, &state, &info, game_field, &current_figure, field, &curr_time,
      &start_time);
  ck_assert_int_eq(state, SHIFTING);
  gameover(action, &info, game_field, &current_figure);

  free_matrix(FIELD_Y, info.field);
  free_matrix(FIELD_Y, game_field);
  free_matrix(NEXT_Y, info.next);
  free_matrix(NEXT_Y, current_figure.field);
}
END_TEST

START_TEST(fsm_9) {
  WINDOW *field = newwin(FIELD_Y + 2, FIELD_X + TEXT_X, 0, 0);
  GameInfo_t info;
  GameState_t state = START;
  Figure_t current_figure;
  clock_t start_time = clock();
  clock_t curr_time = clock();
  int **game_field = create_matrix(FIELD_Y, FIELD_X);

  UserAction_t action = Start;
  fsm(action, &state, &info, game_field, &current_figure, field, &curr_time,
      &start_time);
  ck_assert_int_eq(state, SPAWN);
  gameover(action, &info, game_field, &current_figure);

  free_matrix(FIELD_Y, info.field);
  free_matrix(FIELD_Y, game_field);
  free_matrix(NEXT_Y, info.next);
  free_matrix(NEXT_Y, current_figure.field);
}
END_TEST

START_TEST(fsm_10) {
  WINDOW *field = newwin(FIELD_Y + 2, FIELD_X + TEXT_X, 0, 0);
  GameInfo_t info;
  GameState_t state = SPAWN;
  Figure_t current_figure;
  clock_t start_time = clock();
  clock_t curr_time = clock();
  int **game_field = create_matrix(FIELD_Y, FIELD_X);
  start_info(&info, &current_figure);
  UserAction_t action = Start;

  info.level = LEVEL_MAX + 1;
  fsm(action, &state, &info, game_field, &current_figure, field, &curr_time,
      &start_time);
  ck_assert_int_eq(state, WIN);
  gameover(action, &info, game_field, &current_figure);

  free_matrix(FIELD_Y, info.field);
  free_matrix(FIELD_Y, game_field);
  free_matrix(NEXT_Y, info.next);
  free_matrix(NEXT_Y, current_figure.field);
}
END_TEST

START_TEST(fsm_11) {
  WINDOW *field = newwin(FIELD_Y + 2, FIELD_X + TEXT_X, 0, 0);
  GameInfo_t info;
  GameState_t state = SPAWN;
  Figure_t current_figure;
  clock_t start_time = clock();
  clock_t curr_time = clock();
  int **game_field = create_matrix(FIELD_Y, FIELD_X);
  start_info(&info, &current_figure);
  UserAction_t action = Start;

  fsm(action, &state, &info, game_field, &current_figure, field, &curr_time,
      &start_time);
  ck_assert_int_eq(state, SHIFTING);
  gameover(action, &info, game_field, &current_figure);

  free_matrix(FIELD_Y, info.field);
  free_matrix(FIELD_Y, game_field);
  free_matrix(NEXT_Y, info.next);
  free_matrix(NEXT_Y, current_figure.field);
}
END_TEST

START_TEST(fsm_12) {
  WINDOW *field = newwin(FIELD_Y + 2, FIELD_X + TEXT_X, 0, 0);
  GameInfo_t info;
  GameState_t state = SHIFTING;
  Figure_t current_figure;
  clock_t start_time = 0;
  clock_t curr_time = clock();
  int **game_field = create_matrix(FIELD_Y, FIELD_X);
  start_info(&info, &current_figure);
  UserAction_t action = Start;

  fsm(action, &state, &info, game_field, &current_figure, field, &curr_time,
      &start_time);
  ck_assert_int_eq(state, MOVING);
  gameover(action, &info, game_field, &current_figure);

  free_matrix(FIELD_Y, info.field);
  free_matrix(FIELD_Y, game_field);
  free_matrix(NEXT_Y, info.next);
  free_matrix(NEXT_Y, current_figure.field);
}
END_TEST

START_TEST(fsm_13) {
  WINDOW *field = newwin(FIELD_Y + 2, FIELD_X + TEXT_X, 0, 0);
  GameInfo_t info;
  GameState_t state = SHIFTING;
  Figure_t current_figure;
  clock_t start_time = -1 * DELAY;
  clock_t curr_time = clock();
  int **game_field = create_matrix(FIELD_Y, FIELD_X);
  start_info(&info, &current_figure);
  UserAction_t action = Start;

  fsm(action, &state, &info, game_field, &current_figure, field, &curr_time,
      &start_time);
  ck_assert_int_eq(state, MOVING);
  gameover(action, &info, game_field, &current_figure);

  free_matrix(FIELD_Y, info.field);
  free_matrix(FIELD_Y, game_field);
  free_matrix(NEXT_Y, info.next);
  free_matrix(NEXT_Y, current_figure.field);
}
END_TEST

START_TEST(fsm_14) {
  WINDOW *field = newwin(FIELD_Y + 2, FIELD_X + TEXT_X, 0, 0);
  GameInfo_t info;
  GameState_t state = ATTACHING;
  Figure_t current_figure;
  clock_t start_time = clock();
  clock_t curr_time = clock();
  int **game_field = create_matrix(FIELD_Y, FIELD_X);
  start_info(&info, &current_figure);
  UserAction_t action = Start;

  for (int j = 0; j < FIELD_X; j++) info.field[FIELD_Y - 1][j] = 1;
  fsm(action, &state, &info, game_field, &current_figure, field, &curr_time,
      &start_time);
  ck_assert_int_eq(state, SPAWN);
  ck_assert_int_eq(info.score, 100);
  gameover(action, &info, game_field, &current_figure);

  free_matrix(FIELD_Y, info.field);
  free_matrix(FIELD_Y, game_field);
  free_matrix(NEXT_Y, info.next);
  free_matrix(NEXT_Y, current_figure.field);
}
END_TEST

START_TEST(fsm_15) {
  WINDOW *field = newwin(FIELD_Y + 2, FIELD_X + TEXT_X, 0, 0);
  GameInfo_t info;
  GameState_t state = ATTACHING;
  Figure_t current_figure;
  clock_t start_time = clock();
  clock_t curr_time = clock();
  int **game_field = create_matrix(FIELD_Y, FIELD_X);
  start_info(&info, &current_figure);
  UserAction_t action = ERR;

  info.field[0][0] = 1;
  fsm(action, &state, &info, game_field, &current_figure, field, &curr_time,
      &start_time);
  ck_assert_int_eq(state, GAMEOVER);
  gameover(action, &info, game_field, &current_figure);

  free_matrix(FIELD_Y, info.field);
  free_matrix(FIELD_Y, game_field);
  free_matrix(NEXT_Y, info.next);
  free_matrix(NEXT_Y, current_figure.field);
}
END_TEST

START_TEST(fsm_16) {
  WINDOW *field = newwin(FIELD_Y + 2, FIELD_X + TEXT_X, 0, 0);
  GameInfo_t info;
  GameState_t state = PAUSE;
  Figure_t current_figure;
  clock_t start_time = clock();
  clock_t curr_time = clock();
  int **game_field = create_matrix(FIELD_Y, FIELD_X);
  start_info(&info, &current_figure);
  UserAction_t action = Pause;

  fsm(action, &state, &info, game_field, &current_figure, field, &curr_time,
      &start_time);
  ck_assert_int_eq(state, SHIFTING);
  gameover(action, &info, game_field, &current_figure);

  free_matrix(FIELD_Y, info.field);
  free_matrix(FIELD_Y, game_field);
  free_matrix(NEXT_Y, info.next);
  free_matrix(NEXT_Y, current_figure.field);
}
END_TEST

START_TEST(fsm_17) {
  WINDOW *field = newwin(FIELD_Y + 2, FIELD_X + TEXT_X, 0, 0);
  GameInfo_t info;
  GameState_t state = PAUSE;
  Figure_t current_figure;
  clock_t start_time = clock();
  clock_t curr_time = clock();
  int **game_field = create_matrix(FIELD_Y, FIELD_X);
  start_info(&info, &current_figure);
  UserAction_t action = Terminate;

  fsm(action, &state, &info, game_field, &current_figure, field, &curr_time,
      &start_time);
  ck_assert_int_eq(state, GAMEOVER);

  free_matrix(FIELD_Y, info.field);
  free_matrix(FIELD_Y, game_field);
  free_matrix(NEXT_Y, info.next);
  free_matrix(NEXT_Y, current_figure.field);
}
END_TEST

START_TEST(fsm_18) {
  WINDOW *field = newwin(FIELD_Y + 2, FIELD_X + TEXT_X, 0, 0);
  GameInfo_t info;
  GameState_t state = WIN;
  Figure_t current_figure;
  clock_t start_time = clock();
  clock_t curr_time = clock();
  int **game_field = create_matrix(FIELD_Y, FIELD_X);
  start_info(&info, &current_figure);
  UserAction_t action = Terminate;

  fsm(action, &state, &info, game_field, &current_figure, field, &curr_time,
      &start_time);
  ck_assert_int_eq(state, EXIT_STATE);
}
END_TEST

START_TEST(fsm_19) {
  WINDOW *field = newwin(FIELD_Y + 2, FIELD_X + TEXT_X, 0, 0);
  GameInfo_t info;
  GameState_t state = WIN;
  Figure_t current_figure;
  clock_t start_time = clock();
  clock_t curr_time = clock();
  int **game_field = create_matrix(FIELD_Y, FIELD_X);
  start_info(&info, &current_figure);
  UserAction_t action = Start;

  fsm(action, &state, &info, game_field, &current_figure, field, &curr_time,
      &start_time);
  ck_assert_int_eq(state, SPAWN);
  gameover(action, &info, game_field, &current_figure);

  free_matrix(FIELD_Y, info.field);
  free_matrix(FIELD_Y, game_field);
  free_matrix(NEXT_Y, info.next);
  free_matrix(NEXT_Y, current_figure.field);
}
END_TEST

START_TEST(fsm_20) {
  WINDOW *field = newwin(FIELD_Y + 2, FIELD_X + TEXT_X, 0, 0);
  GameInfo_t info;
  GameState_t state = ATTACHING;
  Figure_t current_figure;
  clock_t start_time = clock();
  clock_t curr_time = clock();
  int **game_field = create_matrix(FIELD_Y, FIELD_X);
  start_info(&info, &current_figure);
  UserAction_t action = Start;

  for (int j = 0; j < FIELD_X; j++)
    info.field[FIELD_Y - 1][j] = info.field[FIELD_Y - 2][j] = 1;
  fsm(action, &state, &info, game_field, &current_figure, field, &curr_time,
      &start_time);
  ck_assert_int_eq(state, SPAWN);
  ck_assert_int_eq(info.score, 300);
  gameover(action, &info, game_field, &current_figure);

  free_matrix(FIELD_Y, info.field);
  free_matrix(FIELD_Y, game_field);
  free_matrix(NEXT_Y, info.next);
  free_matrix(NEXT_Y, current_figure.field);
}
END_TEST

START_TEST(fsm_21) {
  WINDOW *field = newwin(FIELD_Y + 2, FIELD_X + TEXT_X, 0, 0);
  GameInfo_t info;
  GameState_t state = ATTACHING;
  Figure_t current_figure;
  clock_t start_time = clock();
  clock_t curr_time = clock();
  int **game_field = create_matrix(FIELD_Y, FIELD_X);
  start_info(&info, &current_figure);
  UserAction_t action = Start;

  for (int j = 0; j < FIELD_X; j++) {
    info.field[FIELD_Y - 1][j] = info.field[FIELD_Y - 2][j] = 1;
    info.field[FIELD_Y - 3][j] = 1;
  }
  fsm(action, &state, &info, game_field, &current_figure, field, &curr_time,
      &start_time);
  ck_assert_int_eq(state, SPAWN);
  ck_assert_int_eq(info.score, 700);
  gameover(action, &info, game_field, &current_figure);

  free_matrix(FIELD_Y, info.field);
  free_matrix(FIELD_Y, game_field);
  free_matrix(NEXT_Y, info.next);
  free_matrix(NEXT_Y, current_figure.field);
}
END_TEST

START_TEST(fsm_22) {
  WINDOW *field = newwin(FIELD_Y + 2, FIELD_X + TEXT_X, 0, 0);
  GameInfo_t info;
  GameState_t state = ATTACHING;
  Figure_t current_figure;
  clock_t start_time = clock();
  clock_t curr_time = clock();
  int **game_field = create_matrix(FIELD_Y, FIELD_X);
  start_info(&info, &current_figure);
  UserAction_t action = Start;

  for (int j = 0; j < FIELD_X; j++) {
    info.field[FIELD_Y - 1][j] = info.field[FIELD_Y - 2][j] = 1;
    info.field[FIELD_Y - 3][j] = info.field[FIELD_Y - 4][j] = 1;
  }
  fsm(action, &state, &info, game_field, &current_figure, field, &curr_time,
      &start_time);
  ck_assert_int_eq(state, SPAWN);
  ck_assert_int_eq(info.score, 1500);
  gameover(action, &info, game_field, &current_figure);

  free_matrix(FIELD_Y, info.field);
  free_matrix(FIELD_Y, game_field);
  free_matrix(NEXT_Y, info.next);
  free_matrix(NEXT_Y, current_figure.field);
}
END_TEST

START_TEST(fsm_23) {
  WINDOW *field = newwin(FIELD_Y + 2, FIELD_X + TEXT_X, 0, 0);
  GameInfo_t info;
  GameState_t state = MOVING;
  Figure_t current_figure;
  clock_t start_time = clock();
  clock_t curr_time = clock();
  int **game_field = create_matrix(FIELD_Y, FIELD_X);
  start_info(&info, &current_figure);
  current_figure.type = 0;
  current_figure.x = current_figure.y = current_figure.rotate = 1;

  int figure[NEXT_Y][NEXT_X] = {0};
  figure[0][0] = figure[0][1] = figure[0][2] = figure[0][3] = 1;
  figure[0][4] = figure[0][5] = figure[0][6] = figure[0][7] = 1;

  UserAction_t action = userInput(UP_KEY);
  fsm(action, &state, &info, game_field, &current_figure, field, &curr_time,
      &start_time);
  int check = 0;
  for (int i = 0; i < NEXT_Y; i++) {
    for (int j = 0; j < NEXT_X; j++) {
      if (current_figure.field[i][j] != figure[i][j]) {
        check = 1;
        break;
      }
    }
  }
  ck_assert_int_eq(check, 0);
  gameover(action, &info, game_field, &current_figure);

  free_matrix(FIELD_Y, info.field);
  free_matrix(FIELD_Y, game_field);
  free_matrix(NEXT_Y, info.next);
  free_matrix(NEXT_Y, current_figure.field);
}

START_TEST(fsm_24) {
  WINDOW *field = newwin(FIELD_Y + 2, FIELD_X + TEXT_X, 0, 0);
  GameInfo_t info;
  GameState_t state = MOVING;
  Figure_t current_figure;
  clock_t start_time = clock();
  clock_t curr_time = clock();
  int **game_field = create_matrix(FIELD_Y, FIELD_X);
  start_info(&info, &current_figure);
  current_figure.type = 1;
  current_figure.x = current_figure.y = current_figure.rotate = 3;

  int figure[NEXT_Y][NEXT_X] = {0};
  figure[0][0] = figure[0][1] = figure[1][0] = figure[1][1] = 1;
  figure[1][2] = figure[1][3] = figure[1][4] = figure[1][5] = 1;

  UserAction_t action = userInput(UP_KEY);
  fsm(action, &state, &info, game_field, &current_figure, field, &curr_time,
      &start_time);
  int check = 0;
  for (int i = 0; i < NEXT_Y; i++) {
    for (int j = 0; j < NEXT_X; j++) {
      if (current_figure.field[i][j] != figure[i][j]) {
        check = 1;
        break;
      }
    }
  }
  ck_assert_int_eq(check, 0);
  gameover(action, &info, game_field, &current_figure);

  free_matrix(FIELD_Y, info.field);
  free_matrix(FIELD_Y, game_field);
  free_matrix(NEXT_Y, info.next);
  free_matrix(NEXT_Y, current_figure.field);
}

START_TEST(fsm_25) {
  WINDOW *field = newwin(FIELD_Y + 2, FIELD_X + TEXT_X, 0, 0);
  GameInfo_t info;
  GameState_t state = MOVING;
  Figure_t current_figure;
  clock_t start_time = clock();
  clock_t curr_time = clock();
  int **game_field = create_matrix(FIELD_Y, FIELD_X);
  start_info(&info, &current_figure);
  current_figure.type = 1;
  current_figure.x = current_figure.y = current_figure.rotate = 0;

  int figure[NEXT_Y][NEXT_X] = {0};
  figure[0][0] = figure[0][1] = figure[0][2] = figure[0][3] = 1;
  figure[1][0] = figure[1][1] = figure[2][0] = figure[2][1] = 1;

  UserAction_t action = userInput(UP_KEY);
  fsm(action, &state, &info, game_field, &current_figure, field, &curr_time,
      &start_time);
  int check = 0;
  for (int i = 0; i < NEXT_Y; i++) {
    for (int j = 0; j < NEXT_X; j++) {
      if (current_figure.field[i][j] != figure[i][j]) {
        check = 1;
        break;
      }
    }
  }
  ck_assert_int_eq(check, 0);
  gameover(action, &info, game_field, &current_figure);

  free_matrix(FIELD_Y, info.field);
  free_matrix(FIELD_Y, game_field);
  free_matrix(NEXT_Y, info.next);
  free_matrix(NEXT_Y, current_figure.field);
}

START_TEST(fsm_26) {
  WINDOW *field = newwin(FIELD_Y + 2, FIELD_X + TEXT_X, 0, 0);
  GameInfo_t info;
  GameState_t state = MOVING;
  Figure_t current_figure;
  clock_t start_time = clock();
  clock_t curr_time = clock();
  int **game_field = create_matrix(FIELD_Y, FIELD_X);
  start_info(&info, &current_figure);
  current_figure.type = 1;
  current_figure.x = current_figure.y = current_figure.rotate = 1;

  int figure[NEXT_Y][NEXT_X] = {0};
  figure[0][0] = figure[0][1] = figure[1][4] = figure[1][5] = 1;
  figure[0][2] = figure[0][3] = figure[0][4] = figure[0][5] = 1;

  UserAction_t action = userInput(UP_KEY);
  fsm(action, &state, &info, game_field, &current_figure, field, &curr_time,
      &start_time);
  int check = 0;
  for (int i = 0; i < NEXT_Y; i++) {
    for (int j = 0; j < NEXT_X; j++) {
      if (current_figure.field[i][j] != figure[i][j]) {
        check = 1;
        break;
      }
    }
  }
  ck_assert_int_eq(check, 0);
  gameover(action, &info, game_field, &current_figure);

  free_matrix(FIELD_Y, info.field);
  free_matrix(FIELD_Y, game_field);
  free_matrix(NEXT_Y, info.next);
  free_matrix(NEXT_Y, current_figure.field);
}

START_TEST(fsm_27) {
  WINDOW *field = newwin(FIELD_Y + 2, FIELD_X + TEXT_X, 0, 0);
  GameInfo_t info;
  GameState_t state = MOVING;
  Figure_t current_figure;
  clock_t start_time = clock();
  clock_t curr_time = clock();
  int **game_field = create_matrix(FIELD_Y, FIELD_X);
  start_info(&info, &current_figure);
  current_figure.type = 1;
  current_figure.x = current_figure.y = current_figure.rotate = 2;

  int figure[NEXT_Y][NEXT_X] = {0};
  figure[0][2] = figure[0][3] = figure[2][2] = figure[2][3] = 1;
  figure[1][2] = figure[1][3] = figure[2][0] = figure[2][1] = 1;

  UserAction_t action = userInput(UP_KEY);
  fsm(action, &state, &info, game_field, &current_figure, field, &curr_time,
      &start_time);
  int check = 0;
  for (int i = 0; i < NEXT_Y; i++) {
    for (int j = 0; j < NEXT_X; j++) {
      if (current_figure.field[i][j] != figure[i][j]) {
        check = 1;
        break;
      }
    }
  }
  ck_assert_int_eq(check, 0);
  gameover(action, &info, game_field, &current_figure);

  free_matrix(FIELD_Y, info.field);
  free_matrix(FIELD_Y, game_field);
  free_matrix(NEXT_Y, info.next);
  free_matrix(NEXT_Y, current_figure.field);
}

START_TEST(fsm_28) {
  WINDOW *field = newwin(FIELD_Y + 2, FIELD_X + TEXT_X, 0, 0);
  GameInfo_t info;
  GameState_t state = MOVING;
  Figure_t current_figure;
  clock_t start_time = clock();
  clock_t curr_time = clock();
  int **game_field = create_matrix(FIELD_Y, FIELD_X);
  start_info(&info, &current_figure);
  current_figure.type = 2;
  current_figure.x = current_figure.y = current_figure.rotate = 0;

  int figure[NEXT_Y][NEXT_X] = {0};
  figure[0][0] = figure[0][1] = figure[2][2] = figure[2][3] = 1;
  figure[1][0] = figure[1][1] = figure[2][0] = figure[2][1] = 1;

  UserAction_t action = userInput(UP_KEY);
  fsm(action, &state, &info, game_field, &current_figure, field, &curr_time,
      &start_time);
  int check = 0;
  for (int i = 0; i < NEXT_Y; i++) {
    for (int j = 0; j < NEXT_X; j++) {
      if (current_figure.field[i][j] != figure[i][j]) {
        check = 1;
        break;
      }
    }
  }
  ck_assert_int_eq(check, 0);
  gameover(action, &info, game_field, &current_figure);

  free_matrix(FIELD_Y, info.field);
  free_matrix(FIELD_Y, game_field);
  free_matrix(NEXT_Y, info.next);
  free_matrix(NEXT_Y, current_figure.field);
}

START_TEST(fsm_29) {
  WINDOW *field = newwin(FIELD_Y + 2, FIELD_X + TEXT_X, 0, 0);
  GameInfo_t info;
  GameState_t state = MOVING;
  Figure_t current_figure;
  clock_t start_time = clock();
  clock_t curr_time = clock();
  int **game_field = create_matrix(FIELD_Y, FIELD_X);
  start_info(&info, &current_figure);
  current_figure.type = 2;
  current_figure.x = current_figure.y = current_figure.rotate = 1;

  int figure[NEXT_Y][NEXT_X] = {0};
  figure[0][0] = figure[0][1] = figure[0][2] = figure[0][3] = 1;
  figure[1][0] = figure[1][1] = figure[0][4] = figure[0][5] = 1;

  UserAction_t action = userInput(UP_KEY);
  fsm(action, &state, &info, game_field, &current_figure, field, &curr_time,
      &start_time);
  int check = 0;
  for (int i = 0; i < NEXT_Y; i++) {
    for (int j = 0; j < NEXT_X; j++) {
      if (current_figure.field[i][j] != figure[i][j]) {
        check = 1;
        break;
      }
    }
  }
  ck_assert_int_eq(check, 0);
  gameover(action, &info, game_field, &current_figure);

  free_matrix(FIELD_Y, info.field);
  free_matrix(FIELD_Y, game_field);
  free_matrix(NEXT_Y, info.next);
  free_matrix(NEXT_Y, current_figure.field);
}

START_TEST(fsm_30) {
  WINDOW *field = newwin(FIELD_Y + 2, FIELD_X + TEXT_X, 0, 0);
  GameInfo_t info;
  GameState_t state = MOVING;
  Figure_t current_figure;
  clock_t start_time = clock();
  clock_t curr_time = clock();
  int **game_field = create_matrix(FIELD_Y, FIELD_X);
  start_info(&info, &current_figure);
  current_figure.type = 2;
  current_figure.x = current_figure.y = current_figure.rotate = 2;

  int figure[NEXT_Y][NEXT_X] = {0};
  figure[0][0] = figure[0][1] = figure[0][2] = figure[0][3] = 1;
  figure[1][2] = figure[1][3] = figure[2][2] = figure[2][3] = 1;

  UserAction_t action = userInput(UP_KEY);
  fsm(action, &state, &info, game_field, &current_figure, field, &curr_time,
      &start_time);
  int check = 0;
  for (int i = 0; i < NEXT_Y; i++) {
    for (int j = 0; j < NEXT_X; j++) {
      if (current_figure.field[i][j] != figure[i][j]) {
        check = 1;
        break;
      }
    }
  }
  ck_assert_int_eq(check, 0);
  gameover(action, &info, game_field, &current_figure);

  free_matrix(FIELD_Y, info.field);
  free_matrix(FIELD_Y, game_field);
  free_matrix(NEXT_Y, info.next);
  free_matrix(NEXT_Y, current_figure.field);
}

START_TEST(fsm_31) {
  WINDOW *field = newwin(FIELD_Y + 2, FIELD_X + TEXT_X, 0, 0);
  GameInfo_t info;
  GameState_t state = MOVING;
  Figure_t current_figure;
  clock_t start_time = clock();
  clock_t curr_time = clock();
  int **game_field = create_matrix(FIELD_Y, FIELD_X);
  start_info(&info, &current_figure);
  current_figure.type = 3;
  current_figure.x = current_figure.y = current_figure.rotate = 0;

  int figure[NEXT_Y][NEXT_X] = {0};
  figure[0][0] = figure[0][1] = figure[0][2] = figure[0][3] = 1;
  figure[1][0] = figure[1][1] = figure[1][2] = figure[1][3] = 1;

  UserAction_t action = userInput(UP_KEY);
  fsm(action, &state, &info, game_field, &current_figure, field, &curr_time,
      &start_time);
  int check = 0;
  for (int i = 0; i < NEXT_Y; i++) {
    for (int j = 0; j < NEXT_X; j++) {
      if (current_figure.field[i][j] != figure[i][j]) {
        check = 1;
        break;
      }
    }
  }
  ck_assert_int_eq(check, 0);
  gameover(action, &info, game_field, &current_figure);

  free_matrix(FIELD_Y, info.field);
  free_matrix(FIELD_Y, game_field);
  free_matrix(NEXT_Y, info.next);
  free_matrix(NEXT_Y, current_figure.field);
}

START_TEST(fsm_32) {
  WINDOW *field = newwin(FIELD_Y + 2, FIELD_X + TEXT_X, 0, 0);
  GameInfo_t info;
  GameState_t state = MOVING;
  Figure_t current_figure;
  clock_t start_time = clock();
  clock_t curr_time = clock();
  int **game_field = create_matrix(FIELD_Y, FIELD_X);
  start_info(&info, &current_figure);
  current_figure.type = 4;
  current_figure.x = current_figure.y = current_figure.rotate = 1;

  int figure[NEXT_Y][NEXT_X] = {0};
  figure[0][2] = figure[0][3] = figure[0][4] = figure[0][5] = 1;
  figure[1][0] = figure[1][1] = figure[1][2] = figure[1][3] = 1;

  UserAction_t action = userInput(UP_KEY);
  fsm(action, &state, &info, game_field, &current_figure, field, &curr_time,
      &start_time);
  int check = 0;
  for (int i = 0; i < NEXT_Y; i++) {
    for (int j = 0; j < NEXT_X; j++) {
      if (current_figure.field[i][j] != figure[i][j]) {
        check = 1;
        break;
      }
    }
  }
  ck_assert_int_eq(check, 0);
  gameover(action, &info, game_field, &current_figure);

  free_matrix(FIELD_Y, info.field);
  free_matrix(FIELD_Y, game_field);
  free_matrix(NEXT_Y, info.next);
  free_matrix(NEXT_Y, current_figure.field);
}

START_TEST(collide_1) {
  Figure_t cf;
  cf.field = create_matrix(NEXT_Y, NEXT_X);
  int **game_field = create_matrix(FIELD_Y, FIELD_X);
  for (int i = 0; i < NEXT_Y; i++) {
    for (int j = 0; j < NEXT_X; j++) {
      cf.field[i][j] = 1;
    }
  }
  cf.x = FIELD_X;
  cf.y = cf.rotate = 0;
  int check = check_collide_x(game_field, &cf, RIGHT_KEY);
  ck_assert_int_eq(check, 1);

  free_matrix(FIELD_Y, game_field);
  free_matrix(NEXT_Y, cf.field);
}

START_TEST(collide_2) {
  Figure_t cf;
  cf.field = create_matrix(NEXT_Y, NEXT_X);
  int **game_field = create_matrix(FIELD_Y, FIELD_X);
  for (int i = 0; i < NEXT_Y; i++) {
    for (int j = 0; j < NEXT_X; j++) {
      cf.field[i][j] = 1;
    }
  }
  cf.x = 0;
  cf.y = cf.rotate = 0;
  int check = check_collide_x(game_field, &cf, LEFT_KEY);
  ck_assert_int_eq(check, 1);

  free_matrix(FIELD_Y, game_field);
  free_matrix(NEXT_Y, cf.field);
}

START_TEST(collide_3) {
  Figure_t cf;
  cf.field = create_matrix(NEXT_Y, NEXT_X);
  int **game_field = create_matrix(FIELD_Y, FIELD_X);
  for (int i = 0; i < NEXT_Y; i++) {
    for (int j = 0; j < NEXT_X; j++) {
      cf.field[i][j] = 1;
    }
  }
  cf.x = FIELD_X;
  cf.y = 0;
  int check = check_rotate(game_field, &cf);
  ck_assert_int_eq(check, 1);

  free_matrix(FIELD_Y, game_field);
  free_matrix(NEXT_Y, cf.field);
}

START_TEST(collide_4) {
  Figure_t cf;
  cf.field = create_matrix(NEXT_Y, NEXT_X);
  int **game_field = create_matrix(FIELD_Y, FIELD_X);
  for (int i = 0; i < NEXT_Y; i++) {
    for (int j = 0; j < NEXT_X; j++) {
      cf.field[i][j] = 1;
    }
  }
  cf.x = 0;
  cf.y = FIELD_Y;
  cf.rotate = 0;
  int check = check_collide_y(game_field, &cf);
  ck_assert_int_eq(check, 1);

  free_matrix(FIELD_Y, game_field);
  free_matrix(NEXT_Y, cf.field);
}

Suite *tetris_suite() {
  Suite *s = suite_create("tetris_suite");
  TCase *tc = tcase_create("tetris_tc");

  tcase_add_test(tc, init_1);
  tcase_add_test(tc, init_2);
  tcase_add_test(tc, init_3);
  tcase_add_test(tc, init_4);
  tcase_add_test(tc, start_1);
  tcase_add_test(tc, spawn_1);
  tcase_add_test(tc, moving_left);
  tcase_add_test(tc, moving_right);
  tcase_add_test(tc, moving_down);
  tcase_add_test(tc, moving_action);
  tcase_add_test(tc, moving_pause);
  tcase_add_test(tc, fsm_1);
  tcase_add_test(tc, fsm_2);
  tcase_add_test(tc, fsm_3);
  tcase_add_test(tc, fsm_4);
  tcase_add_test(tc, fsm_5);
  tcase_add_test(tc, fsm_6);
  tcase_add_test(tc, fsm_7);
  tcase_add_test(tc, fsm_8);
  tcase_add_test(tc, fsm_9);
  tcase_add_test(tc, fsm_10);
  tcase_add_test(tc, fsm_11);
  tcase_add_test(tc, fsm_12);
  tcase_add_test(tc, fsm_13);
  tcase_add_test(tc, fsm_14);
  tcase_add_test(tc, fsm_15);
  tcase_add_test(tc, fsm_16);
  tcase_add_test(tc, fsm_17);
  tcase_add_test(tc, fsm_18);
  tcase_add_test(tc, fsm_19);
  tcase_add_test(tc, fsm_20);
  tcase_add_test(tc, fsm_21);
  tcase_add_test(tc, fsm_22);
  tcase_add_test(tc, fsm_23);
  tcase_add_test(tc, fsm_24);
  tcase_add_test(tc, fsm_25);
  tcase_add_test(tc, fsm_26);
  tcase_add_test(tc, fsm_27);
  tcase_add_test(tc, fsm_28);
  tcase_add_test(tc, fsm_29);
  tcase_add_test(tc, fsm_30);
  tcase_add_test(tc, fsm_31);
  tcase_add_test(tc, fsm_32);
  tcase_add_test(tc, collide_1);
  tcase_add_test(tc, collide_2);
  tcase_add_test(tc, collide_3);
  tcase_add_test(tc, collide_4);

  suite_add_tcase(s, tc);

  return s;
}

int main() {
  Suite *s = tetris_suite();
  SRunner *sr = srunner_create(s);
  int tf = 0;

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_VERBOSE);
  tf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return tf > 0;
}
