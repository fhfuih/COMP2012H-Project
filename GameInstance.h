#ifndef GAMEINSTANCE_H
#define GAMEINSTANCE_H

#include <QWidget>
#include <QCloseEvent>
#include <QLabel>

#include "FileLoader.h"
#include "OrbGame.h"
#include "CombatGame.h"
#include "OrbGameWindow.h"
#include "CombatGameWindow.h"

namespace Ui {
class BigGameWindow;
}

class GameInstance : public QWidget
{
    Q_OBJECT

public:
    explicit GameInstance(int level, int PetMonsterID[5], QWidget *parent = nullptr);
    ~GameInstance() override;

private:
    /* Consist of two sub-window/widgets, and their corresponding backend logic parts */
    Ui::BigGameWindow *ui;
    OrbGame* orb_game;
    CombatGame* combat_game;

    OrbGameWindow* orb_window;
    CombatGameWindow* combat_window;

    virtual void closeEvent(QCloseEvent* event) override;

signals:
    void game_finished(); // emit to SelectionWindow
private slots:
    void DisplayCombatText (QString text, bool playerAction);
    void on_gameFinished(); // accept from CombatGame/Window
};

#endif // GAMEINSTANCE_H
