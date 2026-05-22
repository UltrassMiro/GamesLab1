#pragma once
#include "../core/GameStatus.h"
#include <string>

using namespace std;

class User;
class Device;
class Game;
class AchievementObserver;


class Interface {
private:
    User* user = nullptr;
    Device* device = nullptr;
    Game* game = nullptr;
    AchievementObserver* achievementObserver = nullptr;
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

    void showMainMenu();
    void showDeviceMenu();
    void showGameMenu();
    void showActionMenu();

    void handleDeviceMenu();
    void handleGameMenu();
    void handleActionMenu();

    bool pcConfigured = false;
    bool mobileConfigured = false;

    int pcCpu = 0;
    int pcRam = 0;
    int pcGpu = 0;
    int pcStorage = 0;

    int mobileCpu = 0;
    int mobileRam = 0;
    int mobileGpu = 0;
    int mobileStorage = 0;

    void notifySystem(
        const string& message,
        GameStatus status
    );
public:

    Interface();
    ~Interface();
    void run();
};