#include "../../brick_game.h"

// finite state machine
void fsm(UserAction_t action, GameState_t *state, GameInfo_t *info,
         int **game_field, Figure_t *current_figure, WINDOW *field,
         clock_t *curr_time, clock_t *start_time) {
  if (*state == START) {
    if (action == Start) {
      start_info(info, current_figure);
      *state = SPAWN;
    } else if (action == Terminate) {
      *state = EXIT_STATE;
    }

  } else if (*state == SPAWN) {
    if (info->level > LEVEL_MAX)
      *state = WIN;
    else {
      next_figure(info, game_field, current_figure);
      *state = SHIFTING;
    }

  } else if (*state == MOVING) {
    if (action == Left)
      move_left(game_field, current_figure);
    else if (action == Right)
      move_right(game_field, current_figure);
    else if (action == Down)
      move_down(game_field, current_figure);
    else if (action == Action)
      rotate(game_field, current_figure);
    else if (action == Terminate)
      *state = GAMEOVER;
    else if (action == Pause) {
      info->pause = 1;
      *state = PAUSE;
    } else
      *state = SHIFTING;

  } else if (*state == SHIFTING) {
    *curr_time = clock();
    if ((*curr_time - *start_time) >= (DELAY * (1 - 0.07 * info->speed))) {
      *start_time = *curr_time;
      if (move_down(game_field, current_figure) == 1)
        *state = ATTACHING;
      else
        *state = MOVING;
    } else
      *state = MOVING;
    combine_fields(info, game_field, current_figure);
    print_overlay(info, field, state);

  } else if (*state == ATTACHING) {
    score_fnc(info, game_field);
    if (check_gameover(info) == 0)
      *state = SPAWN;
    else
      *state = GAMEOVER;

  } else if (*state == PAUSE) {
    if (action == Pause) {
      info->pause = 1;
      *state = SHIFTING;
    } else if (action == Terminate)
      *state = GAMEOVER;

  } else if (*state == GAMEOVER || *state == WIN) {
    print_overlay(info, field, state);
    gameover(action, info, game_field, current_figure);
    if (action == Terminate) {
      *state = EXIT_STATE;
    } else if (action == Start) {
      *start_time = clock();
      *state = SPAWN;
    }
  } else if (*state == EXIT_STATE)
    gameover(action, info, game_field, current_figure);
}

// start game
void start_info(GameInfo_t *info, Figure_t *current_figure) {
  info->field = create_matrix(FIELD_Y, FIELD_X);
  info->next = create_matrix(NEXT_Y, NEXT_X);
  info->level = 1;
  info->speed = 1;
  info->pause = 0;
  info->score = 0;

  FILE *fp = fopen("high_score.txt", "r");
  if (fp == NULL)
    info->high_score = 0;
  else {
    char str[15] = {0};
    fread(str, sizeof str[0], 15, fp);
    info->high_score = strtol(str, NULL, 10);
    fclose(fp);
  }

  current_figure->field = create_matrix(NEXT_Y, NEXT_X);
  current_figure->x = 0;
  current_figure->y = 0;
  current_figure->next_type = rand() % 7;
  current_figure->rotate = 0;
}

int change_position(int x) {
  int x_new;
  x_new = x + 2 * (rand() % ((FIELD_X - NEXT_X) / 2));
  return x_new;
}

// helpers
int **create_matrix(int y, int x) {
  int **ptr = calloc(y, sizeof(int *));
  if (ptr == NULL) {
    free(ptr);
  } else {
    for (int i = 0; i < y; i++) {
      ptr[i] = calloc(x, sizeof(int));
      if (ptr[i] == NULL) {
        for (int k = 0; k < i; k++) {
          free(ptr[k]);
        }
        free(ptr);
        ptr = NULL;
        break;
      }
    }
  }
  return ptr;
}

void free_matrix(int N, int **matrix) {
  if (matrix != NULL) {
    for (int i = 0; i < N; i++) {
      free(matrix[i]);
    }
    free(matrix);
    matrix = NULL;
  }
}

