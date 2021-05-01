#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>

#include <chrono>
#include <thread>

int main() {
    using namespace std::this_thread; // sleep_for, sleep_until
    using namespace std::chrono; // nanoseconds, system_clock, seconds

    // Data comes in in the form of integers with a max value of ~10000.
    // This data is then processed to be in a realistic range (for example, speed=10000 is mapped to speed=120km/h)

    // Only necessary for random generation purposes
    srand(1);
    // random generation limits
    int HI = 10;
    int LO = -10;

    int speedHI = 120;
    int speedLO = -120;
    int rpmHI = 10000;
    int brake_pressureHI = 2000;

    double speed = 120, rpm = 2000, steering_pos = 0, throttle_pos = 15, brake_pressure = 800;

    // Main loop
    while(true) {
        // Generate random data
        // speed = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(speedHI-LO)));
        // rpm = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(rpmHI-LO)));
        // steering_pos = (-100) + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(100-(-100))));
        // throttle_pos = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
        // brake_pressure = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(brake_pressureHI-LO)));

        // Generate random increment
        speed = speed + speedLO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(speedHI-speedLO)));
        rpm = rpm + (-rpmHI) + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(rpmHI-(-rpmHI))));
        steering_pos = steering_pos + (-100) + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(100-(-100))));
        throttle_pos = throttle_pos + LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
        brake_pressure = brake_pressure + LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(brake_pressureHI-LO)));

        // Compose string of values to insert into database
        std::string dataline = "(NOW(), " + std::to_string(speed) + ", "
            + std::to_string(rpm) + ", " + std::to_string(steering_pos) + ", "
            + std::to_string(throttle_pos) + ", " + std::to_string(brake_pressure) + ");";

        // Compose SQL query
        std::string command = "docker exec timescaledb "
            "psql --command=\"INSERT INTO vehicle_data VALUES " + dataline + "\" postgresql://datawriter:password@localhost:5432/postgres";

        // Execute SQL query
        system(command.c_str());

        // Wait
        sleep_for(milliseconds(500));

        std::cout << "Data added: " << dataline << std::endl;
    }
}