#ifndef UTILS_H
#define UTILS_H

/*  Types of monsters and orbs
 * orbs shall start at 1, while monsters starts at 0
 */
enum Type {NONE, WATER, FIRE, GRASS, GROUND, ELECTRIC};
const int TYPE_COUNT = 5;

/* Board geometry */
const int BOARD_ROWS = 5;
const int BOARD_COLS = 6;

/* Orb game structures */
struct Combo {
    Type type;
    int orbCount;
};
struct BoardState {
    Type board[BOARD_ROWS][BOARD_COLS];
    BoardState(Type board[BOARD_ROWS][BOARD_COLS]) {
        for(int i = 0; i < BOARD_ROWS; ++i) for(int j = 0; j < BOARD_COLS; ++j) this->board[i][j] = board[i][j];
    }
};

/* Square geometry */
const int OFFSET_X = 0;
const int OFFSET_Y = 0;
const int SQUARE_WIDTH = 80;
const int SQUARE_HEIGHT = 80;

const int LEVEL_COUNT = 5;
/* Pet and monsters */
const int PET_TYPES = 10;
const int ENEMY_TYPES = 15;
const int PET_TEAM_SIZE = 5;
const int MAXIMAL_ENEMY_TEAM_SIZE = 5;
const int ENEMY_TEAM_SIZE[LEVEL_COUNT] = {1,2,3,4,5};

#endif // UTILS_H
