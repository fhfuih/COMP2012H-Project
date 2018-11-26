#ifndef CombatGame_h
#define CombatGame_h

#include <QObject>

#include "EnemyMonster.h"
#include "PetMonster.h"

#include "gamewindow.h"

class GameWindow; //game window ui

class CombatGame : public QObject {
    Q_OBJECT
public:
    CombatGame();
    ~CombatGame(); //some destructor
    
private:
    GameWindow* game_window;
    PetMonster* petArray[5];
    EnemyMonster* enemyArray[5];
    
    int turnNumber;
    int playerHealth;
    int playerDefense;

    void pets_attack(vector<Combo> combos);
    void enemies_attack();
    int player_recieve_damage(int damage);

    void ability_attack_enemy(Type TYPE, int damage);
    void ability_heal_player(int heal);
    
    void game_over();
    
public slots:
    void start_combat(vector<Combo> combos);
    void pet_ability(int petPosition);

signals:
    void pet_attack_enemy(int enemyPosition, int outputDamage);
    void enemy_attack_player(int attackTurns, int outputDamage);
    void player_update_health(int newHealth);
    void enemy_update_health(int enemyPosition, int newHealth);
    void special_attack_ready(int petPosition);
};

#endif /* CombatGame_h */
