#pragma once

#include "../core/Game.h"
#include "../compatibility/AnyPlatformStrategy.h"

class Adventure : public Game {
public:
    Adventure(string n, int c, int r, int g, int s)
        : Game(n, c, r, g, s, make_unique<AnyPlatformStrategy>()) {}
};