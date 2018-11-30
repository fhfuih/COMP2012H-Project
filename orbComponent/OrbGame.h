#ifndef OrbGame_h
#define OrbGame_h

#include <QObject>
using std::vector;

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
    vector<BoardState> statesComboVector;
    vector<BoardState> statesRefillVector;
    
    void process_combos();
    void shift_orbs();
    void refill_board();

    void generate_board(Type orbBoard[BOARD_ROWS][BOARD_COLS]);
    
public slots:
    void on_orb_select(int row, int col);
    void on_orb_move(int row, int col);
    void on_finish_move();
    void on_combat_finish(int combatStatus);
    
signals:
    void combo_finish(const vector<Combo>& combos);
    void refresh_board(const vector<BoardState>& statesVector);
    void orb_status(bool orbAnimationStatus);

friend GameInstance;
};

#endif /* OrbGame_h */
