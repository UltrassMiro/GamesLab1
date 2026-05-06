#pragma once
#include "Device.h"

class PC : public Device {
public:
    PC(int c, int r, int g, int s) : Device(c, r, g, s) {}
    bool isPC() const override { return true; }
};