#pragma once
#include "Device.h"

class Mobile : public Device {
public:
    Mobile(int cpu, int ram, int gpu, int storage)
        : Device(cpu, ram, gpu, storage) {}

    bool isPC() const override {return false;}
    bool isMobile() const override {return true;}
    bool canStream() const override {return true;}
};