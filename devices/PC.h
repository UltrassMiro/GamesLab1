#pragma once
#include "Device.h"

class PC : public Device {
public:
    PC(int cpu, int ram, int gpu, int storage)
        : Device(cpu, ram, gpu, storage) {}

    bool isPC() const override {return true;}

    bool isMobile() const override {return false;}

    bool canStream() const override {return false;}
};