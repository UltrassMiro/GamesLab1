#include "GameManager.h"
#include "../core/IGame.h"

bool GameManager::start(IGame& g, IUser& u, IDevice& d) {
    if (current && current->isRunning())
        return false;

    auto result = g.run(u, d);

    if (result == GameStatus::OK)
        current = &g;

    return result == GameStatus::OK;

}

void GameManager::clear() {
    current = nullptr;
}