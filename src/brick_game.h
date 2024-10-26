#ifndef BRICK_GAME_H
#define BRICK_GAME_H

#include <locale.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define FIELD_X 10 * 2
#define FIELD_Y 20
#define TEXT_X 30

#define NEXT_X 8
#define NEXT_Y 4

#define STEP_X 2
#define STEP_Y 1

#define ENTER_KEY 13  // enter
#define PAUSE_KEY 'p'
#define TERMINATE_KEY 'q'
#define LEFT_KEY 'a'
#define RIGHT_KEY 'd'
#define UP_KEY 'w'
#define DOWN_KEY 's'

#define LEVEL_MAX 10
#define DELAY 430000

typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

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

typedef enum {
  START = 0,
  SPAWN,
  MOVING,
  SHIFTING,
  ATTACHING,
  PAUSE,
  GAMEOVER,
  WIN,
  EXIT_STATE,
} GameState_t;

typedef struct {
  int **field;
  int x;
  int y;
  int type;
  int next_type;
  int size_x;
  int size_y;
  int rotate;
} Figure_t;

// fsm
void fsm(UserAction_t action, GameState_t *state, GameInfo_t *info,
         int **game_field, Figure_t *current_figure, WINDOW *field,
         clock_t *curr_time, clock_t *start_time);

// start
void start_info(GameInfo_t *info, Figure_t *current_figure);
int change_position(int x);

// helpers
int **create_matrix(int y, int x);
void free_matrix(int N, int **matrix);
void free_fields(GameInfo_t *info, int **game_field, Figure_t *current_figure);
void combine_fields(GameInfo_t *info, int **game_field,
                    Figure_t *current_figure);
void figure_to_field(Figure_t *cf, int **game_field);

// actions
UserAction_t userInput(int user_input);
void move_left(int **game_field, Figure_t *current_figure);
void move_right(int **game_field, Figure_t *current_figure);
void rotate(int **game_field, Figure_t *current_figure);
int move_down(int **game_field, Figure_t *current_figure);
int check_rotate(int **game_field, Figure_t *figure);
int check_collide_x(int **game_field, Figure_t *current_figure, int key);
int check_collide_y(int **game_field, Figure_t *current_figure);

// figures
void next_figure(GameInfo_t *info, int **game_field, Figure_t *current_figure);
void create_figure(int **figure, int type, int rotate);

// score
void score_fnc(GameInfo_t *info, int **game_field);
void delete_string(int str, int **game_field);
void update_high_score(GameInfo_t *info);

// gameover
int check_gameover(GameInfo_t *info);
void gameover(UserAction_t action, GameInfo_t *info, int **game_field,
              Figure_t *current_figure);

// frontend
void colors_fnc();
void print_overlay(GameInfo_t *info, WINDOW *field, GameState_t *state);
void print_border(WINDOW *field, GameState_t state);
void print_field(GameInfo_t *info, WINDOW *field);
void clear_text(WINDOW *field);
void print_start_text(WINDOW *field);
void print_end_text(GameInfo_t *info, WINDOW *field, GameState_t state);
void print_text(GameInfo_t *info, WINDOW *field);

void game_loop(WINDOW *field);

#endif