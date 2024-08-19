

#include "lib.hpp"


void lockFile(int fd) {
    if (flock(fd, LOCK_EX) == -1) {
        std::cerr << "Error locking file!" << std::endl;
    }
}

void unlockFile(int fd) {
    if (flock(fd, LOCK_UN) == -1) {
        std::cerr << "Error unlocking file!" << std::endl;
    }
}

std::vector<unsigned char> readDataFromFile(const std::string& filename) {
    int fd = open(filename.c_str(), O_RDONLY);
    lockFile(fd);
    std::ifstream file(filename);
    std::vector<unsigned char> data;
    if (file.is_open()) {
        char value;
        while (file >> std::noskipws >> value) {
            data.push_back(static_cast<unsigned char>(value));
        }
        file.close();

        std::ofstream clearFile(filename, std::ios::trunc);
        clearFile.close();
    }else{
        std::cout<<"file cannot be opened"<<std::endl;
    }
    unlockFile(fd);
    close(fd);
    return data;
}

void appendDataToFile(const std::string& filename, const std::vector<unsigned char>& data) {
    int fd = open(filename.c_str(), O_WRONLY | O_CREAT | O_APPEND, 0644);
    lockFile(fd);
    std::ofstream file(filename);
    if (file.is_open()) {
        for (auto byte : data) {
            file << byte;
        }
        file.close();
    }
    unlockFile(fd);
    close(fd);
}


int timeDifferenceInSeconds(const std::string& time1, const std::string& time2) {
    std::tm tm1 = {};
    std::tm tm2 = {};
    
    std::istringstream ss1(time1);
    std::istringstream ss2(time2);
    
    // Extract time from strings to tm structures
    ss1 >> std::get_time(&tm1, "%H:%M:%S");
    ss2 >> std::get_time(&tm2, "%H:%M:%S");
    
    // Convert tm structures to time_point
    auto tp1 = std::chrono::system_clock::from_time_t(std::mktime(&tm1));
    auto tp2 = std::chrono::system_clock::from_time_t(std::mktime(&tm2));
    
    // Calculate difference in seconds
    auto diff = std::chrono::duration_cast<std::chrono::seconds>(tp2 - tp1);
    
    // Return difference in seconds
    return diff.count();
}




double  toRadians(const  double& degree)
{
    double one_deg = (M_PI) / 180;
    return (one_deg * degree);
}

double  distance(double lat1, double long1, double lat2, double long2)
{
    // Convert the latitudes and longitudes
    // from degree to radians.
    lat1 = toRadians(lat1);
    long1 = toRadians(long1);
    lat2 = toRadians(lat2);
    long2 = toRadians(long2);

    // Haversine Formula
    double dlong = long2 - long1;
    double dlat = lat2 - lat1;

    double ans = pow(sin(dlat / 2), 2) + cos(lat1) * cos(lat2) * pow(sin(dlong / 2), 2);
    ans = 2 * asin(sqrt(ans));

    // Radius of Earth in
    // Kilometers, R = 6371
    // Use R = 3956 for miles
    double R = 6371;

    // Calculate the result
    ans = ans * R;

    return ans*1000;
}

double  calculateHeading(double lat1, double lon1, double lat2, double lon2) {
    // Convert latitude and longitude from degrees to radians
    lat1 *= M_PI / 180.0;
    lon1 *= M_PI / 180.0;
    lat2 *= M_PI / 180.0;
    lon2 *= M_PI / 180.0;

    // Calculate change in longitude
    double dLon = lon2 - lon1;

    // Calculate heading angle using trigonometry
    double y = sin(dLon) * cos(lat2);
    double x = cos(lat1) * sin(lat2) - sin(lat1) * cos(lat2) * cos(dLon);
    double heading = atan2(y, x);

    // Convert heading from radians to degrees
    heading = heading * 180.0 / M_PI;

    // Normalize heading to range [0, 360) degrees
    heading = fmod((heading + 360.0), 360.0);

    return heading;
}

double  calculateHeadingDifference(double heading1, double heading2) {
    double headingDiff = abs(heading1 - heading2);

    return headingDiff;
}

