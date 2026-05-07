#pragma once
#include "IGame.h"
#include <vector>
#include <functional>

using namespace std;

class Game : public IGame {
protected:
    string name;
    int cpu, ram, gpu, storage;

    bool installed = false;
    bool running = false;

    vector<string> saves;

public:
    function<void(string)> onStart;
    function<void(string)> onStop;

    Game(string n, int c, int r, int g, int s);

    virtual bool canRunOn(IDevice&) = 0;

    GameStatus install(IDevice&) override;
    GameStatus run(IUser&, IDevice&) override;
    void stop() override;

    GameStatus save() override;
    GameStatus load() override;

    bool isInstalled() const;
    bool isRunning() const override;
    string getName() const override;


};