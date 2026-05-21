#pragma once

#include "../core/Game.h"
#include "../compatibility/AnyPlatformStrategy.h"

class RPG : public Game {
private:
    int controllers = 0;

public:
    RPG(string n, int c, int r, int g, int s)
        : Game(n, c, r, g, s, make_unique<AnyPlatformStrategy>()) {}

    void setControllers(int c) {
        controllers = c;
    }

    bool canMultiplayer() const {
        return controllers >= 2;
    }
};