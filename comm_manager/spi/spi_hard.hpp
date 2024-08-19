#ifndef SPI_HARD_H
#define SPI_HARD_H



#include <pigpio.h>
#include <linux/spi/spidev.h>

#include "../../lib/lib.hpp"
#include <cstring>
#include <sys/ioctl.h>

//#define SPI_MODE_0 0



class SPI{
public:
    SPI(const std::string &dev, uint8_t mode, uint32_t speed, uint8_t bitsPerWord);

    ~SPI() ;

    void spi_loop();
    
    

private:
    int spi_fd;
    std::string device;
    uint8_t spiMode;
    uint32_t spiSpeed;
    uint8_t spiBits;

    void transfer(unsigned char send[], unsigned char receive[], int length, uint8_t cs_pin);
    void openDevice();
    void setupCS(uint8_t cs_pin); 



    std::vector<unsigned char> send_esp;
    std::vector<unsigned char> receive_esp;

    std::vector<unsigned char> send_stm;
    std::vector<unsigned char> receive_stm;
    std::string str;

};


#endif