

#include "spi_hard.hpp"



SPI::SPI(const std::string &dev, uint8_t mode, uint32_t speed, uint8_t bitsPerWord):
device(dev), spiMode(mode), spiSpeed(speed), spiBits(bitsPerWord) {
       
    if (gpioInitialise() < 0) {
        std::cerr << "pigpio initialisation failed." << std::endl;
            // Handle error appropriately
        }
    openDevice();
    
}


SPI::~SPI() {
    
        
        close(spi_fd);
        gpioTerminate();
         
       
}




void SPI::transfer(unsigned char send[], unsigned char receive[], int length, uint8_t cs_pin) {
    
    setupCS(cs_pin);
    gpioWrite(cs_pin, 0); // Activate CS line (Low)

    spi_ioc_transfer spiTransfer;
    memset(&spiTransfer, 0, sizeof(spiTransfer));
    spiTransfer.tx_buf = reinterpret_cast<uintptr_t>(send);
    spiTransfer.rx_buf = reinterpret_cast<uintptr_t>(receive);
    spiTransfer.len = length;
    spiTransfer.speed_hz = spiSpeed;
    spiTransfer.bits_per_word = spiBits;

    int status = ioctl(spi_fd, SPI_IOC_MESSAGE(1), &spiTransfer);
    
    if (status < 0) {
        std::cerr << "SPI transfer failed: " << strerror(errno) << std::endl;
        // Optional: Retry the transmission or clean up resources
    } else {
        std::cout << "SPI transfer succeeded, " << receive << std::endl;
    }
    

    gpioWrite(cs_pin, 1); // Deactivate CS line (High)
    
}

void SPI::setupCS(uint8_t cs_pin) {
    
    gpioSetMode(cs_pin, PI_OUTPUT); // Set CS pin as output
    
}


void SPI::openDevice() {
    
    
    spi_fd = open(device.c_str(), O_RDWR);
    ioctl(spi_fd, SPI_IOC_WR_MODE, &spiMode);
    ioctl(spi_fd, SPI_IOC_WR_BITS_PER_WORD, &spiBits);
    ioctl(spi_fd, SPI_IOC_WR_MAX_SPEED_HZ, &spiSpeed);
    

}






void SPI::spi_loop() {
        send_esp = readDataFromFile("/V2V_APP/to_esp32_data.txt");
        receive_esp.resize(send_esp.size());
        send_stm = readDataFromFile("/V2V_APP/to_stm32_data.txt");
        
        transfer(send_esp.data(), receive_esp.data(), send_esp.size(), 7);

        appendDataToFile("/V2V_APP/from_esp32_data.txt", receive_esp);


        
        transfer(send_stm.data(), receive_stm.data(), send_stm.size(), 8);

        


    
}