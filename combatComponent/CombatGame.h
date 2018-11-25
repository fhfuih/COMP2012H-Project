#ifndef CombatGame_h
#define CombatGame_h

#include <QObject>

#include "EnemyMonster.h"
#include "PetMonster.h"

#include "gamewindow.h" //game window ui

class GameWindow; //game window ui

class CombatGame : QObject {
    Q_OBJECT
public:
    CombatGame();
    ~CombatGame(); //some destructor
    void startGraphicUI(); //should be same window as OrbGame?
    GameWindow* get_game_window() const;
    
    int get_player_health() const;
    int get_player_defense() const;
    
private:
    GameWindow* game_window; //game window ui
    PetMonster* petArray[5]; //Pet array
    EnemyMonster* enemyArray[5]; //Enemy array
    
    int turnNumber;
    int playerHealth;
    int playerDefense;

    void pets_attack(vector<int[2]> combos);
    void enemies_attack();
    
    void game_over();
    
private slots:
    void start_combat(vector<int[2]> combos);
    void player_recieve_damage(int damage);
};

#endif /* CombatGame_h */
