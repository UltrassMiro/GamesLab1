#pragma once
#include "IUser.h"

class User : public IUser {
    bool logged = false;

public:
    void login() override { logged = true; }
    bool isLogged() const override { return logged; }
};