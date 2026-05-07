#pragma once

class User;
class Device;
class Game;

class Interface {

private:

    User* user = nullptr;
    Device* device = nullptr;
    Game* game = nullptr;

    class GameManager* manager = nullptr;

    bool checkUser();
    bool checkDevice();
    bool checkGame();
    bool checkRunningGame();
    bool checkStoppedGame();
    bool checkStrategyPlatform();

    void handleInstall();
    void handleRun();
    void handleSave();
    void handleLoad();
    void handleStop();
    void handleStream();

    void selectPC();
    void selectMobile();
    void selectAdventure();
    void selectRPG();
    void selectStrategy();

public:

    Interface();
    ~Interface();

    void run();
};