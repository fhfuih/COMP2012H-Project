# COMP2012H-Project
[TOC]



## 1.Structure

### - PuzzleDragon

#### - Main

#### - Orbgame

```c++
public:
    const Type TYPE; //Element type of this orb
    
    Orb(int row, int col, Type type, Orb* (*orbBoard)[5][6]);//Construtor
    ~Orb(); //Destructor
    
    int get_row();
    int get_col();

protected:
    int row;
    int col;
    
    Orb* (*orbBoard)[5][6]; //pointer to orb game board
    
    void move_orb();//Exchang the orb

    void animate(); //Play animation of changing the orbs

private slots:
    void on_drag(int row, int col);//Emit the signal?
```
##### 1. TBC

#### - Battle

##### 1. AbstractMonster

```c++
public:
    const int ID; //For recording the specific monster
    const Type PRIMARY_TYPE; //First element type?(元素屬性？)
    const Type SECONDARY_TYPE; //Second element type
    const int POSITION; //The placing position on the battle board
    
    AbstractMonster(int position, int ID, AbstractMonster* (*monsterArray)[5]); //Constructor
    virtual ~AbstractMonster() = default; //Destructor
    
    virtual void attack() const = 0; //Return normal attack value
    virtual void special_ability() const = 0; // Special skill

protected:
    const int ATTACK; // Attack value
    const int HEALTH; // Life value
    const int DEFENSE; // Defending value
    
    const int ABILITY_COOLDOWN; //スキルのクールダウン :)
    int turnsAbility; // counting turns?
    
    AbstractMonster* (*monsterArray)[5]; 
//這裡不太懂是是打算做什麼的有人來解釋一下嗎XD
    
    virtual int calculate_damage() = 0; //damage given by the orbgame

    virtual void animation() = 0; //Play Animation
```

###### 1) PetMonster

```c++
public:    
    PetMonster(int position, int ID, AbstractMonster* (*petArray)[5]);//Constructor
    ~PetMonster(); //Destructor

    virtual void attack() const override;
    virtual void special_ability() const override;

protected:
    virtual int calculate_damage() override;
    virtual void animation() override; //Play animation
    
friend Player //Owner of the PetMonster
```



###### 2) EnemyMonster

```c++
public:
    EnemyMonster(int position, int ID, AbstractMonster* (*enemyArray)[5]); //Constructor
    ~EnemyMonster(); //Destructor
    
    virtual void attack() override;
    virtual void special_ability() override;
    
    int get_current_health() const;

protected:
    int currentHealth; //Life
    int turnsAttack; //Counting turns?
    
    virtual int calculate_damage() override;
    virtual void animation() override; 
```
##### 2. Type

```c++

```
##### 3. TBC

## 2.Comments

If there's any interesting features or functions you suggest, please write down here to let us know : )