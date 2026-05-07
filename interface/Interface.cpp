#include "Interface.h"

#include "../user/User.h"

#include "../devices/PC.h"
#include "../devices/Mobile.h"

#include "../games/RPG.h"
#include "../games/Strategy.h"
#include "../games/Adventure.h"

#include "../manager/GameManager.h"

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

bool Interface::checkUser() {

    if (!user || !user->isLogged()) {

        cout << "Error: User is not logged in\n";
        return false;
    }

    return true;
}

bool Interface::checkDevice() {

    if (!device) {

        cout << "Error: Device not selected\n";
        return false;
    }

    return true;
}

bool Interface::checkGame() {

    if (!game) {

        cout << "Error: Game not selected\n";
        return false;
    }

    return true;
}

bool Interface::checkRunningGame() {

    if (!checkGame())
        return false;

    if (!game->isRunning()) {

        cout << "Error: Game is not running\n";
        return false;
    }

    return true;
}

bool Interface::checkStoppedGame() {

    if (!game)
        return true;

    if (game->isRunning()) {

        cout << "Error: Stop current game first\n";
        return false;
    }

    return true;
}

bool Interface::checkStrategyPlatform() {

    if (!device || !device->isPC()) {

        cout << "Error: Strategy supports only PC\n";
        return false;
    }

    return true;
}

void Interface::handleInstall() {

    if (!checkUser() || !checkDevice() || !checkGame())
        return;

    GameStatus result = game->install(*device);

    if (result == GameStatus::OK)
        cout << "Game installed\n";

    else
        cout << "Error: Weak hardware\n";
}

void Interface::handleRun() {

    if (!checkUser() || !checkDevice() || !checkGame())
        return;

    if (game->isRunning()) {

        cout << "Error: Game already running\n";
        return;
    }

    bool result = manager->start(*game, *user, *device);

    if (result)
        cout << "Game is running\n";

    else
        cout << "Error: Cannot boot the game\n";
}

void Interface::handleSave() {

    if (!checkUser() || !checkRunningGame())
        return;

    GameStatus result = game->save();

    if (result == GameStatus::OK)
        cout << "Game saved\n";

    else
        cout << "Error: Save failed\n";
}

void Interface::handleLoad() {

    if (!checkUser() || !checkGame())
        return;

    GameStatus result = game->load();

    if (result == GameStatus::OK)
        cout << "Game loaded\n";

    else if (result == GameStatus::NO_SAVES)
        cout << "Error: No saves found\n";

    else
        cout << "Error: Cannot load game\n";
}

void Interface::handleStop() {

    if (!checkRunningGame())
        return;

    game->stop();

    manager->clear();

    cout << "Game stopped\n";
}

void Interface::handleStream() {

    if (!checkUser() || !checkDevice() || !checkRunningGame())
        return;

    if (!device->canStream()) {

        cout << "Error: Streaming supported only on mobile\n";
        return;
    }

    cout << "Streaming started\n";
}

void Interface::selectPC() {

    if (!checkStoppedGame())
        return;

    int cpu, ram, gpu, storage;

    cout << "Enter CPU RAM GPU STORAGE:\n";

    cin >> cpu >> ram >> gpu >> storage;

    delete device;

    device = new PC(cpu, ram, gpu, storage);

    cout << "PC selected\n";
}

void Interface::selectMobile() {

    if (!checkStoppedGame())
        return;

    int cpu, ram, gpu, storage;

    cout << "Enter CPU RAM GPU STORAGE:\n";

    cin >> cpu >> ram >> gpu >> storage;

    delete device;

    device = new Mobile(cpu, ram, gpu, storage);

    cout << "Mobile selected\n";
}

void Interface::selectAdventure() {

    if (!checkStoppedGame())
        return;

    manager->clear();

    delete game;

    game = new Adventure("Adventure",4,16,4,70);

    cout << "Adventure selected\n";
}

void Interface::selectRPG() {

    if (!checkStoppedGame())
        return;

    manager->clear();

    delete game;

    RPG* rpg = new RPG("RPG",4,16,4,30);

    int controllers;

    cout << "Enter controllers count:\n";

    cin >> controllers;

    rpg->setControllers(controllers);

    if (rpg->canMultiplayer())
        cout << "Multiplayer available\n";

    else
        cout << "Multiplayer unavailable\n";

    game = rpg;

    cout << "RPG selected\n";
}

void Interface::selectStrategy() {

    if (!checkStoppedGame())
        return;

    if (!checkStrategyPlatform())
        return;

    manager->clear();

    delete game;

    game = new Strategy("Strategy",4,8,4,20);

    cout << "Strategy selected\n";
}

void Interface::run() {

    char choice;

    do {

        cout << "\n========= MENU =========\n";

        cout << "1 - Login\n";
        cout << "2 - Select PC\n";
        cout << "3 - Select Mobile\n";

        cout << "4 - Select Adventure\n";
        cout << "5 - Select RPG\n";
        cout << "6 - Select Strategy\n";

        cout << "7 - Install Game\n";
        cout << "8 - Run Game\n";
        cout << "9 - Save Game\n";

        cout << "q - Load Game\n";
        cout << "s - Stop Game\n";
        cout << "e - Stream\n";

        cout << "0 - Exit\n";

        cout << "Choice: ";

        cin >> choice;

        if (choice == '1') {

            user->login();

            cout << "User logged in\n";
        }

        else if (choice == '2')
            selectPC();

        else if (choice == '3')
            selectMobile();

        else if (choice == '4')
            selectAdventure();

        else if (choice == '5')
            selectRPG();

        else if (choice == '6')
            selectStrategy();

        else if (choice == '7')
            handleInstall();

        else if (choice == '8')
            handleRun();

        else if (choice == '9')
            handleSave();

        else if (choice == 'q')
            handleLoad();

        else if (choice == 's')
            handleStop();

        else if (choice == 'e')
            handleStream();

        else if (choice != '0')
            cout << "Invalid choice\n";

    } while (choice != '0');
}