#pragma once

#include <iostream>
#include <map>
#include <string>
#include "IGameObserver.h"

using namespace std;

class AchievementObserver : public IGameObserver {
private:
    map<string, int> launchCount;
    map<string, bool> firstSaveUnlocked;
    map<string, bool> veteranUnlocked;

public:
    void onGameEvent(const GameEventArgs& args) override {
        string gameName = args.getGameName();

        cout << "[EVENT] "
             << gameName
             << ": "
             << args.getMessage()
             << endl;

        if (
            args.getStatus() == GameStatus::OK &&
            args.getMessage() == "Game started successfully"
        ) {
            launchCount[gameName]++;

            cout << "[STATS] "
                 << gameName
                 << " launches: "
                 << launchCount[gameName]
                 << endl;

            if (launchCount[gameName] == 3 && !veteranUnlocked[gameName]) {
                veteranUnlocked[gameName] = true;

                cout << "[ACHIEVEMENT] "
                     << gameName
                     << ": Veteran Player unlocked!"
                     << endl;
            }
        }

        if (
            args.getStatus() == GameStatus::OK &&
            args.getMessage() == "Game state saved"
        ) {
            if (!firstSaveUnlocked[gameName]) {
                firstSaveUnlocked[gameName] = true;

                cout << "[ACHIEVEMENT] "
                     << gameName
                     << ": First Save unlocked!"
                     << endl;
            }
        }
    }
};