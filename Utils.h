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

#endif // UTILS_H
