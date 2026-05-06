#pragma once

class IUser {
public:
    virtual void login() = 0;
    virtual bool isLogged() const = 0;
    virtual ~IUser() {}
};