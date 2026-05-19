#pragma once

#include "../core/GameStatus.h"

class IGame;
class IUser;
class IDevice;

class GameManager {
private:
    IGame* current = nullptr;

public:
    GameStatus installGame(IGame& game, IDevice& device);
    GameStatus start(IGame& game, IUser& user, IDevice& device);
    void clear();
};