void free_fields(GameInfo_t *info, int **game_field, Figure_t *current_figure) {
  free_matrix(FIELD_Y, info->field);
  free_matrix(NEXT_Y, info->next);
  free_matrix(NEXT_Y, current_figure->field);
  for (int i = 0; i < FIELD_Y; i++) {
    for (int j = 0; j < FIELD_X; j++) {
      game_field[i][j] = 0;
    }
  }
}

void combine_fields(GameInfo_t *info, int **game_field, Figure_t *cf) {
  for (int i = 0; i < FIELD_Y; i++) {
    for (int j = 0; j < FIELD_X; j++) {
      info->field[i][j] = game_field[i][j];
    }
  }

  for (int i = 0; i < NEXT_Y; i++) {
    for (int j = 0; j < NEXT_X; j++) {
      if (cf->field[i][j] == 1 && (i + cf->y) < FIELD_Y &&
          (j + cf->x) < FIELD_X)
        info->field[i + cf->y][j + cf->x] = 1;
    }
  }
}

// actions
UserAction_t userInput(int user_input) {
  UserAction_t action = {-1};
  if (user_input == ENTER_KEY)
    action = Start;
  else if (user_input == PAUSE_KEY)
    action = Pause;
  else if (user_input == TERMINATE_KEY)
    action = Terminate;
  else if (user_input == LEFT_KEY)
    action = Left;
  else if (user_input == RIGHT_KEY)
    action = Right;
  else if (user_input == UP_KEY)
    action = Action;
  else if (user_input == DOWN_KEY)
    action = Down;
  return action;
}

void move_left(int **game_field, Figure_t *current_figure) {
  if (check_collide_x(game_field, current_figure, LEFT_KEY) == 0)
    current_figure->x = current_figure->x - STEP_X;
}

void move_right(int **game_field, Figure_t *current_figure) {
  if (check_collide_x(game_field, current_figure, RIGHT_KEY) == 0)
    current_figure->x = current_figure->x + STEP_X;
}

void rotate(int **game_field, Figure_t *cf) {
  Figure_t temp;
  temp.x = cf->x;
  temp.y = cf->y;
  temp.field = create_matrix(NEXT_Y, NEXT_X);
  create_figure(temp.field, cf->type, ((cf->rotate + 1) % 4));
  if (check_rotate(game_field, &temp) == 0) {
    for (int i = 0; i < NEXT_Y; i++) {
      for (int j = 0; j < NEXT_X; j++) {
        cf->field[i][j] = temp.field[i][j];
      }
    }
  }
  cf->rotate = (cf->rotate + 1) % 4;
  free_matrix(NEXT_Y, temp.field);
}

int move_down(int **game_field, Figure_t *current_figure) {
  int result = 1;
  if (check_collide_y(game_field, current_figure) == 0) {
    current_figure->y = current_figure->y + STEP_Y;
    result = 0;
  }
  return result;
}

int check_rotate(int **game_field, Figure_t *figure) {
  int check_collide = 0;
  for (int i = 0; i < NEXT_Y; i++) {
    for (int j = 0; j < NEXT_X; j++) {
      if (figure->field[i][j] == 1 &&
          ((i + figure->y) >= FIELD_Y || (j + figure->x) >= FIELD_X ||
           (game_field[i + figure->y][j + figure->x] == 1))) {
        check_collide = 1;
        break;
        break;
      }
    }
  }
  return check_collide;
}

int check_collide_x(int **game_field, Figure_t *cf, int key) {
  int check_collide = 0;
  if (key == RIGHT_KEY) {
    for (int i = 0; i < NEXT_Y; i++) {
      for (int j = 0; j < NEXT_X; j++) {
        if (cf->field[i][j] == 1 &&
            ((j + cf->x + STEP_X) >= FIELD_X ||
             game_field[i + cf->y][j + cf->x + STEP_X] == 1)) {
          check_collide = 1;
          break;
          break;
        }
      }
    }
  } else if (key == LEFT_KEY) {
    for (int i = 0; i < NEXT_Y; i++) {
      for (int j = 0; j < NEXT_X; j++) {
        if (cf->field[i][j] == 1 &&
            ((j + cf->x - STEP_X) < 0 ||
             game_field[i + cf->y][j + cf->x - STEP_X] == 1)) {
          check_collide = 1;
          break;
          break;
        }
      }
    }
  }
  return check_collide;
}

