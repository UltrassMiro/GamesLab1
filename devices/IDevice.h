#pragma once

class IDevice {
public:
    virtual ~IDevice() = default;

    virtual int getCpu() const = 0;
    virtual int getRam() const = 0;
    virtual int getGpu() const = 0;
    virtual int getStorage() const = 0;

    virtual bool isPC() const = 0;
    virtual bool isMobile() const = 0;
    virtual bool canStream() const = 0;

    virtual bool canRun(
        int requiredCpu,
        int requiredRam,
        int requiredGpu
    ) const = 0;

    virtual bool hasEnoughStorage(
        int requiredStorage
    ) const = 0;

    virtual void useStorage(int size) = 0;
};