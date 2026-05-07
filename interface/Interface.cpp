#include "Interface.h"

#include "../user/User.h"

#include "../devices/PC.h"
#include "../devices/Mobile.h"

#include "../games/RPG.h"
#include "../games/Strategy.h"
#include "../games/Adventure.h"

#include <iostream>

using namespace std;

Interface::Interface() {
    user = new User();
}

Interface::~Interface() {
    delete user;
    delete device;
    delete game;
}

void Interface::handleInstall() {

    if (!user->isLogged()) {
        cout << "Error: user is not logged in\n";
        return;
    }

    if (!device) {
        cout << "Error: device not selected\n";
        return;
    }

    if (!game) {
        cout << "Error: game not selected\n";
        return;
    }

    GameStatus result = game->install(*device);

    if (result == GameStatus::OK)
        cout << "Game installed\n";

    else
        cout << "Error: not enough storage\n";
}

void Interface::handleRun() {

    if (!user->isLogged()) {
        cout << "Error: user is not logged in\n";
        return;
    }

    if (!device) {
        cout << "Error: device not selected\n";
        return;
    }

    if (!game) {
        cout << "Error: game not selected\n";
        return;
    }

    bool result = manager.start(*game, *user, *device);

    if (result)
        cout << "Game started\n";

    else
        cout << "Error: cannot start game\n";
}

void Interface::handleSave() {

    if (!user->isLogged()) {
        cout << "Error: user is not logged in\n";
        return;
    }

    if (!device) {
        cout << "Error: device not selected\n";
        return;
    }

    if (!game) {
        cout << "Error: game not selected\n";
        return;
    }

    GameStatus result = game->save();

    if (result == GameStatus::OK)
        cout << "Game saved\n";

    else
        cout << "Error: game is not running\n";
}

void Interface::handleLoad() {

    if (!user->isLogged()) {
        cout << "Error: user is not logged in\n";
        return;
    }

    if (!device) {
        cout << "Error: device not selected\n";
        return;
    }

    if (!game) {
        cout << "Error: game not selected\n";
        return;
    }

    GameStatus result = game->load();

    if (result == GameStatus::OK)
        cout << "Game loaded\n";

    else if (result == GameStatus::NO_SAVES)
        cout << "Error: no saves found\n";

    else
        cout << "Error: game is not running\n";
}

void Interface::handleStop() {

    if (!user->isLogged()) {
        cout << "Error: user is not logged in\n";
        return;
    }

    if (!game) {
        cout << "Error: game not selected\n";
        return;
    }

    if (!game->isRunning()) {
        cout << "Error: game is not running\n";
        return;
    }

    game->stop();

    cout << "Game stopped\n";
}

void Interface::handleStream() {

    if (!user->isLogged()) {
        cout << "Error: user is not logged in\n";
        return;
    }

    if (!device) {
        cout << "Error: device not selected\n";
        return;
    }

    if (!device->canStream()) {
        cout << "Error: streaming supported only on mobile\n";
        return;
    }

    if (!game) {
        cout << "Error: game not selected\n";
        return;
    }

    if (!game->isRunning()) {
        cout << "Error: game is not running\n";
        return;
    }

    cout << "Streaming started\n";
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
        cout << "w - Stop Game\n";
        cout << "e - Stream\n";

        cout << "0 - Exit\n";

        cout << "Choice: ";

        cin >> choice;

        if (choice == '1') {

            user->login();

            cout << "User logged in\n";
        }

        else if (choice == '2') {

            if (game && game->isRunning()) {
                cout << "Error: stop current game first\n";
                continue;
            }

            int cpu, ram, gpu, storage;

            cout << "Enter CPU RAM GPU STORAGE:\n";

            cin >> cpu >> ram >> gpu >> storage;

            delete device;

            device = new PC(cpu, ram, gpu, storage);

            cout << "PC selected\n";
        }

        else if (choice == '3') {

            if (game && game->isRunning()) {
                cout << "Error: stop current game first\n";
                continue;
            }

            int cpu, ram, gpu, storage;

            cout << "Enter CPU RAM GPU STORAGE:\n";

            cin >> cpu >> ram >> gpu >> storage;

            delete device;

            device = new Mobile(cpu, ram, gpu, storage);

            cout << "Mobile selected\n";
        }

        else if (choice == '4') {

            if (!user->isLogged()) {
                cout << "Error: user is not logged in\n";
                continue;
            }

            if (!device) {
                cout << "Error: device not selected\n";
                continue;
            }

            if (game && game->isRunning()) {
                cout << "Error: stop current game first\n";
                continue;
            }

            delete game;

            game = new Adventure(
                    "Adventure",4,8,4,20
            );

            cout << "Adventure selected\n";
        }

        else if (choice == '5') {

            if (!user->isLogged()) {
                cout << "Error: user is not logged in\n";
                continue;
            }

            if (!device) {
                cout << "Error: device not selected\n";
                continue;
            }

            if (game && game->isRunning()) {
                cout << "Error: stop current game first\n";
                continue;
            }

            delete game;

            RPG* rpg = new RPG(
                    "RPG",4,8,4,20
            );

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

        else if (choice == '6') {

            if (!user->isLogged()) {
                cout << "Error: user is not logged in\n";
                continue;
            }

            if (!device) {
                cout << "Error: device not selected\n";
                continue;
            }

            if (game && game->isRunning()) {
                cout << "Error: stop current game first\n";
                continue;
            }

            if (!device->isPC()) {
                cout << "Error: Strategy supports only PC\n";
                continue;
            }

            delete game;

            game = new Strategy(
                    "Strategy",4,8,4,20
            );

            cout << "Strategy selected\n";
        }

        else if (choice == '7') {
            handleInstall();
        }

        else if (choice == '8') {
            handleRun();
        }

        else if (choice == '9') {
            handleSave();
        }

        else if (choice == 'q') {
            handleLoad();
        }

        else if (choice == 'w') {
            handleStop();
        }

        else if (choice == 'e') {
            handleStream();
        }

    } while (choice != '0');
}