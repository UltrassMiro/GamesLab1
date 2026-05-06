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

void Interface::handleStream() {
    if (!device) {
        cout << "Error: device not selected\n";
        return;
    }

    if (!device->canStream()) {
        cout << "Streaming not supported\n";
        return;
    }

    if (!game || !game->isRunning()) {
        cout << "Game is not running\n";
        return;
    }

    cout << "Streaming started\n";
}

void Interface::run() {
    int choice;

    do {
        cout << "\n1 Login\n2 PC\n3 Mobile\n4 Adventure\n5 RPG\n6 Strategy\n7 Save\n8 Load\n9 Stream\n0 Exit\n";
        cin >> choice;

        if (choice == 1) {
            user->login();
            cout << "Logged\n";
        }

        else if (choice == 2) {
            cout << "Enter CPU, RAM, GPU, Storage" << endl;
            int c,r,g,s;
            cin >> c >> r >> g >> s;
            delete device;
            device = new PC(c,r,g,s);
        }

        else if (choice == 3) {
            cout << "Enter CPU, RAM, GPU, Storage" << endl;
            int c,r,g,s;
            cin >> c >> r >> g >> s;
            delete device;
            device = new Mobile(c,r,g,s);
        }

        else if (choice >= 4 && choice <= 6) {
            if (!device || !user->isLogged()) {
                cout << "Error\n";
                continue;
            }

            delete game;

            if (choice == 4) game = new Adventure("Adv",4,8,4,20);
            if (choice == 5) game = new RPG("RPG",4,8,4,20);
            if (choice == 6) game = new Strategy("Str",4,8,4,20);

            game->install(*device);

            auto ok = manager.start(*game,*user,*device);
            cout << (ok ? "Started\n" : "Failed\n");
        }

        else if (choice == 7) {
            if (game) cout << (game->save()==GameStatus::OK?"Saved\n":"Error\n");
        }

        else if (choice == 8) {
            if (game) cout << (game->load()==GameStatus::OK?"Loaded\n":"Error\n");
        }

        else if (choice == 9) {
            handleStream();
        }

    } while (choice != 0);
}