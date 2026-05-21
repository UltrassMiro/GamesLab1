#pragma once

#include "GameEventArgs.h"

class IGameObserver {
public:
    virtual ~IGameObserver() = default;

    virtual void onGameEvent(const GameEventArgs& args) = 0;
};