#include "OrbGame.h"

OrbGame::OrbGame() {
    for(int i = 0; i < BOARD_ROWS; ++i) for(int j = 0; j < BOARD_COLS; ++j) orbBoard[i][j] = NONE;
    generate_board(orbBoard);
}

OrbGame::~OrbGame() {
}

void OrbGame::process_combos() {
    int mark[5][6];
    std::function<void (int, int, Type)> find_connected = [&](int row, int col, Type type)->void {
        if(mark[row][col] == 1) return;
        if(orbBoard[row][col] == type) {
            mark[row][col] = 1;
            if(row > 0) find_connected(row-1, col, type);
            if(row < BOARD_ROWS-1) find_connected(row+1, col, type);
            if(col > 0) find_connected(row, col-1, type);
            if(col < BOARD_COLS-1) find_connected(row, col+1, type);
        }
    };
    std::function<bool (int, int)> check_combo = [&](int row, int col)->bool {
        if(((col > 0) && (col < BOARD_COLS-1) && (mark[row][col-1] == 1) && (mark[row][col+1] == 1)) ||
           ((col > 1) && (mark[row][col-1] == 1) && (mark[row][col-2] == 1)) ||
           ((col < BOARD_COLS-2) && (mark[row][col+1] == 1) && (mark[row][col+2] == 1))) {
            return true;
        }
        if(((row > 0) && (row < BOARD_ROWS-1) && (mark[row-1][col] == 1) && (mark[row+1][col] == 1)) ||
           ((row > 1) && (mark[row-1][col] == 1) && (mark[row-2][col] == 1)) ||
           ((row < BOARD_ROWS-2) && (mark[row+1][col] == 1) && (mark[row+2][col] == 1))) {
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

        if(orbCount != 0) {
            combosVector.push_back({type, orbCount});
            statesVector.push_back(orbBoard);
        }
    }
}

void OrbGame::shift_orbs() {
    for(int i = 0; i < BOARD_ROWS-1; ++i) {
        bool shifted = false;
        for(int j = 0, k = 0; j < BOARD_COLS; ++j, k = 0) {
            while((k < BOARD_ROWS-1) && (orbBoard[k][j] != NONE)) ++k;
            if(k < BOARD_ROWS-1) {
                for( ; k < BOARD_ROWS-1; ++k) orbBoard[k][j] = orbBoard[k+1][j];
                orbBoard[BOARD_ROWS-1][j] = NONE;
                shifted = true;
            }
        }
        if(shifted == true) statesVector.push_back(orbBoard);
        shifted = false;
    }
}

void OrbGame::refill_board() {
    generate_board(orbBoard);
    statesVector.push_back(orbBoard);
}

void OrbGame::generate_board(Type orbBoard[BOARD_ROWS][BOARD_COLS]) {
    std::function<bool (int, int, Type)> check_combo = [&](int row, int col, Type type)->bool {
        if(((col > 0) && (col < BOARD_COLS) && (orbBoard[row][col-1] == type) && (orbBoard[row][col+1] == type)) ||
           ((col > 1) && (orbBoard[row][col-1] == type) && (orbBoard[row][col-2] == type)) ||
           ((col < BOARD_COLS-1) && (orbBoard[row][col+1] == type) && (orbBoard[row][col+2] == type))) {
            return true;
        }
        if(((row > 0) && (row < BOARD_ROWS) && (orbBoard[row-1][col] == type) && (orbBoard[row+1][col] == type)) ||
           ((row > 1) && (orbBoard[row-1][col] == type) && (orbBoard[row-2][col] == type)) ||
           ((row < BOARD_ROWS-1) && (orbBoard[row+1][col] == type) && (orbBoard[row+2][col] == type))) {
            return true;
        }
        return false;
    };

    for(int i = 0; i < BOARD_ROWS; ++i) for(int j = 0; j < BOARD_COLS; ++j) {
        if(orbBoard[i][j] == NONE) {
            Type newOrb;
            do {
                newOrb = static_cast<Type>(rand()%TYPE_COUNT + 1);
            } while(check_combo(i, j, newOrb));
            orbBoard[i][j] = newOrb;
        }
    }
}

void OrbGame::on_orb_select(int row, int col) {
    selectedOrbRow = row;
    selectedOrbCol = col;
    selectedType = orbBoard[row][col];
}

void OrbGame::on_orb_move(int row, int col) {
    orbBoard[selectedOrbRow][selectedOrbCol] = orbBoard[row][col];
    orbBoard[row][col] = selectedType;

    selectedOrbRow = row;
    selectedOrbCol = col;
}

void OrbGame::on_finish_move() {
    combosVector.clear();
    statesVector.clear();
    process_combos();
    shift_orbs();
    //refill_board();
    emit combo_finish(combosVector);
    emit refresh_board(statesVector);
}
