#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QCloseEvent>

#include"GameInstance.h"
#include "FileLoader.h"
#include "Utils.h"
#include "PetBox.h"
#include "ButtonWithDagger.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    Ui::MainWindow *ui;
    ButtonWithDagger backButton;
    PetBox* petButtons[PET_TYPES];

    /* some data and user choice */
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
    /* auto-connect signals (on_x_y format) */
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
