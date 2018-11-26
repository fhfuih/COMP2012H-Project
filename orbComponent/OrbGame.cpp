#include "OrbGame.h"

OrbGame::OrbGame() :
    selectedOrb(nullptr),
    spinning(false)
{
    game_window = new GameWindow(nullptr, this); //new game window

    for(int i = 0; i < 5; ++i) for(int j = 0; j < 6; ++j) {
        orbBoard[i][j] = new Orb(i, j, static_cast<Type>(rand()%3 + 1), &orbBoard);
    }
}

OrbGame::~OrbGame() {
}

GameWindow* OrbGame::get_game_window() const {
    return game_window;
}

void OrbGame::process_combos() {
    int mark[5][6];
    std::function<void (int, int, Type)> find_connected = [&](int row, int col, Type type)->void {
        if(mark[row][col] == 1) return;
        if((orbBoard[row][col] != NONE) && (orbBoard[row][col] == type)) {
            mark[row][col] = 1;
            if(row > 0) find_connected(row-1, col, type);
            if(row < BOARD_ROWS) find_connected(row+1, col, type);
            if(col > 0) find_connected(row, col-1, type);
            if(col < BOARD_COLS) find_connected(row, col+1, type);
        }
    };
    std::function<bool (int, int)> check_combo = [&](int row, int col)->bool {
        if(((col > 0) && (col < BOARD_COLS) && (mark[row][col-1] == 1) && (mark[row][col+1] == 1)) ||
           ((col > 1) && (mark[row][col-1] == 1) && (mark[row][col-2] == 1)) ||
           ((col < BOARD_COLS-1) && (mark[row][col+1] == 1) && (mark[row][col+2] == 1))) {
            return true;
            }
        if(((row > 0) && (row < BOARD_ROWS) && (mark[row-1][col] == 1) && (mark[row+1][col] == 1)) ||
           ((row > 1) && (mark[row-1][col] == 1) && (mark[row-2][col] == 1)) ||
           ((row < BOARD_ROWS-1) && (mark[row+1][col] == 1) && (mark[row+2][col] == 1))) {
            return true;
        }
        return false;
    };

    for(int i = 0; i < BOARD_ROWS; ++i) for(int j = 0; j < BOARD_COLS; ++j) {
        for(int i = 0; i < BOARD_ROWS; ++i) for(int j = 0; j < BOARD_COLS; ++j) mark[i][j] = 0;

        Type type = orbBoard[i][j];
        if(type == NONE) continue;

        find_connected(i, j, type);
        for(int i = 0; i < BOARD_ROWS; ++i) for(int j = 0; j < BOARD_COLS; ++j) {
            if((mark[i][j] == 1) && (!check_combo(i, j))) mark[i][j] = 0;
        }

        int orbCount = 0;
        for(int i = 0; i < BOARD_ROWS; ++i) for(int j = 0; j < BOARD_COLS; ++j) {
            if(mark[i][j] == 1) {
                ++orbCount;
                orbBoard[i][j] = NONE;
            }
        }
        combosVector.push_back({type, orbCount});
        statesVector.push_back(orbBoard);
    }
}

void OrbGame::shift_orbs() {
    for(int i = 0; i < BOARD_ROWS; ++i) {
        bool shifted = false;
        for(int j = 0; j < BOARD_COLS; ++j) {
            for(int k = i; (k < BOARD_ROWS-1) && (orbBoard[k][j] == NONE); ++k) {
                for(int l = k+1; l < BOARD_ROWS-1; ++l) orbBoard[l][j] = orbBoard[l+1][j];
                orbBoard[BOARD_ROWS-1][j] = NONE;
                shifted = true;
                break;
            }
        }
        if(shifted == true) statesVector.push_back(orbBoard);
        shifted = false;
    }
}

void OrbGame::refill_board() {
    for(int i = 0; i < BOARD_ROWS; ++i) for(int j = 0; j < BOARD_COLS; ++j) {
        if(orbBoard[i][j] == NONE) orbBoard[i][j] = static_cast<Type>(rand()%TYPE_COUNT + 1);
    }
    statesVector.push_back(orbBoard);
}

void OrbGame::on_return_key(Type types[BOARD_ROWS][BOARD_COLS]) {
    for(int i = 0; i < BOARD_ROWS; ++i) for(int j = 0; j < BOARD_COLS; ++j) orbBoard[i][j] = types[j][j];
    process_combos();
    shift_orbs();
    refill_board(); //need to make board have no combo
    emit combo_finish(combosVector);
    emit refresh_board(statesVector);
    combosVector.clear();
    statesVector.clear();
}
