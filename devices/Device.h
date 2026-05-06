#pragma once
#include "IDevice.h"

class Device : public IDevice {
protected:
    int cpu, ram, gpu, storage;

public:
    Device(int c, int r, int g, int s)
            : cpu(c), ram(r), gpu(g), storage(s) {}

    bool canRun(int c, int r, int g) const override {
        return cpu >= c && ram >= r && gpu >= g;
    }

    int getStorage() const override { return storage; }
    void useStorage(int s) override { storage -= s; }

    bool isPC() const override { return false; }
    bool isMobile() const override { return false; }
    bool canStream() const override { return false; }
};