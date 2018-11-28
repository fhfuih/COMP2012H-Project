#include "gameinstance.h"

GameInstance::GameInstance(int level, int PetMonsterID[5], QWidget *parent) {
    orb_game = new OrbGame();
    combat_game = new CombatGame(level, PetMonsterID);

    orb_window = new OrbGameWindow(orb_game->orbBoard);
    orb_window->show();

    vector<int> monster {fileLoader().getLevel(level)};
    int EnemyMonsterID[5] {monster[0], monster[1], monster[2], monster[3], monster[4]};
    combat_window = new CombatGameWindow(PetMonsterID, EnemyMonsterID,level);
    combat_window->show();

    //Orb game and combat game
    connect(orb_game, &OrbGame::combo_finish, combat_game, &CombatGame::start_combat);

    //Orb game processor with UI
    connect(orb_window, &OrbGameWindow::orb_selected, orb_game, &OrbGame::on_orb_select);
    connect(orb_window, &OrbGameWindow::orb_move_to, orb_game, &OrbGame::on_orb_move);
    connect(orb_window, &OrbGameWindow::orb_deselected, orb_game, &OrbGame::on_finish_move);
    connect(orb_game, &OrbGame::refresh_board, orb_window, &OrbGameWindow::refresh_board);

    //Combat game processor with UI
    connect(combat_window, &CombatGameWindow::SelectedPetMonster, combat_game, &CombatGame::activate_pet_ability);
    connect(combat_game, &CombatGame::pet_attack_enemy, combat_window, &CombatGameWindow::PetAttackEnemy);
    connect(combat_game, &CombatGame::enemy_attack_player, combat_window, &CombatGameWindow::EnemyAttackPlayer);
    connect(combat_game, &CombatGame::player_update_health, combat_window, &CombatGameWindow::PlayerHealthChange);
    connect(combat_game, &CombatGame::enemy_update_health, combat_window, &CombatGameWindow::EnemyHealthChange);
    connect(combat_game, &CombatGame::special_attack_ready, combat_window, &CombatGameWindow::PetSkillReady);
    connect(combat_game, &CombatGame::enemy_die, combat_window, &CombatGameWindow::EnemyDie);
    connect(combat_game, &CombatGame::player_die, combat_window, &CombatGameWindow::PlayerDie);
    connect(combat_game, &CombatGame::level_cleared, combat_window, &CombatGameWindow::LevelCleared);

    /* Other signals and slots
    CombatGame

    CombatGameWindow
        signals:
            void PetMonsterIndexToID(int ID[5]);
            void EnemyMonsterIndexToID(int ID[5]);
    */

}

GameInstance::~GameInstance() {
    delete orb_game;
    delete combat_game;
    delete orb_window;
    delete combat_window;
}
