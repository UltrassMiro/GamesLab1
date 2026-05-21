cmake_minimum_required(VERSION 3.27)
project(GamesLab1)

set(CMAKE_CXX_STANDARD 17)

add_executable(GamesLab1 main.cpp
        core/Game.h
        core/Game.cpp
        devices/Device.h
        devices/PC.h
        devices/Mobile.h
        user/User.h
        manager/GameManager.h
        manager/GameManager.cpp
        games/Strategy.h
        games/Adventure.h
        games/RPG.h
        user/IUser.h
        devices/IDevice.h
        core/IGame.h
        interface/Interface.h
        interface/Interface.cpp
        core/GameStatus.h
        observers/GameEventArgs.h
        observers/IGameObserver.h
        compatibility/IPlatformCompatibilityStrategy.h
        compatibility/AnyPlatformStrategy.h
        compatibility/WindowsPcOnlyStrategy.h
        observers/AchievementObserver.h
)
