#include "brick_game.h"

int main() {
  srand(time(NULL));
  initscr();  //инициализируем библиотеку
  cbreak();  //Не использовать буфер для функции getch()
  raw();
  nonl();
  noecho();  //Не печатать на экране то, что набирает пользователь на клавиатуре
  curs_set(0);  //Убрать курсор
  WINDOW *field = newwin(FIELD_Y + 2, FIELD_X + TEXT_X, 0, 0);  //игровое поле
  keypad(field, TRUE);  // позволяет читать нажатия специальных клавиш
  nodelay(field, TRUE);
  colors_fnc();
  game_loop(field);
  endwin();
  return 0;
}

void game_loop(WINDOW *field) {
  GameInfo_t info;
  GameState_t state = START;
  Figure_t current_figure;
  clock_t start_time = clock();
  clock_t curr_time = clock();
  int **game_field = create_matrix(FIELD_Y, FIELD_X);
  start_info(&info, &current_figure);
  bool break_flag = TRUE;
  print_overlay(&info, field, &state);

  while (break_flag) {
    if (state == EXIT_STATE) break_flag = FALSE;
    fsm(userInput(wgetch(field)), &state, &info, game_field, &current_figure,
        field, &curr_time, &start_time);
  }
}
