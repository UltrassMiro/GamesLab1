#include "Interface.h"
#include "../devices/PC.h"
#include "../devices/Mobile.h"
#include "../games/Adventure.h"
#include "../games/RPG.h"
#include "../games/Strategy.h"
#include "../manager/GameManager.h"
#include "../user/User.h"
#include "../observers/AchievementObserver.h"
#include "../observers/GameEventArgs.h"
#include <iostream>

using namespace std;

Interface::Interface() {
    user = new User();
    device = nullptr;
    game = nullptr;
    manager = new GameManager();

    achievementObserver = new AchievementObserver();

    adventureGame = nullptr;
    rpgGame = nullptr;
    strategyGame = nullptr;
}

Interface::~Interface() {
    delete user;
    delete device;
    delete manager;

    delete adventureGame;
    delete rpgGame;
    delete strategyGame;

    delete achievementObserver;
}

void Interface::selectPC() {
    if (pcConfigured) {
        cout << "Windows PC is already configured.\n";
        cout << "Current PC hardware:\n";
        cout << "CPU=" << pcCpu
             << ", RAM=" << pcRam
             << ", GPU=" << pcGpu
             << ", Storage=" << pcStorage
             << endl;

        delete device;
        device = new PC(pcCpu, pcRam, pcGpu, pcStorage);

        cout << "Windows PC selected again with existing hardware.\n";
        return;
    }

    cout << "Enter PC CPU level: ";
    cin >> pcCpu;

    cout << "Enter PC RAM amount: ";
    cin >> pcRam;

    cout << "Enter PC GPU level: ";
    cin >> pcGpu;

    cout << "Enter PC Storage amount: ";
    cin >> pcStorage;

    pcConfigured = true;

    delete device;
    device = new PC(pcCpu, pcRam, pcGpu, pcStorage);

    cout << "PC selected with hardware:\n";
    cout << "CPU=" << pcCpu
         << ", RAM=" << pcRam
         << ", GPU=" << pcGpu
         << ", Storage=" << pcStorage
         << endl;
}

void Interface::selectMobile() {
    if (mobileConfigured) {
        cout << "Mobile device is already configured.\n";
        cout << "Current mobile hardware:\n";
        cout << "CPU=" << mobileCpu
             << ", RAM=" << mobileRam
             << ", GPU=" << mobileGpu
             << ", Storage=" << mobileStorage
             << endl;

        delete device;
        device = new Mobile(mobileCpu, mobileRam, mobileGpu, mobileStorage);

        cout << "Mobile device selected again with existing hardware.\n";
        return;
    }

    cout << "Enter Mobile CPU level: ";
    cin >> mobileCpu;

    cout << "Enter Mobile RAM amount: ";
    cin >> mobileRam;

    cout << "Enter Mobile GPU level: ";
    cin >> mobileGpu;

    cout << "Enter Mobile Storage amount: ";
    cin >> mobileStorage;

    mobileConfigured = true;

    delete device;
    device = new Mobile(mobileCpu, mobileRam, mobileGpu, mobileStorage);

    cout << "Mobile selected with hardware:\n";
    cout << "CPU=" << mobileCpu
         << ", RAM=" << mobileRam
         << ", GPU=" << mobileGpu
         << ", Storage=" << mobileStorage
         << endl;
}

void Interface::selectAdventure() {
    if (adventureGame == nullptr) {
        adventureGame = new Adventure("Adventure World", 2, 4, 2, 20);
        adventureGame->addObserver(achievementObserver);
    }

    game = adventureGame;

    cout << "Adventure game selected.\n";

    if (game->isInstalled()) {
        cout << "This game is already installed.\n";
    }
}

void Interface::selectRPG() {
    if (rpgGame == nullptr) {
        rpgGame = new RPG("Fantasy RPG", 4, 8, 4, 50);

        int controllers;
        cout << "Enter number of connected controllers: ";
        cin >> controllers;

        rpgGame->setControllers(controllers);
        rpgGame->addObserver(achievementObserver);
    }

    game = rpgGame;

    cout << "RPG game selected.\n";

    if (rpgGame->canMultiplayer()) {
        cout << "Multiplayer mode is available.\n";
    } else {
        cout << "Multiplayer mode is unavailable. At least 2 controllers are required.\n";
    }

    if (game->isInstalled()) {
        cout << "This game is already installed.\n";
    }
}

void Interface::selectStrategy() {
    if (strategyGame == nullptr) {
        strategyGame = new Strategy("War Strategy", 6, 12, 6, 70);
        strategyGame->addObserver(achievementObserver);
    }

    game = strategyGame;

    cout << "Strategy game selected.\n";
    cout << "Requirements: CPU=6, RAM=12, GPU=6, Storage=70\n";

    if (game->isInstalled()) {
        cout << "This game is already installed.\n";
    }
}

void Interface::handleInstall() {
    if (!checkUser() || !checkDevice() || !checkGame()) {
        return;
    }

    manager->installGame(*game, *device);
}

void Interface::handleRun() {
    if (!checkUser() || !checkDevice() || !checkGame()) {
        return;
    }

    if (game->isRunning()) {
        notifySystem(
            "This game is already running. Stop it before starting again.",
            GameStatus::NOT_RUNNING
        );
        return;
    }

    if (manager->hasActiveGame()) {
        notifySystem(
            "Another game is already running. Stop it first.",
            GameStatus::NOT_RUNNING
        );
        return;
    }

    manager->start(*game, *user, *device);
}

