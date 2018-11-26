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

void OrbGame::on_mouse_click(int row, int col) {
    selectedOrbRow = row;
    selectedOrbCol = col;
    selectedType = orbBoard[row][col];
}

void OrbGame::on_arrow_key(int row, int col) {
    orbBoard[selectedOrbRow][selectedOrbCol] = orbBoard[row][col];
    orbBoard[row][col] = selectedType;

    selectedOrbRow = row;
    selectedOrbCol = col;
}

void OrbGame::on_return_key() {
    combosVector.clear();
    statesVector.clear();
    process_combos();
    shift_orbs();
    refill_board();
    emit combo_finish(combosVector);
    emit refresh_board(statesVector);
}
