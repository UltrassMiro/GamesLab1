#pragma once

enum class GameStatus {
    OK,
    NOT_INSTALLED,
    ALREADY_INSTALLED,
    NOT_LOGGED,
    WEAK_HARDWARE,
    WRONG_PLATFORM,
    NO_SAVES,
    NOT_RUNNING
};