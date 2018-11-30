#ifndef GAMEINSTANCE_H
#define GAMEINSTANCE_H

#include <QWidget>
#include <QCloseEvent>
#include <QLabel>

#include "fileloader.h"
#include "OrbGame.h"
#include "CombatGame.h"
#include "OrbGameWindow.h"
#include "CombatGameWindow.h"
#include "biggamewindow.h"

class GameInstance : public QWidget
{
    Q_OBJECT

public:
    explicit GameInstance(int level, int PetMonsterID[5], QWidget *parent = nullptr);
    ~GameInstance() override;

private:
    OrbGame* orb_game;
    CombatGame* combat_game;

    OrbGameWindow* orb_window;
    CombatGameWindow* combat_window;


    QLabel* left;
    QLabel* right;

    virtual void closeEvent(QCloseEvent* event) override;

signals:
    void game_finished();
private slots:
    void on_gameFinished();
};

#endif // GAMEINSTANCE_H
