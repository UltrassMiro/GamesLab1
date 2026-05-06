#pragma once
#include "../core/Game.h"

class Strategy : public Game {
public:
    Strategy(string n, int c, int r, int g, int s) : Game(n, c, r, g, s) {}

    bool canRunOn(IDevice& d) override {
        return d.isPC();
    }
};