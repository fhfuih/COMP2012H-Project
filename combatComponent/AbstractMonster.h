#ifndef AbstractMonster_h
#define AbstractMonster_h

#include <QObject>
#include <vector>
using std::vector;

#include "OrbGameWindow.h"
#include "Utils.h"
#include "fileloader.h"

class AbstractMonster : public QObject {
    Q_OBJECT
public:
    const int ID;
    const QString NAME;
    const Type TYPE;
    const int POSITION;
    
    AbstractMonster(int position, int ID);
    virtual ~AbstractMonster() = default;
    
    virtual int attack() = 0;
    virtual int special_ability() = 0;
    
    int get_attack() const;
    int get_health() const;
    int get_defense() const;
protected:
    const int ATTACK;
    const int HEALTH;
    const int DEFENSE;
    
    const int COOLDOWN;
    int turnsCooldown;
};

#endif /* AbstractMonster_h */
