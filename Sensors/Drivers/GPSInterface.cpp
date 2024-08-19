#include "GPSInterface.hpp"
#include <iostream>
#include <cstring>
#include <vector>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <sstream>

GPSInterface::GPSInterface(const char* device, int baudrate) {
    
    fd_ = setup_serial(device, baudrate);
    
}

GPSInterface::~GPSInterface() {
    
    if (fd_ != -1) {
        close(fd_);
    }
    
}

GPSData GPSInterface::getGPSData() {
    
    std::string buffer;
    char read_buf[1024];
    double latitude, longitude, altitude;
    std::string time;

    while (true) {  // Read loop for each open device
        ssize_t num_read = read(fd_, read_buf, sizeof(read_buf) - 1);
        if (num_read > 0) {
            read_buf[num_read] = '\0';
            buffer.append(read_buf);

            size_t pos;
            while ((pos = buffer.find('\n')) != std::string::npos) {
                std::string line = buffer.substr(0, pos);
                buffer.erase(0, pos + 1);
                if (parse_gps(line, latitude, longitude, altitude, time)) {
                    GPSData data;
                    data.latitude = latitude;
                    data.longitude = longitude;
                    data.altitude = altitude;
                    data.time = time;
                    return data;
                }
            }
        } else if (num_read == 0) {
            std::cerr << "Serial port closed unexpectedly." << std::endl;
            throw std::runtime_error("Serial port closed unexpectedly.");
        } else {
            std::cerr << "Error reading from serial port: " << strerror(errno) << std::endl;
            throw std::runtime_error("Error reading from serial port.");
        }
    }
    
}

int GPSInterface::setup_serial(const char* device, int baudrate) {
    
    int fd = open(device, O_RDWR | O_NOCTTY);
    if (fd == -1) {
        std::cerr << "Error opening serial port " << device << ": " << strerror(errno) << std::endl;
        throw std::runtime_error("Error opening serial port.");
    }

    struct termios tty;
    if (tcgetattr(fd, &tty) != 0) {
        std::cerr << "Error getting attributes: " << strerror(errno) << std::endl;
        close(fd);
        throw std::runtime_error("Error getting attributes.");
    }

    cfsetospeed(&tty, baudrate);
    cfsetispeed(&tty, baudrate);

    tty.c_cflag &= ~(PARENB | CSTOPB | CSIZE | CRTSCTS);
    tty.c_cflag |= (CS8 | CREAD | CLOCAL);

    tty.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);

    tty.c_iflag &= ~(IXON | IXOFF | IXANY | IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL);

    tty.c_oflag &= ~(OPOST | ONLCR);

    if (tcsetattr(fd, TCSANOW, &tty) != 0) {
        std::cerr << "Error setting attributes: " << strerror(errno) << std::endl;
        close(fd);
        throw std::runtime_error("Error setting attributes.");
    }

    return fd;
    
}

bool GPSInterface::parse_gps(const std::string& line, double& latitude, double& longitude, double& altitude, std::string& time) {
    
    if (line.find("$GPGGA") == 0) {
        std::istringstream iss(line);
        std::vector<std::string> tokens;
        std::string token;
        while (getline(iss, token, ',')) {
            tokens.push_back(token);
        }

        if (tokens.size() > 9) {
            time = tokens[1].substr(0, 2) + ":" + tokens[1].substr(2, 2) + ":" + tokens[1].substr(4, 2);
            double lat_deg = std::stod(tokens[2].substr(0, 2));
            double lat_min = std::stod(tokens[2].substr(2));
            latitude = lat_deg + (lat_min / 60.0);
            if (tokens[3] == "S") latitude = -latitude;

            double lon_deg = std::stod(tokens[4].substr(0, 3));
            double lon_min = std::stod(tokens[4].substr(3));
            longitude = lon_deg + (lon_min / 60.0);
            if (tokens[5] == "W") longitude = -longitude;

            altitude = std::stod(tokens[9]);

            return true;
        }
    }
    return false;
    
}


/*
int main() {
    const char* device = "/dev/ttyS0";
    int baudrate = B9600;

    GPSInterface gps(device, baudrate);

    while (true) {
        try {
            GPSData data = gps.getGPSData();
            std::cout << "Latitude: " << data.latitude << ", Longitude: " << data.longitude << ", Time: " << data.time << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Exception occurred: " << e.what() << std::endl;
        }
    }

    return 0;
}
*/