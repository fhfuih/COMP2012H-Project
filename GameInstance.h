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
//#include "BigGameWindow.h"

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
    Ui::BigGameWindow *ui;
    OrbGame* orb_game;
    CombatGame* combat_game;

//    BigGameWindow* big_window;
    OrbGameWindow* orb_window;
    CombatGameWindow* combat_window;

    QLabel* left;
    QLabel* right;

    virtual void closeEvent(QCloseEvent* event) override;

signals:
    void game_finished();
private slots:
    void DisplayCombatText (QString text, bool playerAction);
    void on_gameFinished();
};

#endif // GAMEINSTANCE_H
