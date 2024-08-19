# V2V_Collision_Avoidance

## Overview
**V2V_Collision_Avoidance** is a vehicle-to-vehicle communication project aimed at enhancing road safety by enabling vehicles to communicate and share critical data in real-time to avoid collisions. This project was developed as a graduation project, mentored by Valeo Egypt, and involves a robust and modular software architecture that supports various collision avoidance features.

## Features
The project includes the following key features:

- **Forward Collision Warning (FCW)**: Alerts the driver if there is a risk of collision with a vehicle ahead.
- **Blind Spot Warning (BSW)**: Monitors the blind spots of the vehicle and warns if another vehicle is detected.
- **Dynamic Navigation Prediction Warning (DNPW)**: Provides warnings based on predicted trajectories of surrounding vehicles.
- **Intersection Movement Assistance (IMA)**: Assists in navigating intersections by predicting and avoiding potential collisions.
- **Emergency Electronic Brake Light (EEBL)**: Communicates sudden braking events to vehicles behind to prevent rear-end collisions.

## Sensors
The system uses the following sensors for data collection:

- **IMU (Inertial Measurement Unit)**: Measures vehicle orientation and motion.
- **GPS (Global Positioning System)**: Provides real-time location data.
- **Encoder**: Measures wheel rotation to determine vehicle speed.
- **Ultrasonic Sensors**: Detects objects and measures distances to avoid collisions.

## Controllers
The project integrates multiple controllers to handle various tasks:

- **Raspberry Pi (RPI)**: Serves as the main controller, managing all logic and decision-making processes.
- **ESP32**: Handles vehicle-to-vehicle communication by broadcasting data to nearby vehicles.
- **STM32F401**: Controls motor speed based on signals received from the Raspberry Pi, which are derived from sensor data and V2V communication.

## Software Architecture
The software follows a layered architecture to ensure modularity and ease of integration:

- **Application Layer**: Implements the five features (FCW, BSW, DNPW, IMA, EEBL).
- **Features Layer**: Manages the logic and algorithms for each feature.
- **Features Manager**: Acts as an intermediary between the application layer and lower layers, coordinating data flow and processing.
- **Sensor Manager**: Interfaces with all sensors to collect and process data.
- **Communication Manager**: Manages communication with the ESP32 for V2V communication and the STM32 for motor control.
- **Device Drivers**: Low-level code that interacts directly with the hardware components (sensors and controllers).
- **Libraries (LIB)**: Shared utilities and functions used across different layers.

## Setup and Installation
(TODO: Add instructions for setting up the system, including flashing the customized Yocto Linux image onto the Raspberry Pi, configuring the ESP32 and STM32F401 controllers, and calibrating the sensors.)

## Usage
(TODO: Provide guidelines on how to run the software, interact with the system, and perform tests on the different features using the prototypes developed.)

## Contributions
(TODO: Add guidelines for contributing to the project, including coding standards, branching strategies, and how to submit pull requests.)

## License
(TODO: Provide information about the licensing of the project.)

## Acknowledgments
Special thanks to Valeo Egypt for mentoring this project and to everyone involved in its development.
