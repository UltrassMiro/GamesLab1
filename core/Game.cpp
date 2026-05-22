#include "Game.h"
#include "../devices/IDevice.h"
#include "../user/IUser.h"

Game::Game(
    string name,
    int cpu,
    int ram,
    int gpu,
    int storage,
    unique_ptr<IPlatformCompatibilityStrategy> strategy
)
    : name(name),
      cpu(cpu),
      ram(ram),
      gpu(gpu),
      storage(storage),
      platformStrategy(move(strategy)) {}

void Game::addObserver(IGameObserver* observer) {
    observers.push_back(observer);
}

void Game::removeObserver(IGameObserver* observer) {
    observers.erase(
        remove(observers.begin(), observers.end(), observer),
        observers.end()
    );
}

void Game::notifyObservers(
    const string& message,
    GameStatus status
) {
    GameEventArgs args(name, message, status);

    for (IGameObserver* observer : observers) {
        observer->onGameEvent(args);
    }
}

GameStatus Game::install(IDevice& device) {

    if (!device.hasEnoughStorage(storage)) {
        notifyObservers(
            "Installation failed: not enough HDD space",
            GameStatus::WEAK_HARDWARE
        );

        return GameStatus::WEAK_HARDWARE;
    }

    if (installed) {
        notifyObservers(
            "Installation failed: game is already installed",
            GameStatus::ALREADY_INSTALLED
        );

        return GameStatus::ALREADY_INSTALLED;
    }
    device.useStorage(storage);
    installed = true;

    notifyObservers(
        "Game installed successfully",
        GameStatus::OK
    );

    return GameStatus::OK;
}

GameStatus Game::run(IUser& user, IDevice& device) {
    if (!installed) {
        notifyObservers(
            "Run failed: game is not installed",
            GameStatus::NOT_INSTALLED
        );

        return GameStatus::NOT_INSTALLED;
    }

    if (!user.isLogged()) {
        notifyObservers(
            "Run failed: user is not logged in",
            GameStatus::NOT_LOGGED
        );

        return GameStatus::NOT_LOGGED;
    }

    if (!device.canRun(cpu, ram, gpu)) {
        notifyObservers(
            "Run failed: hardware does not meet minimum requirements",
            GameStatus::WEAK_HARDWARE
        );

        return GameStatus::WEAK_HARDWARE;
    }

    if (!platformStrategy->isCompatible(device)) {
        notifyObservers(
            "Run failed: wrong platform",
            GameStatus::WRONG_PLATFORM
        );

        return GameStatus::WRONG_PLATFORM;
    }

    running = true;

    notifyObservers(
        "Game started successfully",
        GameStatus::OK
    );

    return GameStatus::OK;
}

void Game::stop() {
    if (!running) {
        notifyObservers(
            "Stop failed: game is not running",
            GameStatus::NOT_RUNNING
        );

        return;
    }

    running = false;

    notifyObservers(
        "Game stopped successfully",
        GameStatus::OK
    );
}

GameStatus Game::save() {
    if (!running) {
        notifyObservers(
            "Save failed: game is not running",
            GameStatus::NOT_RUNNING
        );

        return GameStatus::NOT_RUNNING;
    }

    saves.push_back("save");

    notifyObservers(
        "Game state saved",
        GameStatus::OK
    );

    return GameStatus::OK;
}

GameStatus Game::load() {
    if (!running) {
        notifyObservers(
            "Load failed: game is not running",
            GameStatus::NOT_RUNNING
        );

        return GameStatus::NOT_RUNNING;
    }

    if (saves.empty()) {
        notifyObservers(
            "Load failed: no saved states",
            GameStatus::NO_SAVES
        );

        return GameStatus::NO_SAVES;
    }

    notifyObservers(
        "Saved state loaded",
        GameStatus::OK
    );

    return GameStatus::OK;
}

bool Game::isInstalled() const {
    return installed;
}

bool Game::isRunning() const {
    return running;
}

string Game::getName() const {
    return name;
}