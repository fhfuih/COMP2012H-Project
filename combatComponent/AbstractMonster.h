#ifndef AbstractMonster_h
#define AbstractMonster_h

#include <QObject>
#include <vector>
using std::vector;

#include "OrbGameWindow.h"
#include "Utils.h"
#include "FileLoader.h"

//This file is the implementation of the class AbstractMonster.
//This class is the base class for two key elements in the part of the battle game which are the pet monster and the enemy monster.
//It contains the common properties and abilities of the two different kinds of monster

class AbstractMonster : public QObject {
    Q_OBJECT
public:
    const int ID; //int type, which is used to identify the specific monster object
    const QString NAME; //QString type, which is the “name” of the specific monster object printed out to the user when gaming
    const Type TYPE; //Self-defined type “type”, which is used to distinct the different “element property” of different monsters
    const int POSITION; //int type, which is used to store the position of the monster in the gaming slot (there will be 5 positions for monster to pick, which decides the attack order)
    
    AbstractMonster(int position, int ID); //constructor
    virtual ~AbstractMonster() = default; //destructor
    
    virtual int attack() = 0; //return int type, which is called when the monster gives attack to others
    virtual int special_ability() = 0; //return int type, which is called when the monster use special skill
    
    int get_attack() const; //return attack value
    int get_health() const; //return health value
    int get_defense() const; //return defense value
protected:
    const int ATTACK; //int type, which is used to store the attack value of a specific monster
    const int HEALTH; //int type, which is used to store the life value of a specific monster
    const int DEFENSE; //int type, which is used to store the defense value of a specific monster
    
    const int COOLDOWN; //int type, which is used to store the cooldown time of special skill of a specific monster
    int turnsCooldown; //int type, which is used to calculate the time from the present time to time when the monster can use its special skill
};

#endif /* AbstractMonster_h */
