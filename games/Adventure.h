#pragma once

#include "../core/Game.h"
#include "../compatibility/AnyPlatformStrategy.h"

class Adventure : public Game {
public:
    Adventure(string name, int cpu, int ram, int gpu, int storage)
        : Game(name, cpu, ram, gpu, storage, make_unique<AnyPlatformStrategy>()) {}
};