int check_collide_y(int **game_field, Figure_t *cf) {
  int check_collide = 0;
  for (int i = 0; i < NEXT_Y; i++) {
    for (int j = 0; j < NEXT_X; j++) {
      if (cf->field[i][j] == 1 &&
          ((i + cf->y + STEP_Y) >= FIELD_Y ||
           game_field[i + cf->y + STEP_Y][j + cf->x] == 1)) {
        check_collide = 1;
        break;
        break;
      }
    }
  }
  return check_collide;
}

// figures
void next_figure(GameInfo_t *info, int **game_field, Figure_t *cf) {
  cf->type = cf->next_type;
  create_figure(cf->field, cf->next_type, 0);
  cf->x = change_position(0);
  cf->y = 0;
  combine_fields(info, game_field, cf);
  cf->next_type = rand() % 7;
  cf->rotate = 0;
  create_figure(info->next, cf->next_type, 0);
}

void create_figure(int **figure, int type, int rotate) {
  for (int i = 0; i < NEXT_Y; i++) {
    for (int j = 0; j < NEXT_X; j++) {
      figure[i][j] = 0;
    }
  }
  if (type == 0 && (rotate % 2) == 0) {
    figure[0][0] = figure[0][1] = figure[0][2] = figure[0][3] = 1;
    figure[0][4] = figure[0][5] = figure[0][6] = figure[0][7] = 1;
  } else if (type == 0 && (rotate % 2) == 1) {
    figure[0][0] = figure[0][1] = figure[1][0] = figure[1][1] = 1;
    figure[2][0] = figure[2][1] = figure[3][0] = figure[3][1] = 1;
  } else if (type == 1 && rotate == 0) {
    figure[0][0] = figure[0][1] = figure[1][0] = figure[1][1] = 1;
    figure[1][2] = figure[1][3] = figure[1][4] = figure[1][5] = 1;
  } else if (type == 1 && rotate == 1) {
    figure[0][0] = figure[0][1] = figure[0][2] = figure[0][3] = 1;
    figure[1][0] = figure[1][1] = figure[2][0] = figure[2][1] = 1;
  } else if (type == 1 && rotate == 2) {
    figure[0][0] = figure[0][1] = figure[1][4] = figure[1][5] = 1;
    figure[0][2] = figure[0][3] = figure[0][4] = figure[0][5] = 1;
  } else if (type == 1 && rotate == 3) {
    figure[0][2] = figure[0][3] = figure[2][2] = figure[2][3] = 1;
    figure[1][2] = figure[1][3] = figure[2][0] = figure[2][1] = 1;
  } else if (type == 2 && rotate == 0) {
    figure[0][4] = figure[0][5] = figure[1][0] = figure[1][1] = 1;
    figure[1][2] = figure[1][3] = figure[1][4] = figure[1][5] = 1;
  } else if (type == 2 && rotate == 1) {
    figure[0][0] = figure[0][1] = figure[2][2] = figure[2][3] = 1;
    figure[1][0] = figure[1][1] = figure[2][0] = figure[2][1] = 1;
  } else if (type == 2 && rotate == 2) {
    figure[0][0] = figure[0][1] = figure[0][2] = figure[0][3] = 1;
    figure[1][0] = figure[1][1] = figure[0][4] = figure[0][5] = 1;
  } else if (type == 2 && rotate == 3) {
    figure[0][0] = figure[0][1] = figure[0][2] = figure[0][3] = 1;
    figure[1][2] = figure[1][3] = figure[2][2] = figure[2][3] = 1;
  } else if (type == 3) {
    figure[0][0] = figure[0][1] = figure[0][2] = figure[0][3] = 1;
    figure[1][0] = figure[1][1] = figure[1][2] = figure[1][3] = 1;
  } else if (type == 4 && (rotate % 2) == 0) {
    figure[0][2] = figure[0][3] = figure[0][4] = figure[0][5] = 1;
    figure[1][0] = figure[1][1] = figure[1][2] = figure[1][3] = 1;
  } else if (type == 4 && (rotate % 2) == 1) {
    figure[0][0] = figure[0][1] = figure[2][2] = figure[2][3] = 1;
    figure[1][0] = figure[1][1] = figure[1][2] = figure[1][3] = 1;
  } else if (type == 5 && rotate == 0) {
    figure[0][2] = figure[0][3] = figure[1][0] = figure[1][1] = 1;
    figure[1][2] = figure[1][3] = figure[1][4] = figure[1][5] = 1;
  } else if (type == 5 && rotate == 1) {
    figure[0][0] = figure[0][1] = figure[1][0] = figure[1][1] = 1;
    figure[1][2] = figure[1][3] = figure[2][0] = figure[2][1] = 1;
  } else if (type == 5 && rotate == 2) {
    figure[0][0] = figure[0][1] = figure[0][2] = figure[0][3] = 1;
    figure[0][4] = figure[0][5] = figure[1][2] = figure[1][3] = 1;
  } else if (type == 5 && rotate == 3) {
    figure[0][2] = figure[0][3] = figure[1][0] = figure[1][1] = 1;
    figure[1][2] = figure[1][3] = figure[2][2] = figure[2][3] = 1;
  } else if (type == 6 && (rotate % 2) == 0) {
    figure[0][0] = figure[0][1] = figure[0][2] = figure[0][3] = 1;
    figure[1][2] = figure[1][3] = figure[1][4] = figure[1][5] = 1;
  } else if (type == 6 && (rotate % 2) == 1) {
    figure[0][2] = figure[0][3] = figure[1][0] = figure[1][1] = 1;
    figure[1][2] = figure[1][3] = figure[2][0] = figure[2][1] = 1;
  }
}

