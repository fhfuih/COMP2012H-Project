#ifndef CombatGame_h
#define CombatGame_h

#include <QObject>

#include "EnemyMonster.h"
#include "PetMonster.h"

#include "OrbGameWindow.h"
#include "fileloader.h"

class GameWindow; //game window ui

class CombatGame : public QObject {
    Q_OBJECT
public:
    CombatGame(int level, int petSelection[5]);
    ~CombatGame(); //some destructor
    
private:
    int level;
    PetMonster* petArray[5];
    EnemyMonster* enemyArray[5];
    
    int turnNumber;
    int totalHealth;
    int playerHealth;
    int playerDefense;
    int playerTrueDamage;

    bool gameOver;

    void pets_attack(const vector<Combo>& combos);
    void enemies_attack();
    int player_recieve_damage(int damage);

    void ability_attack_enemy(int petPosition, Type TYPE, int damage);
    void ability_heal_player(int petPosition, int heal);
    
public slots:
    void start_combat(const vector<Combo>& combos);
    void activate_pet_ability(int petPosition);

signals:
    void pet_attack_enemy(int petPosition, int enemyPosition, int newHealth, bool criticalHit);
    void enemy_attack_player(int enemyPosition, int attackCooldown, int newHealth);
    void player_update_health(int petPosition, int newHealth);
    void enemy_update_health(int enemyPosition, int attackCooldown, int newHealth);
    void special_attack_ready(int petPosition);
    void enemy_die(int enemyPosition);
    void player_die();
    void level_cleared();
    void combat_end();
    void combat_text(QString text, bool playerAction);
};

#endif /* CombatGame_h */
