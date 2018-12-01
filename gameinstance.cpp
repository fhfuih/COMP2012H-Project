#include "gameinstance.h"

GameInstance::GameInstance(int level, int PetMonsterID[5], QWidget *parent):
    QWidget(parent)
{
    setGeometry(0, 0, COMBAT_WINDOW_WIDTH, COMBAT_WINDOW_HEIGHT + ORB_WINDOW_HEIGHT+2*BOARD_WIDTH);
    orb_game = new OrbGame();
    combat_game = new CombatGame(level, PetMonsterID);

    big_window = new BigGameWindow(this);
    big_window->setGeometry(0, 0, COMBAT_WINDOW_WIDTH, COMBAT_WINDOW_HEIGHT + ORB_WINDOW_HEIGHT+2*BOARD_WIDTH);

    combat_window = new CombatGameWindow(level, PetMonsterID, big_window);
    combat_window->setGeometry(0, 0, COMBAT_WINDOW_WIDTH, COMBAT_WINDOW_HEIGHT);

    orb_window = new OrbGameWindow(orb_game->orbBoard, big_window);
    orb_window->setGeometry((COMBAT_WINDOW_WIDTH - ORB_WINDOW_WIDTH)/2, COMBAT_WINDOW_HEIGHT+BOARD_WIDTH, ORB_WINDOW_WIDTH, ORB_WINDOW_HEIGHT);
    //orb_window = new OrbGameWindow(orb_game->orbBoard);
    //orb_window->show();

    this->setWindowTitle("Puzzle Dragon - Battleground");
    this->show();

    /* Orb game and combat game */
    connect(orb_window, &OrbGameWindow::animation_start, orb_window, &OrbGameWindow::update_orb_animation_status);
    connect(orb_window, &OrbGameWindow::animation_start, combat_window, &CombatGameWindow::UpdateAnimationStatus);
    connect(orb_game, &OrbGame::combo_finish, combat_game, &CombatGame::start_combat);
    connect(combat_game, &CombatGame::combat_end, orb_game, &OrbGame::on_combat_finish);
    connect(combat_game, &CombatGame::pet_ability_animation, orb_window, &OrbGameWindow::update_orb_animation_status);
    connect(combat_game, &CombatGame::pet_ability_animation, combat_window, &CombatGameWindow::UpdateAnimationStatus);
    connect(orb_game, &OrbGame::animation_end, orb_window, &OrbGameWindow::update_orb_animation_status);
    connect(orb_game, &OrbGame::animation_end, combat_window, &CombatGameWindow::UpdateAnimationStatus);
    connect(combat_game, &CombatGame::player_die, orb_window, &OrbGameWindow::game_over);
    connect(combat_game, &CombatGame::level_cleared, orb_window, &OrbGameWindow::game_over);

    /* Orb game processor with UI */
    connect(orb_window, &OrbGameWindow::orb_selected, orb_game, &OrbGame::on_orb_select);
    connect(orb_window, &OrbGameWindow::orb_move_to, orb_game, &OrbGame::on_orb_move);
    connect(orb_window, &OrbGameWindow::orb_deselected, orb_game, &OrbGame::on_finish_move);
    connect(orb_game, &OrbGame::refresh_board, orb_window, &OrbGameWindow::refresh_board);

    /* Combat game processor with UI */
    connect(combat_window, &CombatGameWindow::SelectedPetMonster, combat_game, &CombatGame::activate_pet_ability);
    connect(combat_game, &CombatGame::pet_attack_enemy, combat_window, &CombatGameWindow::PetAttackEnemy);
    connect(combat_game, &CombatGame::enemy_attack_player, combat_window, &CombatGameWindow::EnemyAttackPlayer);
    connect(combat_game, &CombatGame::player_update_health, combat_window, &CombatGameWindow::PlayerHealthChange);
    connect(combat_game, &CombatGame::enemy_update_health, combat_window, &CombatGameWindow::EnemyHealthChange);
    connect(combat_game, &CombatGame::special_attack_ready, combat_window, &CombatGameWindow::PetSkillReady);
    connect(combat_game, &CombatGame::enemy_die, combat_window, &CombatGameWindow::EnemyDie);
    connect(combat_game, &CombatGame::player_die, combat_window, &CombatGameWindow::PlayerDie);
    connect(combat_game, &CombatGame::level_cleared, combat_window, &CombatGameWindow::LevelCleared);

    /* Other signals and slots */
    connect(combat_window, &CombatGameWindow::gameFinished, this, &GameInstance::on_gameFinished);
    connect(combat_game, &CombatGame::combat_text, big_window, &BigGameWindow::DisplayCombatText);
}

GameInstance::~GameInstance() {
    delete orb_game;
    delete combat_game;
    delete orb_window;
    delete combat_window;
}

void GameInstance::closeEvent(QCloseEvent *event)
{
    emit game_finished();
    event->accept();
}

void GameInstance::on_gameFinished()
{
    close();
}
