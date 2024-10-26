#include "../../brick_game.h"

void colors_fnc() {
  start_color();
  init_pair(1, COLOR_CYAN, COLOR_WHITE);
  init_pair(2, COLOR_CYAN, COLOR_CYAN);
  init_pair(3, COLOR_WHITE, COLOR_WHITE);
  init_pair(4, COLOR_WHITE, COLOR_CYAN);
}

void print_overlay(GameInfo_t *info, WINDOW *field, GameState_t *state) {
  print_border(field, *state);
  print_field(info, field);
  clear_text(field);
  if (*state == START) {
    print_start_text(field);
  } else if (*state == GAMEOVER || *state == WIN) {
    print_end_text(info, field, *state);
  } else
    print_text(info, field);
}

void print_border(WINDOW *field, GameState_t state) {
  wattron(field, COLOR_PAIR(4));
  box(field, 0, 0);
  if (state != START) {
    for (int i = 1; i < FIELD_Y + 1; i++) {
      mvwaddch(field, i, (FIELD_X + 1), ACS_VLINE);
    }
    mvwaddch(field, 0, (FIELD_X + 1), ACS_TTEE);
    mvwaddch(field, FIELD_Y + 1, (FIELD_X + 1), ACS_BTEE);
  } else {
    for (int i = 1; i < FIELD_Y + 1; i++) {
      mvwaddch(field, i, (FIELD_X + 1), ' ');
    }
  }
  wattroff(field, COLOR_PAIR(4));
}

void print_field(GameInfo_t *info, WINDOW *field) {
  for (int i = 0; i < FIELD_Y; i++) {
    for (int j = 0; j < FIELD_X; j++) {
      if (info->field[i][j] == 1) {
        wattron(field, COLOR_PAIR(3));
        mvwprintw(field, i + 1, j + 1, "#");
        wattroff(field, COLOR_PAIR(3));
      } else {
        wattron(field, COLOR_PAIR(2));
        mvwprintw(field, i + 1, j + 1, " ");
        wattroff(field, COLOR_PAIR(2));
      }
    }
  }
}

void clear_text(WINDOW *field) {
  wattron(field, COLOR_PAIR(2));
  for (int i = 0; i < FIELD_Y; i++) {
    for (int j = FIELD_X + 1; j < FIELD_X + TEXT_X - 2; j++) {
      mvwaddch(field, i + 1, j + 1, ' ');
    }
  }
  wattroff(field, COLOR_PAIR(2));
}

void print_start_text(WINDOW *field) {
  wattron(field, COLOR_PAIR(4));
  mvwprintw(field, (FIELD_Y - 3) / 2 + 1, (FIELD_X + TEXT_X - 2 - 22) / 2 + 1,
            "PRESS \"ENTER\" TO START");
  mvwprintw(field, (FIELD_Y - 3) / 2 + 3, (FIELD_X + TEXT_X - 2 - 16) / 2 + 1,
            "PRESS \"Q\" TO QUIT");
  wattroff(field, COLOR_PAIR(4));
}

void print_end_text(GameInfo_t *info, WINDOW *field, GameState_t state) {
  wattron(field, COLOR_PAIR(4));
  if (state == GAMEOVER) {
    mvwprintw(field, 2, FIELD_X + 4, "GAMEOVER!");
    mvwprintw(field, 8, FIELD_X + 4, "YOUR LEVEL: %d", info->level);
  } else {
    mvwprintw(field, 2, FIELD_X + 4, "CONGRATULATIONS!");
  }
  mvwprintw(field, 4, FIELD_X + 4, "HIGH SCORE: %d", info->high_score);
  mvwprintw(field, 6, FIELD_X + 4, "YOUR SCORE: %d", info->score);
  mvwprintw(field, 12, FIELD_X + 4, "PRESS \"ENTER\" TO START");
  mvwprintw(field, 14, FIELD_X + 4, "PRESS \"Q\" TO QUIT");
  wattroff(field, COLOR_PAIR(4));
}

void print_text(GameInfo_t *info, WINDOW *field) {
  wattron(field, COLOR_PAIR(4));
  mvwprintw(field, 2, FIELD_X + 4, "SCORE: %d", info->score);
  mvwprintw(field, 4, FIELD_X + 4, "HIGH SCORE: %d", info->high_score);
  mvwprintw(field, 6, FIELD_X + 4, "LEVEL: %d", info->level);
  mvwprintw(field, 8, FIELD_X + 4, "NEXT FIGURE:");
  for (int i = 0; i < NEXT_Y; i++) {
    for (int j = 0; j < NEXT_X; j++) {
      if (info->next[i][j] == 1) {
        wattron(field, COLOR_PAIR(3));
        mvwaddch(field, i + 10, j + FIELD_X + 6, '#');
      }
    }
    wattron(field, COLOR_PAIR(4));
  }
  mvwprintw(field, 15, FIELD_X + 4, "\"A\" - LEFT, \"D\" - RIGHT");
  mvwprintw(field, 17, FIELD_X + 4, "\"S\" - DOWN, \"W\" - ROTATE");
  mvwprintw(field, 19, FIELD_X + 4, "\"Q\" - QUIT, \"P\" - PAUSE");
  wattroff(field, COLOR_PAIR(4));
}