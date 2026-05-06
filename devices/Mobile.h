#pragma once
#include "Device.h"

class Mobile : public Device {
public:
    Mobile(int c, int r, int g, int s) : Device(c, r, g, s) {}
    bool isMobile() const override { return true; }
    bool canStream() const override { return true; }
};