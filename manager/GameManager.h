#pragma once

class IGame;
class IUser;
class IDevice;

class GameManager {
    IGame* current = nullptr;

public:
    bool start(IGame&, IUser&, IDevice&);
    void clear();
};