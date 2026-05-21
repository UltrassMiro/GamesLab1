#pragma once
#include "IPlatformCompatibilityStrategy.h"
#include "../devices/IDevice.h"

class WindowsPcOnlyStrategy : public IPlatformCompatibilityStrategy {
public:
    bool isCompatible(IDevice& device) const override {
        return device.isPC();
    }
};