# COMP2012H-Project

> I don't know the version of this readme file. Can I just dump my new thoughts at the top?

## Checklist

```
C:.
│  about.txt
│  FileLoader.cpp
│  FileLoader.h
│  GameInstance.cpp
│  GameInstance.h
│  LICENSE
│  main.cpp
│  PuzzleDragon.pro
│  README.md
│  resource.qrc
│  Utils.cpp
│  Utils.h
│
├─combatComponent
│      AbstractMonster.cpp
│      AbstractMonster.h
│      CombatGame.cpp
│      CombatGame.h
│      EnemyMonster.cpp
│      EnemyMonster.h
│      PetMonster.cpp
│      PetMonster.h
│
├─orbComponent
│      OrbGame.cpp
│      OrbGame.h
│
├─resource
│  │  101.png
│  │  101_icon.png
│  │  102.png
│  │  102_icon.png
│  │  103.png
│  │  103_icon.png
│  │  104.png
│  │  104_icon.png
│  │  105.png
│  │  105_icon.png
│  │  106.png
│  │  106_icon.png
│  │  107.png
│  │  107_icon.png
│  │  108.png
│  │  108_icon.png
│  │  109.png
│  │  109_icon.png
│  │  110.png
│  │  110_icon.png
│  │  201.png
│  │  202.png
│  │  203.png
│  │  204.png
│  │  205.png
│  │  blackSquare.jpg
│  │  Border pattern1.png
│  │  Border pattern2.png
│  │  Border pattern3.png
│  │  Border pattern4.png
│  │  clawCritical.png
│  │  clawNormal.png
│  │  CombatBorder.png
│  │  CombatGameBackground1.jpg
│  │  CombatGameBackground2.jpg
│  │  CombatGameBackground3.jpg
│  │  CombatGameBackground4.jpg
│  │  CombatGameBackground5.jpg
│  │  CombatGameBackground6.jpg
│  │  combatHeal.png
│  │  combatSword.png
│  │  data.json
│  │  deathSymbol.png
│  │  DisplayBorder.png
│  │  logo2-add.png
│  │  logo2-emptyStar.PNG
│  │  logo2-fullStar.PNG
│  │  logo2-indicator.png
│  │  logo2-pause.png
│  │  logo2-play.png
│  │  logo2-sad.PNG
│  │  logo2-smile.PNG
│  │  logo2-symbol1.PNG
│  │  logo2-symbol2.PNG
│  │  logo2.5.PNG
│  │  logo2.PNG
│  │  Long_Shot.ttf
│  │  Orb0.png
│  │  Orb1.png
│  │  Orb2.png
│  │  Orb3.png
│  │  Orb4.png
│  │  Orb5.png
│  │  OrbBorder.png
│  │  OrbGameBoard.jpg
│  │  SkillReady.png
│  │  SkillReady_transparent.png
│  │  yellowSquare.jpg
│  │
│  ├─100 other_PM_icons
│  │      101_icon.png
│  │      102_icon.png
│  │      103_icon.png
│  │      104_icon.png
│  │      105_icon.png
│  │      106_icon.png
│  │      107_icon.png
│  │      108_icon.png
│  │      109_icon.png
│  │      110_icon.png
│  │      PM11.png
│  │      PM13.png
│  │      PM14.png
│  │      PM15.png
│  │      PM16.png
│  │      PM17.png
│  │      PM18.png
│  │      PM19.png
│  │
│  └─200 other_EM_icons
│          EM10.png
│          EM11.png
│          EM12.png
│          EM13.png
│          EM16.png
│          EM17.png
│          EM18.png
│          EM2.png
│          EM3.png
│          EM6.png
│          EM7.png
│          EM8.png
│          EM9.png
│
└─uiComponent
        AboutWindow.cpp
        AboutWindow.h
        AboutWindow.ui
        BigGameWindow.ui
        ButtonWithDagger.cpp
        ButtonWithDagger.h
        ButtonWithDagger.ui
        CombatGameWindow.cpp
        CombatGameWindow.h
        CombatGameWindow.ui
        OrbBox.cpp
        OrbBox.h
        OrbGameWindow.cpp
        OrbGameWindow.h
        OrbGameWindow.ui
        PetBox.cpp
        PetBox.h
        SelectionWindow.cpp
        SelectionWindow.h
        SelectionWindow.ui
        StartWindow.cpp
        StartWindow.h
        StartWindow.ui
```

