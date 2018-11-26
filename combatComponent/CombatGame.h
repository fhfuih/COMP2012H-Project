#ifndef CombatGame_h
#define CombatGame_h

#include <QObject>

#include "EnemyMonster.h"
#include "PetMonster.h"

#include "gamewindow.h"

//class GameWindow; //game window ui

class CombatGame : public QObject {
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

    void pets_attack(vector<Combo> combos);
    void enemies_attack();
    
    void game_over();
    
private slots:
    void start_combat(vector<Combo> combos);
    void player_recieve_damage(int damage);

    void ability_attack_enemy(Type PRIMARY_TYPE, int damage);
    void ability_heal_player(int heal);
};

#endif /* CombatGame_h */
