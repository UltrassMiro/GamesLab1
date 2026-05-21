#pragma once
#include "IPlatformCompatibilityStrategy.h"

class AnyPlatformStrategy : public IPlatformCompatibilityStrategy {
public:
    bool isCompatible(IDevice& device) const override {
        return true;
    }
};