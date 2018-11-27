#ifndef OrbGame_h
#define OrbGame_h

#include <QObject>
#include <QKeyEvent>
using std::vector;

#include "Orb.h"
#include "OrbGameWindow.h"

class GameInstance;

class OrbGame : public QObject {
    Q_OBJECT
public:
    OrbGame();
    ~OrbGame();

private:
    Type orbBoard[BOARD_ROWS][BOARD_COLS];
    int selectedOrbRow;
    int selectedOrbCol;
    Type selectedType;
    
    vector<Combo> combosVector;
    vector<BoardState> statesVector;
    
    void process_combos();
    void shift_orbs();
    void refill_board();

    void generate_board(Type orbBoard[BOARD_ROWS][BOARD_COLS]);
    
public slots:
    void on_orb_select(int row, int col);
    void on_orb_move(int row, int col);
    void on_finish_move();
    
signals:
    void combo_finish(const vector<Combo>& combos);
    void refresh_board(const vector<BoardState>& statesVector);

friend GameInstance;
};

#endif /* OrbGame_h */
