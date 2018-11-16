#ifndef PetMonster_h
#define PeMonster_h

class PetMonster : public AbstractMonster {
public:
    PetMonster(); //some constructor
    ~PetMonster(); //some destructor
    
    virtual char getImage() const;
    
    virtual void animation(); //some animation?
    
    virtual int calculate_attack(); //calculate here or in derived class?
    virtual void attack(); //attack here or in derived class?
    
    virtual void special_attack(); //special attack here or in derived class?
protected:
    const Type second_type; //secondary type
}

#endif /* AbstractMonster_h */
