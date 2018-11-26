#ifndef AbstractMonster_h
#define AbstractMonster_h

#include <QObject>
#include <vector>
using std::vector;

#include "gamewindow.h"
#include "Utils.h"

class AbstractMonster : public QObject {
    Q_OBJECT
public:
    const int ID; //predefined pet/enemy id in records
    const Type PRIMARY_TYPE;
    const int POSITION;
    
    AbstractMonster(int position, int ID);
    virtual ~AbstractMonster() = default;
    
    virtual void attack() = 0;
    virtual void special_ability() = 0;
    
    int get_attack() const;
    int get_health() const;
    int get_defense() const;
protected:
    const int ATTACK;
    const int HEALTH;
    const int DEFENSE;
    
    const int COOLDOWN;
    int turnsCooldown;
    
    virtual void animation() = 0; //some animation?
};

#endif /* AbstractMonster_h */
