#pragma once

#include "IGame.h"
#include "GameStatus.h"
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include "../observers/IGameObserver.h"
#include "../compatibility/IPlatformCompatibilityStrategy.h"

using namespace std;

class Game : public IGame {
protected:
    string name;

    int cpu;
    int ram;
    int gpu;
    int storage;

    bool installed = false;
    bool running = false;

    vector<string> saves;
    vector<IGameObserver*> observers;

    unique_ptr<IPlatformCompatibilityStrategy> platformStrategy;

    void notifyObservers(
        const string& message,
        GameStatus status
    );

public:
    Game(
        string name,
        int cpu,
        int ram,
        int gpu,
        int storage,
        unique_ptr<IPlatformCompatibilityStrategy> strategy
    );

    void addObserver(IGameObserver* observer);
    void removeObserver(IGameObserver* observer);

    GameStatus install(IDevice& device) override;
    GameStatus run(IUser& user, IDevice& device) override;
    void stop() override;
    GameStatus save() override;
    GameStatus load() override;

    bool isInstalled() const override;
    bool isRunning() const override;
    string getName() const override;
};