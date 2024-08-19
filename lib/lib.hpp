#ifndef LIB_H_
#define LIB_H_


#include "lib_includes.hpp"

void lockFile(int fd);

void unlockFile(int fd);

std::vector<unsigned char> readDataFromFile(const std::string& filename) ;

void appendDataToFile(const std::string& filename, const std::vector<unsigned char>& data);


int timeDifferenceInSeconds(const std::string& time1, const std::string& time2);


double toRadians(const  double& degree);
double distance(double lat1, double long1, double lat2, double long2);
double calculateHeading(double lat1, double lon1, double lat2, double lon2);
double calculateHeadingDifference(double heading1, double heading2);
bool isAheadAndSameDirection(double vehicle1Lat1, double vehicle1Lon1, double vehicle1Lat2, double vehicle1Lon2, double vehicle2Lat1, double vehicle2Lon1, double vehicle2Lat2, double vehicle2Lon2);
bool isAheadAndOppositeDirection(double vehicle1Lat1, double vehicle1Lon1, double vehicle1Lat2, double vehicle1Lon2, double vehicle2Lat1, double vehicle2Lon1, double vehicle2Lat2, double vehicle2Lon2);



double radiansToDegrees(double radians);
double degreesToRadians(double degrees) ;
double calculateBearing(double lat1, double lon1, double lat2, double lon2) ;
bool determineRelativePosition(double lat1, double lon1, double lat2, double lon2, double lat3, double lon3);


#endif