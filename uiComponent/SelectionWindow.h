#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QCloseEvent>
#include"gameinstance.h"

#include "fileloader.h"
#include "Utils.h"
#include "petbox.h"
#include "buttonwithdagger.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    ButtonWithDagger backButton;
    PetBox* petButtons[PET_TYPES];

    /* user choice */
    int level = 0; // [0, MAX_LEVEL),
    int pets[PET_TEAM_SIZE] = {};
    int selectedCount = 0;
    GameInstance* game_instance;

private:
    /* helper function */
    int idToIndex(int i) { return i - 101; }
    int indexToId(int i) { return i + 101; }
    /* show thumbnail */
    void showThumbnail(int id);
    /* level selection */
    void refreshLevelDisplay();

signals:
    void closed();

private slots:
    /* auto-connect signals */
    void on_Start_clicked();
    void on_LevelSub_clicked();
    void on_LevelAdd_clicked();
    /* self-defined signals */
    void entering_pet_box(int id);
    void clicking_pet_box(int id);
    void on_gameFinished();

private:
    virtual void closeEvent(QCloseEvent* event) override;
};

#endif // MAINWINDOW_H
