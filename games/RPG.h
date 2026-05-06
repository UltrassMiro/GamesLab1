#pragma once
#include "../core/Game.h"

class RPG : public Game {
    int controllers = 0;

public:
    RPG(string n, int c, int r, int g, int s) : Game(n, c, r, g, s) {}

    bool canRunOn(IDevice&) override {
        return true;
    }

    void setControllers(int c) {
        controllers = c;
    }

    bool canMultiplayer() const {
        return controllers >= 2;
    }
};