void Interface::handleSave() {
    if (!checkGame()) {
        return;
    }

    game->save();
}

void Interface::handleLoad() {
    if (!checkGame()) {
        return;
    }

    game->load();
}

void Interface::handleStop() {
    if (!checkGame()) {
        return;
    }

    game->stop();
    manager->clear();
}

void Interface::handleStream() {
    if (!checkDevice()) {
        return;
    }

    if (device->canStream()) {
        notifySystem(
            "Streaming from mobile device started",
            GameStatus::OK
        );
    } else {
        notifySystem(
            "Streaming is available only from mobile device",
            GameStatus::WRONG_PLATFORM
        );
    }
}

bool Interface::checkUser() {
    if (user == nullptr) {
        notifySystem(
            "User was not created",
            GameStatus::NOT_LOGGED
        );
        return false;
    }

    return true;
}

bool Interface::checkDevice() {
    if (device == nullptr) {
        notifySystem(
            "Device is not selected",
            GameStatus::WEAK_HARDWARE
        );
        return false;
    }

    return true;
}

bool Interface::checkGame() {
    if (game == nullptr) {
        notifySystem(
            "Game is not selected",
            GameStatus::NOT_INSTALLED
        );
        return false;
    }

    return true;
}

bool Interface::checkRunningGame() {
    if (!checkGame())
        return false;

    if (!game->isRunning()) {
        cout << "Error: Game is not running.\n";
        return false;
    }

    return true;
}

bool Interface::checkStoppedGame() {
    if (!checkGame())
        return false;

    if (game->isRunning()) {
        cout << "Error: Game is already running.\n";
        return false;
    }

    return true;
}

bool Interface::checkStrategyPlatform() {
    if (!checkDevice() || !checkGame())
        return false;

    Strategy* strategy = dynamic_cast<Strategy*>(game);
    PC* pc = dynamic_cast<PC*>(device);

    if (strategy != nullptr && pc == nullptr) {
        cout << "Error: Strategy game can run only on Windows PC.\n";
        return false;
    }

    return true;
}
void Interface::notifySystem(
    const string& message,
    GameStatus status
) {
    GameEventArgs args(
        "System",
        message,
        status
    );

    achievementObserver->onGameEvent(args);
}
void Interface::run() {
    char choice;

    do {
        showMainMenu();
        cin >> choice;

        switch (choice) {
        case '1':
            user->login();
            cout << "User logged in successfully.\n";
            break;
        case '2':
            handleDeviceMenu();
            break;
        case '3':
            handleGameMenu();
            break;
        case '4':
            handleActionMenu();
            break;
        case '0':
            cout << "Exit program.\n";
            break;
        default:
            cout << "Invalid choice.\n";
            break;
        }

    } while (choice != '0');
}

void Interface::showMainMenu() {
    cout << "\n===== MAIN MENU =====\n";
    cout << "1 - Login to game account\n";
    cout << "2 - Device menu\n";
    cout << "3 - Game menu\n";
    cout << "4 - Actions menu\n";
    cout << "0 - Exit\n";
    cout << "Choice: ";
}

void Interface::showDeviceMenu() {
    cout << "\n===== DEVICE MENU =====\n";
    cout << "1 - Select Windows PC\n";
    cout << "2 - Select Mobile device\n";
    cout << "0 - Back\n";
    cout << "Choice: ";
}

void Interface::showGameMenu() {
    cout << "\n===== GAME MENU =====\n";
    cout << "1 - Select Adventure game\n";
    cout << "2 - Select RPG game\n";
    cout << "3 - Select Strategy game\n";
    cout << "0 - Back\n";
    cout << "Choice: ";
}

void Interface::showActionMenu() {
    cout << "\n===== ACTION MENU =====\n";
    cout << "1 - Install game\n";
    cout << "2 - Run game\n";
    cout << "3 - Save game\n";
    cout << "4 - Load saved game\n";
    cout << "5 - Stop game\n";
    cout << "6 - Stream\n";
    cout << "0 - Back\n";
    cout << "Choice: ";
}

void Interface::handleDeviceMenu() {
    char choice;

    do {
        showDeviceMenu();
        cin >> choice;

        switch (choice) {
        case '1':
            selectPC();
            break;
        case '2':
            selectMobile();
            break;
        case '0':
            break;
        default:
            cout << "Invalid choice.\n";
            break;
        }

    } while (choice != '0');
}

void Interface::handleGameMenu() {
    char choice;

    do {
        showGameMenu();
        cin >> choice;

        switch (choice) {
        case '1':
            selectAdventure();
            break;
        case '2':
            selectRPG();
            break;
        case '3':
            selectStrategy();
            break;
        case '0':
            break;
        default:
            cout << "Invalid choice.\n";
            break;
        }

    } while (choice != '0');
}

void Interface::handleActionMenu() {
    char choice;

    do {
        showActionMenu();
        cin >> choice;

        switch (choice) {
            case '1':
                handleInstall();
                break;
            case '2':
                handleRun();
                break;
            case '3':
                handleSave();
                break;
            case '4':
                handleLoad();
                break;
            case '5':
                handleStop();
                break;
            case '6':
                handleStream();
                break;
            case '0':
                break;
            default:
                cout << "Invalid choice.\n";
                break;
        }

    } while (choice != '0');
}