#pragma once

class IDevice {
public:
    virtual bool canRun(int, int, int) const = 0;
    virtual int getStorage() const = 0;
    virtual void useStorage(int) = 0;

    virtual bool isPC() const = 0;
    virtual bool isMobile() const = 0;
    virtual bool canStream() const = 0;

    virtual ~IDevice() {}
};