#pragma once

#include "../core/Game.h"
#include "../compatibility/WindowsPcOnlyStrategy.h"

class Strategy : public Game {
public:
    Strategy(string name, int cpu, int ram, int gpu, int storage)
        : Game(name, cpu, ram, gpu, storage, make_unique<WindowsPcOnlyStrategy>()) {}
};