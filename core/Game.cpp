#include "Game.h"
#include "../devices/IDevice.h"
#include "../user/IUser.h"

Game::Game(string n, int c, int r, int g, int s)
        : name(n), cpu(c), ram(r), gpu(g), storage(s) {}

GameStatus Game::install(IDevice& d) {
    if (installed)
        return GameStatus::ALREADY_INSTALLED;

    if (d.getStorage() < storage)
        return GameStatus::WEAK_HARDWARE;

    d.useStorage(storage);
    installed = true;

    return GameStatus::OK;
}

bool Game::isInstalled() const {
    return installed;
}

GameStatus Game::run(IUser& u, IDevice& d) {
    if (!installed)
        return GameStatus::NOT_INSTALLED;

    if (!u.isLogged())
        return GameStatus::NOT_LOGGED;

    if (!d.canRun(cpu, ram, gpu))
        return GameStatus::WEAK_HARDWARE;

    if (!canRunOn(d))
        return GameStatus::WRONG_PLATFORM;

    running = true;

    if (onStart)
        onStart(name);

    return GameStatus::OK;
}

void Game::stop() {
    if (!running) return;

    running = false;

    if (onStop)
        onStop(name);
}

GameStatus Game::save() {
    if (!running)
        return GameStatus::NOT_RUNNING;

    saves.push_back("save");
    return GameStatus::OK;
}

GameStatus Game::load() {
    if (!running)
        return GameStatus::NOT_RUNNING;

    if (saves.empty())
        return GameStatus::NO_SAVES;

    return GameStatus::OK;
}

bool Game::isRunning() const { return running; }
string Game::getName() const { return name; }