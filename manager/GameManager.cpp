#include "GameManager.h"
#include "../core/IGame.h"

GameStatus GameManager::installGame(IGame& game, IDevice& device) {
    if (game.isInstalled())
        return GameStatus::ALREADY_INSTALLED;

    return game.install(device);
}

GameStatus GameManager::start(IGame& game, IUser& user, IDevice& device) {
    if (current && current->isRunning())
        return GameStatus::NOT_RUNNING;

    GameStatus result = game.run(user, device);

    if (result == GameStatus::OK)
        current = &game;

    return result;
}

void GameManager::clear() {
    current = nullptr;
}