#ifndef UTILS_H
#define UTILS_H

#include <QDebug>
#include <QWidget>
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

/*  Types of monsters and orbs
 * orbs shall start at 1, while monsters starts at 0
 */
enum Type {NONE, METAL, WOOD, EARTH, WATER, FIRE};
const int TYPE_COUNT = 5;

/* Orb game board geometry */
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

/* Levels */
const int LEVEL_COUNT = 5;

/* Pet and monsters */
const int PET_TYPES = 10;
const int ENEMY_TYPES = 15;
const int PET_TEAM_SIZE = 5;
const int MAXIMAL_ENEMY_TEAM_SIZE = 5;
const int ENEMY_TEAM_SIZE[LEVEL_COUNT] = {1,2,3,4,5};

/* GUI */
/* OrbBox geometry */
const int OFFSET_X = 0;
const int OFFSET_Y = 0;
const int ORBBOX_WIDTH = 80;
const int ORBBOX_HEIGHT = 80;

/* Setting hold place when hiding */
void keepItsFuckingSize(QWidget* widget);

const int COMBAT_WINDOW_WIDTH = 800;
const int COMBAT_WINDOW_HEIGHT = 500;
const int ORB_WINDOW_WIDTH = 480;
const int ORB_WINDOW_HEIGHT = 400;

/* Functions */
void utils_delay(int milliseconds);

#endif // UTILS_H
