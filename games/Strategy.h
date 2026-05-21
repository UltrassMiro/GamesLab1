#pragma once

#include "../core/Game.h"
#include "../compatibility/WindowsPcOnlyStrategy.h"

class Strategy : public Game {
public:
    Strategy(string n, int c, int r, int g, int s)
        : Game(n, c, r, g, s, make_unique<WindowsPcOnlyStrategy>()) {}
};