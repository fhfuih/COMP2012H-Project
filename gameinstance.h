#ifndef GAMEINSTANCE_H
#define GAMEINSTANCE_H

#include <QWidget>
#include <QCloseEvent>

#include "fileloader.h"
#include "OrbGame.h"
#include "CombatGame.h"
#include "OrbGameWindow.h"
#include "CombatGameWindow.h"

class GameInstance : public QWidget
{
    Q_OBJECT

public:
    explicit GameInstance(QWidget *parent = nullptr);
    ~GameInstance() override;

private:
    OrbGame* orb_game;
    CombatGame* combat_game;

    OrbGameWindow* orb_window;
    CombatGameWindow* combat_window;
};

#endif // GAMEINSTANCE_H
