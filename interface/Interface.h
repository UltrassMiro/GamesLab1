#pragma once
#include "../user/IUser.h"
#include "../devices/IDevice.h"
#include "../core/IGame.h"
#include "../manager/GameManager.h"

class Interface {
    IUser* user = nullptr;
    IDevice* device = nullptr;
    IGame* game = nullptr;

    GameManager manager;

    void handleStream();
public:
    Interface();
    ~Interface();

    void run();
};