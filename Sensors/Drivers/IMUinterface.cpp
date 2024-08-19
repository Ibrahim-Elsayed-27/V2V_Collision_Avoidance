#include "IMUinterface.hpp"

MPU6050::MPU6050(int address) : address(address) {
    
    const char *device = "/dev/i2c-1";
    if ((file = open(device, O_RDWR)) < 0) {
        //throw std::runtime_error("Failed to open the i2c bus");
        std::cerr << "Failed to open the i2c bus" << std::endl;
    }
    else{
        if (ioctl(file, I2C_SLAVE, address) < 0) {
            //throw std::runtime_error("Failed to acquire bus access and/or talk to slave.");
            std::cerr << "Failed to acquire bus access and/or talk to slave." << std::endl;
        }
        // Wake up the MPU-6050 since it starts in sleep mode
    }
    writeRegister(PWR_MGMT_1, 0x00);
    
    
}

MPU6050::~MPU6050() {
    
    close(file);
    
}

short MPU6050::readWord(int reg) {
    
    __s32 res;
    char buf[2];
    buf[0] = reg;
    if (write(file, buf, 1) != 1) {
        throw std::runtime_error("Failed to write to the I2C bus");
    }
    if (read(file, buf, 2) != 2) {
        throw std::runtime_error("Failed to read from the I2C bus");
    }
    res = (buf[0] << 8) | buf[1];
    return res;
    
}

int MPU6050::readAccelRange(bool raw) {
    
    int raw_data = readWord(ACCEL_CONFIG);
    if (raw) {
        return raw_data;
    } else {
        switch (raw_data) {
            case ACCEL_RANGE_2G:
                return 2;
            case ACCEL_RANGE_4G:
                return 4;
            case ACCEL_RANGE_8G:
                return 8;
            case ACCEL_RANGE_16G:
                return 16;
            default:
                return -1;
        }
    }
    
}

IMUData MPU6050::readAccelData(bool g) {
    
    short x = readWord(ACCEL_XOUT0);
    short y = readWord(ACCEL_YOUT0);
    short z = readWord(ACCEL_ZOUT0);
    int accelRange = readAccelRange(true);
    float accelScaleModifier;

    switch (accelRange) {
        case ACCEL_RANGE_2G:
            accelScaleModifier = ACCEL_SCALE_MODIFIER_2G;
            break;
        case ACCEL_RANGE_4G:
            accelScaleModifier = ACCEL_SCALE_MODIFIER_4G;
            break;
        case ACCEL_RANGE_8G:
            accelScaleModifier = ACCEL_SCALE_MODIFIER_8G;
            break;
        case ACCEL_RANGE_16G:
            accelScaleModifier = ACCEL_SCALE_MODIFIER_16G;
            break;
        default:
            accelScaleModifier = ACCEL_SCALE_MODIFIER_2G;
            break;
    }

    IMUData data;
    data.AccX = static_cast<float>(x) / accelScaleModifier;
    data.AccY = static_cast<float>(y) / accelScaleModifier;
    data.AccZ = static_cast<float>(z) / accelScaleModifier;

    if (!g) {
        data.AccX *= GRAVITY_MS2;
        data.AccY *= GRAVITY_MS2;
        data.AccZ *= GRAVITY_MS2;
    }

    return data;
    
}

void MPU6050::writeRegister(int reg, int value) {
    
    char buf[2];
    buf[0] = reg;
    buf[1] = value;
    if (write(file, buf, 2) != 2) {
        throw std::runtime_error("Failed to write to the I2C bus");
        
    }
    
}
