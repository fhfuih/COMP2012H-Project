#ifndef OrbGame_h
#define OrbGame_h

#include <array>

#include "Orb.h"

extern const int ORB_BOARD_HEIGHT = 6;
extern const int ORB_BOARD_WIDTH  = 5;

class OrbGame{
public:
    OrbGame();
    ~OrbGame();
    void select(int row, int col);
    bool move(int dir);
    std::array<Type, TYPE_COUNT> checkout();
private:
    Orb* orbBoard[ORB_BOARD_WIDTH][ORB_BOARD_HEIGHT];
    Orb* selectedOrb;
};

#endif /* OrbGame_h */