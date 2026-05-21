#pragma once

#include <string>
#include "../core/GameStatus.h"

using namespace std;

class GameEventArgs {
private:
    string gameName;
    string message;
    GameStatus status;

public:
    GameEventArgs(
        const string& gameName,
        const string& message,
        GameStatus status
    )
        : gameName(gameName),
          message(message),
          status(status) {}

    string getGameName() const {
        return gameName;
    }

    string getMessage() const {
        return message;
    }

    GameStatus getStatus() const {
        return status;
    }
};