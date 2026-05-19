#include "Interface.h"
#include "../devices/PC.h"
#include "../devices/Mobile.h"
#include "../games/Adventure.h"
#include "../games/RPG.h"
#include "../games/Strategy.h"
#include "../manager/GameManager.h"
#include "../user/User.h"

#include <iostream>

using namespace std;

Interface::Interface() {
    user = new User();
    device = nullptr;
    game = nullptr;
    manager = new GameManager();
}

Interface::~Interface() {
    delete user;
    delete device;
    delete game;
    delete manager;
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

void Interface::selectPC() {
    delete device;
    device = new PC(8, 16, 6, 500);

    cout << "Windows PC selected.\n";
}

void Interface::selectMobile() {
    delete device;
    device = new Mobile(4, 8, 3, 128);

    cout << "Mobile device selected.\n";
}

void Interface::selectAdventure() {
    delete game;
    game = new Adventure("Adventure World", 2, 4, 2, 20);

    cout << "Adventure game selected.\n";
}

void Interface::selectRPG() {
    delete game;
    game = new RPG("Fantasy RPG", 4, 8, 4, 50);

    cout << "RPG game selected.\n";
}

void Interface::selectStrategy() {
    delete game;
    game = new Strategy("War Strategy", 6, 12, 6, 70);

    cout << "Strategy game selected.\n";
}

void Interface::handleInstall() {
    if (!checkUser() || !checkDevice() || !checkGame())
        return;

    GameStatus result = manager->installGame(*game, *device);

    switch (result) {
    case GameStatus::OK:
        cout << "Game installed successfully.\n";
        break;
    case GameStatus::ALREADY_INSTALLED:
        cout << "Error: Game is already installed.\n";
        break;
    case GameStatus::WEAK_HARDWARE:
        cout << "Error: Not enough free HDD space.\n";
        break;
    default:
        cout << "Error: Game installation failed.\n";
        break;
    }
}

void Interface::handleRun() {
    if (!checkUser() || !checkDevice() || !checkGame())
        return;

    GameStatus result = manager->start(*game, *user, *device);

    switch (result) {
    case GameStatus::OK:
        cout << "Game started successfully.\n";
        break;
    case GameStatus::NOT_INSTALLED:
        cout << "Error: Game is not installed.\n";
        break;
    case GameStatus::NOT_LOGGED:
        cout << "Error: User is not logged in.\n";
        break;
    case GameStatus::WEAK_HARDWARE:
        cout << "Error: Hardware does not meet game requirements.\n";
        break;
    case GameStatus::WRONG_PLATFORM:
        cout << "Error: This game cannot run on selected platform.\n";
        break;
    default:
        cout << "Error: Another game is already running.\n";
        break;
    }
}

void Interface::handleSave() {
    if (!checkGame())
        return;

    GameStatus result = game->save();

    if (result == GameStatus::OK)
        cout << "Game state saved successfully.\n";
    else if (result == GameStatus::NOT_RUNNING)
        cout << "Error: Game is not running.\n";
    else
        cout << "Error: Save failed.\n";
}

void Interface::handleLoad() {
    if (!checkGame())
        return;

    GameStatus result = game->load();

    if (result == GameStatus::OK)
        cout << "Saved game loaded successfully.\n";
    else if (result == GameStatus::NO_SAVES)
        cout << "Error: No saved states found.\n";
    else if (result == GameStatus::NOT_RUNNING)
        cout << "Error: Game is not running.\n";
    else
        cout << "Error: Load failed.\n";
}

void Interface::handleStop() {
    if (!checkGame())
        return;

    if (!game->isRunning()) {
        cout << "Error: Game is not running.\n";
        return;
    }

    game->stop();
    manager->clear();

    cout << "Game stopped successfully.\n";
}

void Interface::handleStream() {
    if (!checkDevice())
        return;

    if (device->canStream())
        cout << "Streaming from mobile device started.\n";
    else
        cout << "Error: Streaming is available only from mobile device.\n";
}

bool Interface::checkUser() {
    if (user == nullptr) {
        cout << "Error: User was not created.\n";
        return false;
    }

    return true;
}

bool Interface::checkDevice() {
    if (device == nullptr) {
        cout << "Error: Device is not selected.\n";
        return false;
    }

    return true;
}

bool Interface::checkGame() {
    if (game == nullptr) {
        cout << "Error: Game is not selected.\n";
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
    cout << "6 - Stream from mobile device\n";
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