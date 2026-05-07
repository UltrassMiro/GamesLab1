#pragma once
#include "../user/IUser.h"
#include "../devices/IDevice.h"
#include "../core/IGame.h"
#include "../manager/GameManager.h"

class Interface {
private:
    IUser* user = nullptr;
    IDevice* device = nullptr;
    IGame* game = nullptr;

    GameManager manager;

    void handleInstall();
    void handleRun();
    void handleSave();
    void handleLoad();
    void handleStop();
    void handleStream();

public:
    Interface();
    ~Interface();

    void run();
};