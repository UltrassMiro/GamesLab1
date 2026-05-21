#pragma once

class IDevice;

class IPlatformCompatibilityStrategy {
public:
    virtual ~IPlatformCompatibilityStrategy() = default;

    virtual bool isCompatible(IDevice& device) const = 0;
};