## To-dos

- [x] Implement MainWindow level selection
- [x] on mainwindow start button clicked, construct a game instance.
- [x] fix combatgamewindow: all findChild shall be this->findChild but not ui->xxx->findChild
- [ ] ~~Display cooldown info~~
- [x] Combat window pictures
- [x] Display gameplay log (e.g. "Pet 1 deals 38 damage to Enemy 3", "Pet 4 heals player for 500 health", "Enemy 2 deals 56 damage to player", "Enemy 5 heals for 300 health", [Critical hit!]", "[Super effective!]")
- [x] Display hit claw animation (claw appear and disappear)
- [x] Display pet attack animation
- [x] Display enemy attack animation (sword on head appear and disappear)
- [x] Display heal animation (heart on head appear and disappear)
- [x] Modify CombatWindow layout (make pretty)
- [x] Add game over checking
- [x] Fix player health issue
- [x] Exit button in selection window and game window
- [x] Display type info
- [x] Change pet monster ID's
- [x] Remove orb highlight border
- [ ] Clean up "resource" folder
- [ ] Make game documentation


[TOC]



## 1.Structure

### Main

Trivial.

### Orbgame

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

### - Battle

#### 1. AbstractMonster

##### **1.**     **Description:**

This file is the implementation of the class **AbstractMonster.** This class is the base class for two key elements in the part of the battle game which are the pet monster and the enemy monster. It contains the common properties and abilities of the two different kinds of monster

##### **2.**     **Data Members:**

Public:

【ID】int type, which is used to identify the specific monster object

【NAME】QString type, which is the “name” of the specific monster object printed out to the user when gaming

【TYPE】Self-defined type “type”, which is used to distinct the different “element property” of different monsters

【POSITION】int type, which is used to store the position of the monster in the gaming slot (there will be 5 positions for monster to pick, which decides the attack order)

Protected:

【ATTACK】int type, which is used to store the attack value of a specific monster

【HEALTH】int type, which is used to store the life value of a specific monster

【DEFENSE】int type, which is used to store the defense value of a specific monster

【COOLDOWN】int type, which is used to store the cooldown time of special skill of a specific monster

【turnsCooldown】int type, which is used to calculate the time from the present time to time when the monster can use its special skill

##### **3.**     **Member Functions:**

Public：

【**AbstractMonster** (int position, int ID)】constructor

【~**AbstractMonster**()】destructor

【**attack**()】return int type, which is called when the monster gives attack to others

【**special_ability**()】return int type, which is called when the monster use special skill

【**get_attack**()】return attack value

【**get_health**()】return health value

【**get_defense**()】return defense value

#### 2. PetMonster

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



#### 3. EnemyMonster

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
#### 4. CombatGame

##### **1.**     **Description:**

This file is the implementation of the class **CombatGame**. This class is used to do the battle game by receiving the corresponding value from orb game and return the corresponding signal to the orb game and display part.

##### **2.**     **Data Members:**

Private:

【level】int type, which is used to record the current level of the game

【petArray[5]】PetMonster* type, which is used to store the pet monsters that used in the current game, the order of the array also stands for the position of the pet monsters

【enemyArray[5]】EnemyMonster* type, which is used to store the enemy monsters that used in the current game, the order of the array also stands for the position of the enemy monsters

【turnNumber】int type, which is used to record the turn of the game

【totalHealth】int type, which is calculated by add up all the health value of the pet monster

【playerHealth】int type, which represents the health of the current player

【playerDefense】int type, which represents the defense of the current player

【playerTrueDamage】int type, which stands for the total damage received by the player

【gameOver】bool type, which states the condition of the game

##### **3.**     **Member Functions:**

Public:

【**CombatGame**(int level, int petSelection[5])】constructor

【~**CombatGame**()】destructor

Private:

**【pets_attack**(const vector<Combo>& combos);**】**void, which is called when the player finish the orb game and the pet monsters give damage to the enemy

【**enemies_attack**()】void, which is called when the enemy attack the player

【**player_recieve_damage**(int damage)】int, which is called when the player is attacked, return the current player health

【**ability_attack_enemy**(int petPosition, Type TYPE, int damage)】void, which is called when a pet monster use its attack skill

【**ability_heal_player**(int petPosition, int heal)】void, which is called when a pet monster use its heal skill

##### **4.**     **Slots:**

【**start_combat**(const vector<Combo>& combos)】receive when the combat game start

【**activate_pet_ability**(int petPosition)】receive when some pets use their special skill 

##### **5.**     **Signals:**

【**pet_attack_enemy**(int petPosition, int enemyPosition, int newHealth, bool criticalHit)】sent out when a pet attack the enemy

【**enemy_attack_player**(int enemyPosition, int newHealth)】sent out when the enemy attack the player

【**player_update_health**(int petPosition, int newHealth)】sent out when the player health value is changed

【**enemy_update_health**(int enemyPosition, int newHealth)】sent out when the player health value is changed

【**special_attack_ready**(int petPosition)】sent out when a pet’s cooldown turn become 0

【**pet_ability_animation**(bool animationStatus)】sent out when the pet’s special skill is ready

【**enemy_die**(int enemyPosition)】sent out when an enemy is dead

【**player_die**()】sent out when the player die

【**combat_end**()】sent out when the combat game is finished

【**combat_text**(QString text, bool playerAction)】sent out when a action of the  combat game is taken

### UI

#### GameWindow

Listed is the only interface (public methods) of GameWindow. All UI stuff are handled currectly *inside* the object, and thus methods like `set_highlight()` are deprecated.

`GameWindow(Type types[BOARD_ROWS][BOARD_COLS], QWidget *parent = nullptr)`

Requires `OrbGame` instance to generate a random but no combo gameboard, which will be used to initialize the buttons UI.

`GameWindow(QWidget *parent = nullptr)`

**Shall be used only when testing.** This version of constructor will generate a random board UI by itself, and will **not guarantee that there is no combo**.

(signal) `orb_selected(int row, int col)`

Emitted when the user successfully selects an orb (i.e. if clicking on another orb without pressing enter to confirm the previous operation, it will not be emitted, and the UI makes no respond as well). It signals the coordinate of the selected orb, and all UI responds are properly done before the emission.

(signal) `orb_deselected()`

Emitted when the user successfully deselect the currently selected orb (i.e. the second time the user presses Enter will not trigger this signal). All UI responds are properly done before the emission.

(signal) `orb_move_to(int row, int col)`

Emitted when the user successfully moves an orb (i.e. within the gameborad boundary). Note that this means the signal is emitted every time the user pressed a W/A/S/D key. It signals the **destination** coordinate of the current operation. (i.e. operation 1,2->1,3 signals 1,3), and all UI responds are properly done before the emission.

(signal) `closed()`

Emitted upon the closing of the window. Used to do further destruction tasks.

#### To-dos

- [x] CombatGame compability
- [x] OrbWindow display combo behavior
- [x] Make arrow keys able to move the selected orb as well. (study EventFilter)
- [x] MainWindow (select team pets and level)
- [ ] ~~Display cooldown info~~
- [ ] ~~Combat window pictures~~
- [x] Fix OrbGame: will crash if first key press is enter & other random crashes

## 2.Comments

In my commit on 2018/11/24, there are the following midifications:

- Finish the gameboard clicking and moving UI. Users may click on an orb to select it, use WASD to move it, and press enter to finish the operation.
- Comprehensive redesign of GameWindow's interface and related business logic. Now GameWindow shall not leave any direct UI operations/methods to OrbGame or CombatGame. Current interface is described as above.
- Move `Type.h` to its parent folder and rename it to `Utils.h`. This file shall now store all frequently-used, cross-file constants, enums, helper functions and other utilities. e.g. `BOARD_ROWS` and `BOARD_COLS` has been added, indicating the dimension of the gameboard.
- Make main.cpp directly generate GameWindow, since MainWindow is not finished yet.
