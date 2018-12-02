#ifndef CombatGame_h
#define CombatGame_h

#include <QObject>

#include "EnemyMonster.h"
#include "PetMonster.h"

#include "OrbGameWindow.h"
#include "FileLoader.h"

class GameWindow; //game window ui


//This file is the implementation of the class CombatGame.
//This class is used to do the battle game by receiving the corresponding value from orb game and return the corresponding signal to the orb game and display part.

class CombatGame : public QObject {
    Q_OBJECT
public:
    CombatGame(int level, int petSelection[5]); //constructor
    ~CombatGame(); //some destructor
    
private:
    int level; //int type, which is used to record the current level of the game
    PetMonster* petArray[5]; //PetMonster* type, which is used to store the pet monsters that used in the current game, the order of the array also stands for the position of the pet monsters
    EnemyMonster* enemyArray[5]; //EnemyMonster* type, which is used to store the enemy monsters that used in the current game, the order of the array also stands for the position of the enemy monsters
    
    int turnNumber; //int type, which is used to record the turn of the game
    int totalHealth; //int type, which is calculated by add up all the health value of the pet monster
    int playerHealth; //int type, which represents the health of the current player
    int playerDefense; //int type, which represents the defense of the current player
    int playerTrueDamage; //int type, which stands for the total damage received by the player

    bool gameOver; //bool type, which states the condition of the game

    void pets_attack(const vector<Combo>& combos); //void, which is called when the player finish the orb game and the pet monsters give damage to the enemy
    void enemies_attack(); //void, which is called when the enemy attack the player
    int player_recieve_damage(int damage); //int, which is called when the player is attacked, return the current player health

    void ability_attack_enemy(int petPosition, Type TYPE, int damage); //void, which is called when a pet monster use its attack skill
    void ability_heal_player(int petPosition, int heal); //void, which is called when a pet monster use its heal skill
    
public slots:
    void start_combat(const vector<Combo>& combos); //receive when the combat game start
    void activate_pet_ability(int petPosition); //receive when some pets use their special skill

signals:
    void pet_attack_enemy(int petPosition, int enemyPosition, int newHealth, bool criticalHit); //sent out when a pet attack the enemy
    void enemy_attack_player(int enemyPosition, int newHealth); //sent out when the enemy attack the player
    void player_update_health(int petPosition, int newHealth); //sent out when the player health value is changed
    void enemy_update_health(int enemyPosition, int newHealth); //sent out when the player health value is changed
    void special_attack_ready(int petPosition); //sent out when a pet’s cooldown turn become 0
    void pet_ability_animation(bool animationStatus); //sent out when the pet’s special skill is ready
    void enemy_die(int enemyPosition); //sent out when an enemy is dead
    void player_die(); //sent out when the player die
    void level_cleared();
    void combat_end(); //sent out when the combat game is finished
    void combat_text(QString text, bool playerAction); //sent out when a action of the  combat game is taken
};

#endif /* CombatGame_h */
