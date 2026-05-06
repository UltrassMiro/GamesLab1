#pragma once
#include <string>
#include "GameStatus.h"

using namespace std;

class IUser;
class IDevice;

class IGame {
public:
    virtual GameStatus install(IDevice&) = 0;
    virtual GameStatus run(IUser&, IDevice&) = 0;
    virtual void stop() = 0;

    virtual GameStatus save() = 0;
    virtual GameStatus load() = 0;

    virtual bool isRunning() const = 0;
    virtual string getName() const = 0;

    virtual ~IGame() {}
};