// score
void score_fnc(GameInfo_t *info, int **game_field) {
  int number = 0;
  int flag = 0;
  for (int i = 0; i < FIELD_Y; i++) {
    for (int j = 0; j < FIELD_X; j++) {
      if (info->field[i][j] == 0) {
        flag = -1;
        break;
      }
    }
    if (flag == 0) {
      delete_string(i, info->field);
      number++;
    }
    flag = 0;
  }
  for (int i = 0; i < FIELD_Y; i++) {
    for (int j = 0; j < FIELD_X; j++) {
      game_field[i][j] = info->field[i][j];
    }
  }
  if (number == 1)
    info->score = info->score + 100;
  else if (number == 2)
    info->score = info->score + 300;
  else if (number == 3)
    info->score = info->score + 700;
  else if (number == 4)
    info->score = info->score + 1500;
  if (info->score > info->high_score) info->high_score = info->score;
  if (info->level * 600 <= info->score) {
    info->level = info->score / 600 + 1;
    info->speed = info->level;
  }
}

void delete_string(int str, int **game_field) {
  for (int i = FIELD_X - 1; i >= 0; i--) {
    for (int j = 0; j < FIELD_X; j++) {
      if (i <= str && i > 0)
        game_field[i][j] = game_field[i - 1][j];
      else if (i == 0)
        game_field[i][j] = 0;
    }
  }
}

void update_high_score(GameInfo_t *info) {
  if (info->score == info->high_score) {
    FILE *fp = fopen("high_score.txt", "w");
    if (fp != NULL) {
      char str[15] = {0};
      if (snprintf(str, sizeof str, "%d", info->high_score) > 0)
        fwrite(str, sizeof str[0], 15, fp);
      fclose(fp);
    }
  }
}

// gameover
int check_gameover(GameInfo_t *info) {
  int result = 0;
  for (int j = 0; j < FIELD_X; j++) {
    if (info->field[0][j] == 1) {
      result = 1;
      break;
    }
  }
  return result;
}

void gameover(UserAction_t action, GameInfo_t *info, int **game_field,
              Figure_t *current_figure) {
  if (action == Terminate) {
    free_fields(info, game_field, current_figure);
    free_matrix(FIELD_Y, game_field);
    update_high_score(info);
  } else if (action == Start) {
    free_fields(info, game_field, current_figure);
    update_high_score(info);
    start_info(info, current_figure);
  }
}