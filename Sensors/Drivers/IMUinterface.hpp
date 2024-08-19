#ifndef IMAINTERFACE_HPP
#define IMAINTERFACE_HPP

#include <iostream>
#include <iomanip>
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdexcept>

#include "../../Config/config.hpp"


class MPU6050 {
private:
    const float GRAVITY_MS2 = 9.80665;
    const float ACCEL_SCALE_MODIFIER_2G = 16384.0;
    const float ACCEL_SCALE_MODIFIER_4G = 8192.0;
    const float ACCEL_SCALE_MODIFIER_8G = 4096.0;
    const float ACCEL_SCALE_MODIFIER_16G = 2048.0;

    static constexpr int ACCEL_RANGE_2G = 0x00;
    static constexpr int ACCEL_RANGE_4G = 0x08;
    static constexpr int ACCEL_RANGE_8G = 0x10;
    static constexpr int ACCEL_RANGE_16G = 0x18;

    const int PWR_MGMT_1 = 0x6B;
    const int ACCEL_XOUT0 = 0x3B;
    const int ACCEL_YOUT0 = 0x3D;
    const int ACCEL_ZOUT0 = 0x3F;
    const int ACCEL_CONFIG = 0x1C;

    int file;
    int address;

public:
    MPU6050(int address);

    ~MPU6050();

    IMUData readAccelData(bool g = false);

private:
    short readWord(int reg);

    int readAccelRange(bool raw = false);

    void writeRegister(int reg, int value);
};

#endif // IMAINTERFACE_HPP
