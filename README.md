# COMP 2012H Project [Puzzle Dragon]



[TOC]

## Documentation

Below is a summary of each component in Puzzle Dragon code. Please find detailed implementations from embedded comments in the source code.

### Main

Trivial.

### Orb Component

Backend processor for orb game functions. Receives user input signal from OrbGameWindow and monitors orb movement. When user finishes orb movement, OrbGame will process orb combos. Number of combos and corresponding orbs will be removed form the orb board. Then, a the missing orbs will be regenerated without new combos. Combo information will be passed to combat component. New board state will be passed back to OrbGameWindow.

### Combat Component

Backend processor for combat game functions. Receives orb combo information from OrbGame and executes combat procedure. Combo information will be used to calculate output damage for each pet monster. Pets will first damage their corresponding enemy targets. Then, enemy monsters will take turns to damage the player. Combat information will be signaled to CombatGameWindow to display graphically. If pet ability becomes ready, a signal will be sent to CombatGameWindow to activate the pet button. When the pet button is pressed, the pet ability function will be processed. When either all enemy monsters are defeated or player health reaches zero, a signal will be sent to indicate game over.

### User Interface Component

Frontend user interface to accept user input and display graphics. OrbGameWindow accepts input to the orb board and send signals to the OrbGame processor. CombatGameWindow displays combat animation and accepts pet ability activation, in connection with CombatGame processor. SelectionWindow allows user to select team of pet monsters and game level. StartWindow lets user enter game and read information from AboutWindow.

### Other Components

Other components and utilities in Puzzle Dragon code. FileLoader is used to load pet monster, enemy monster, and level information to be used for game execution. Utils is used to store game constants such as combat parameters, orb board parameters, and window geometry. GameInstance is used to construct a game instance connect all components of Puzzle Dragon frontend and backend.



## Resources

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
│  │  DisplayBorder.png
│  │  logo2-indicator.png
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
│  │  SkillReady.png
│  │  yellowSquare.jpg
│  │
│  ├─0 other resources
│  │  ├─100 other_PM_icons
│  │  │      101_icon.png
│  │  │      102_icon.png
│  │  │      103_icon.png
│  │  │      104_icon.png
│  │  │      105_icon.png
│  │  │      106_icon.png
│  │  │      107_icon.png
│  │  │      108_icon.png
│  │  │      109_icon.png
│  │  │      110_icon.png
│  │  │      PM11.png
│  │  │      PM13.png
│  │  │      PM14.png
│  │  │      PM15.png
│  │  │      PM16.png
│  │  │      PM17.png
│  │  │      PM18.png
│  │  │      PM19.png
│  │  │
│  │  └─200 other_EM_icons
│  │  │      EM10.png
│  │  │      EM11.png
│  │  │      EM12.png
│  │  │      EM13.png
│  │  │      EM16.png
│  │  │      EM17.png
│  │  │      EM18.png
│  │  │      EM2.png
│  │  │      EM3.png
│  │  │      EM6.png
│  │  │      EM7.png
│  │  │      EM8.png
│  │  │      EM9.png
│  │  │  deathSymbol.png
│  │  │  logo2-add.png
│  │  │  logo2-emptyStar.PNG
│  │  │  logo2-fullStar.PNG
│  │  │  logo2-pause.png
│  │  │  logo2-play.png
│  │  │  logo2-sad.PNG
│  │  │  logo2-smile.PNG
│  │  │  logo2-symbol1.PNG
│  │  │  logo2-symbol2.PNG
│  │  │  OrbGameBoard.jpg
│  │  │  SkillReady_transparent.png
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
