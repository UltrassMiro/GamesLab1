#include "GameManager.h"
#include "../core/Game.h"
#include "../user/IUser.h"
#include "../devices/IDevice.h"

GameStatus GameManager::installGame(Game& game, IDevice& device) {
    return game.install(device);
}

bool GameManager::start(Game& game, IUser& user, IDevice& device) {
    if (activeGame != nullptr && activeGame != &game) {
        return false;
    }

    if (activeGame == &game && game.isRunning()) {
        return false;
    }

    GameStatus result = game.run(user, device);

    if (result == GameStatus::OK) {
        activeGame = &game;
        return true;
    }

    return false;
}

void GameManager::clear() {
    activeGame = nullptr;
}

bool GameManager::hasActiveGame() const {
    return activeGame != nullptr;
}