bool isAheadAndSameDirection(double vehicle1Lat1, double vehicle1Lon1, double vehicle1Lat2, double vehicle1Lon2, double vehicle2Lat1, double vehicle2Lon1, double vehicle2Lat2, double vehicle2Lon2) {
    double heading1 = calculateHeading(vehicle1Lat1, vehicle1Lon1, vehicle1Lat2, vehicle1Lon2);
    double heading2 = calculateHeading(vehicle2Lat1, vehicle2Lon1, vehicle2Lat2, vehicle2Lon2);

    double headingDiff = calculateHeadingDifference(heading1, heading2);
    // Determine if in the same direction, typically within a 30 degree cone
    if (headingDiff <= 30) {
        // Calculate distance from vehicle1 point2 to vehicle2 point2
        double dist = distance(vehicle1Lat2, vehicle1Lon2, vehicle2Lat2, vehicle2Lon2);

        // Calculate the bearing from vehicle1's last position to vehicle2's last position
        double bearingToVehicle2 = calculateHeading(vehicle1Lat2, vehicle1Lon2, vehicle2Lat2, vehicle2Lon2);
        double bearingDiffToVehicle2 = calculateHeadingDifference(heading1, bearingToVehicle2);
        // Check if vehicle2 is ahead of vehicle1 (within a 90-degree forward arc)
    if (bearingDiffToVehicle2 <= 45 || bearingDiffToVehicle2 >= 315) {
            return true; // Vehicle2 is ahead and in the same direction
        }
    }
    return false; // Not in the same direction or not ahead
}

bool isAheadAndOppositeDirection(double vehicle1Lat1, double vehicle1Lon1, double vehicle1Lat2, double vehicle1Lon2, double vehicle2Lat1, double vehicle2Lon1, double vehicle2Lat2, double vehicle2Lon2) {
    double heading1 = calculateHeading(vehicle1Lat1, vehicle1Lon1, vehicle1Lat2, vehicle1Lon2);
    double heading2 = calculateHeading(vehicle2Lat1, vehicle2Lon1, vehicle2Lat2, vehicle2Lon2);

    double headingDiff = calculateHeadingDifference(heading1, heading2);

    // Determine if in the opposite direction, typically within a 150 to 210 degree cone
    if (headingDiff >= 150 && headingDiff <= 210) {
        // Calculate distance from vehicle1 point2 to vehicle2 point2
        double dist = distance(vehicle1Lat2, vehicle1Lon2, vehicle2Lat2, vehicle2Lon2);

        // Calculate the bearing from vehicle1's last position to vehicle2's last position
        double bearingToVehicle2 = calculateHeading(vehicle1Lat2, vehicle1Lon2, vehicle2Lat2, vehicle2Lon2);
        double bearingDiffToVehicle2 = calculateHeadingDifference(heading1, bearingToVehicle2);

        // Check if vehicle2 is ahead of vehicle1 (within a 90-degree forward arc)
        if (bearingDiffToVehicle2 >= 135 && bearingDiffToVehicle2 <= 225) {
            return true; // Vehicle2 is ahead and in the opposite direction
        }
    }
    return false; // Not in the opposite direction or not ahead
}




// Function to convert degrees to radians
double degreesToRadians(double degrees) {
    return degrees * M_PI / 180.0;
}

// Function to convert radians to degrees
double radiansToDegrees(double radians) {
    return radians * 180.0 / M_PI;
}



// Function to calculate the bearing between two points
double calculateBearing(double lat1, double lon1, double lat2, double lon2) {
    // Convert latitude and longitude from degrees to radians
    lat1 = degreesToRadians(lat1);
    lon1 = degreesToRadians(lon1);
    lat2 = degreesToRadians(lat2);
    lon2 = degreesToRadians(lon2);

    // Calculate change in longitude
    double dLon = lon2 - lon1;

    // Calculate bearing using trigonometry
    double y = sin(dLon) * cos(lat2);
    double x = cos(lat1) * sin(lat2) - sin(lat1) * cos(lat2) * cos(dLon);
    double bearing = atan2(y, x);

    // Convert bearing from radians to degrees
    bearing = radiansToDegrees(bearing);

    // Normalize bearing to range [0, 360) degrees
    bearing = fmod((bearing + 360.0), 360.0);

    return bearing;
}

// Function to determine if vehicle2 is to the left or right of vehicle1
bool determineRelativePosition(double lat1, double lon1, double lat2, double lon2, double lat3, double lon3) {
    // Calculate the heading of vehicle1 using points (lat1, lon1) and (lat2, lon2)
    double heading = calculateHeading(lat1, lon1, lat2, lon2);

    // Calculate the bearing from vehicle1 to vehicle2 using points (lat2, lon2) and (lat3, lon3)
    double bearing = calculateBearing(lat2, lon2, lat3, lon3);

    // Calculate the relative bearing
    double relativeBearing = fmod((bearing - heading + 360.0), 360.0);

    // Determine if vehicle2 is to the left or right
    if (relativeBearing > 0 && relativeBearing < 180) {
        return 1 ;  //right
    } else {
        return 0;  //left
    }
}