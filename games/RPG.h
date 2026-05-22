#pragma once

#include "../core/Game.h"
#include "../compatibility/AnyPlatformStrategy.h"

class RPG : public Game {
private:
    int controllers = 0;

public:
    RPG(string name, int cpu, int ram, int gpu, int storage)
        : Game(name, cpu, ram, gpu, storage,make_unique<AnyPlatformStrategy>()) {}

    void setControllers(int c) {
        controllers = c;
    }

    bool canMultiplayer() const {
        return controllers >= 2;
    }
};