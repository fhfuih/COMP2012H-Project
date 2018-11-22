#include "Orb.h"
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
    for(int i = 0; i < 5; ++i) for(int j = 0; j < 6; ++j) {
        delete orbBoard[i][j];
        orbBoard[i][j] = nullptr;
    }
}

void OrbGame::startGraphicUI() {
    game_window->show();
}

GameWindow* OrbGame::get_game_window() const {
    return game_window;
}

void OrbGame::refresh_board() {
    //UI
} 

void OrbGame::select_orb(int row, int col) {
    selectedOrb = orbBoard[row][col];
    selectedOrb->set_highlighted(true);
    
    refresh_board();
}

void OrbGame::move_orb(int moveRow, int moveCol) {
    int currentRow = selectedOrb->get_row();
    int currentCol = selectedOrb->get_col();
    int targetRow = currentRow + moveRow;
    int targetCol = currentCol + moveCol;
    
    orbBoard[targetRow][targetCol]->set_row(currentRow);
    orbBoard[targetRow][targetCol]->set_col(currentCol);
    orbBoard[currentRow][currentCol] = orbBoard[targetRow][targetCol];
    
    selectedOrb->set_row(targetRow);
    selectedOrb->set_col(targetCol);
    orbBoard[targetRow][targetCol] = selectedOrb;
    
    refresh_board();
}

void OrbGame::process_combos() {
    int mark[5][6];
    std::function<void (int, int, Type)> find_connected = [&](int row, int col, Type type)->void {
        if(mark[row][col] == 1) return;
        if((orbBoard[row][col] != nullptr) && (orbBoard[row][col]->get_type() == type)) {
            mark[row][col] = 1;
            if(row > 0) find_connected(row-1, col, type);
            if(row < 5) find_connected(row+1, col, type);
            if(col > 0) find_connected(row, col-1, type);
            if(col < 6) find_connected(row, col+1, type);
        }
    };
    std::function<bool (int, int)> check_combo = [&](int row, int col)->bool {
        if(((col > 0) && (col < 6) && (mark[row][col-1] == 1) && (mark[row][col+1] == 1)) ||
           ((col > 1) && (mark[row][col-1] == 1) && (mark[row][col-2] == 1)) ||
           ((col < 5) && (mark[row][col+1] == 1) && (mark[row][col+2] == 1))) {
            return true;
            }
        if(((row > 0) && (row < 5) && (mark[row-1][col] == 1) && (mark[row+1][col] == 1)) ||
           ((row > 1) && (mark[row-1][col] == 1) && (mark[row-2][col] == 1)) ||
           ((row < 4) && (mark[row+1][col] == 1) && (mark[row+2][col] == 1))) {
            return true;
        }
        return false;
    };
    
    for(int i = 0; i < 5; ++i) for(int j = 0; j < 6; ++j) {
        for(int i = 0; i < 5; ++i) for(int j = 0; j < 6; ++j) mark[i][j] = 0;
        
        Type type = orbBoard[i][j]->get_type();
        find_connected(i, j, type);
        for(int i = 0; i < 5; ++i) for(int j = 0; j < 6; ++j) {
            if((mark[i][j] == 1) && (!check_combo(i, j))) mark[i][j] = 0;
        }
        
        int count = 0;
        for(int i = 0; i < 5; ++i) for(int j = 0; j < 6; ++j) {
            if(mark[i][j] == 1) ++count;
            delete orbBoard[i][j];
            orbBoard[i][j] = nullptr;
        }
        combos.push_back({static_cast<int>(type), count});
    }
}

void OrbGame::shift_orbs() {
    for(int i = 0; i < 5; ++i) for(int j = 0; j < 6; ++j) {
        if(orbBoard[i][j] == nullptr) {
            for(int k = i+1; k < 5; ++k) {
                orbBoard[k][j]->set_row(i);
                orbBoard[i][j] = orbBoard[k][j];
                orbBoard[k][j] = nullptr;
            }
        }
    }
    
    refresh_board();
}

void OrbGame::refill_board() {
    for(int i = 0; i < 5; ++i) for(int j = 0; j < 6; ++j) {
        if(orbBoard[i][j] == nullptr) orbBoard[i][j] = new Orb(i, j, static_cast<Type>(rand()%3 + 1), &orbBoard);
    }
    
    refresh_board();
}

void OrbGame::on_orb_click(int row, int col) {
    if(!spinning) select_orb(row, col);
}

void OrbGame::on_arrow_key(int key) {
    switch (key) {
        case Qt::Key_Down:
            if(selectedOrb->get_row() > 0) move_orb(-1, 0);
            break;
        case Qt::Key_Up:
            if(selectedOrb->get_row() < 5) move_orb(1, 0);
            break;
        case Qt::Key_Left:
            if(selectedOrb->get_col() > 0) move_orb(0, -1);
            break;
        case Qt::Key_Right:
            if(selectedOrb->get_col() < 6) move_orb(0, 1);
            break;
        default:
            break;
    }
    
    refresh_board();
}

void OrbGame::on_return_key() {
    if(spinning) {
        process_combos(); //can animate combos in order
        refill_board(); //can wait a bit until refill shows
        emit spin_finish(combos);
        combos.clear();
    }
    spinning = false;
}
