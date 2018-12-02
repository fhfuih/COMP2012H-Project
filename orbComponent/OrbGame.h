#ifndef OrbGame_h
#define OrbGame_h

#include <QObject>
using std::vector;

#include "OrbGameWindow.h"

class GameInstance;

class OrbGame : public QObject {
    Q_OBJECT
    /* Backend for orb game interactions
     * accepts user input from OrbGameWindow
     * calculates number of orb combos
     * passes combo information to combat component
     * regenerates new board state */
public:
    OrbGame();
    ~OrbGame();

private:
    /* dynamic data to monitor user inputs */
    Type orbBoard[BOARD_ROWS][BOARD_COLS];
    int selectedOrbRow;
    int selectedOrbCol;
    Type selectedType;
    
    /* containers to store orb combos and combat information */
    vector<Combo> combosVector;
    vector<BoardState> statesComboVector;
    vector<BoardState> statesRefillVector;
    
    /* functions to calculate orb combos
     * and refill missing orbs after combos */
    void process_combos();
    void shift_orbs();
    void refill_board();

    /* function to generate a new board
     * or generate missing orbs after combos */
    void generate_board(Type orbBoard[BOARD_ROWS][BOARD_COLS]);
    
public slots:
    /* slots to respond to user inputs in OrbGameWindow */
    void on_orb_select(int row, int col);
    void on_orb_move(int row, int col);
    void on_finish_move();
    /* slot to respond to CombatGame termination */
    void on_combat_finish();
    
signals:
    /* signal to activate CombatGame process */
    void combo_finish(const vector<Combo>& combos);
    /* signal to refresh OrbGameWindow graphic */
    void refresh_board(const vector<BoardState>& statesVector);
    /* signal to update overall anmiation status */
    void animation_end(bool animationStatus);

friend GameInstance;
};

#endif /* OrbGame_h */
