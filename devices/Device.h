#pragma once
#include "IDevice.h"

class Device : public IDevice {
protected:
    int cpu;
    int ram;
    int gpu;
    int storage;

public:
    Device(int cpu, int ram, int gpu, int storage)
        : cpu(cpu), ram(ram), gpu(gpu), storage(storage) {}

    int getCpu() const override {return cpu;}

    int getRam() const override {return ram;}

    int getGpu() const override {return gpu;}

    int getStorage() const override {return storage;}

    bool canRun(int requiredCpu, int requiredRam, int requiredGpu) const override {
        return cpu >= requiredCpu &&
               ram >= requiredRam &&
               gpu >= requiredGpu;
    }

    bool hasEnoughStorage(int requiredStorage) const override {
        return storage >= requiredStorage;
    }

    void useStorage(int size) override {
        storage -= size;
    }
};