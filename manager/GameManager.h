#pragma once

#include "../core/GameStatus.h"

class Game;
class IUser;
class IDevice;

class GameManager {

private:

    Game* activeGame = nullptr;

public:
    GameStatus installGame(Game& game, IDevice& device);
    bool hasActiveGame() const;

    bool start(
            Game& game,
            IUser& user,
            IDevice& device
    );

    void clear();
};