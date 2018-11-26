#ifndef UTILS_H
#define UTILS_H

/*  Types of monsters and orbs
 * orbs shall start at 1, while monsters starts at 0
 */
enum Type {NONE, FIRE, WATER, GRASS};
const int TYPE_COUNT = 4;

/* Board geometry */
const int BOARD_ROWS = 6;
const int BOARD_COLS = 5;

/* Square geometry */
const int OFFSET_X = 50;
const int OFFSET_Y = 50;
const int SQUARE_WIDTH = 80;
const int SQUARE_HEIGHT = 80;

#endif // UTILS_H
