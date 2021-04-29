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

    srand(1);

    double speed, rpm, steering_pos, throttle_pos, brake_pressure;

    // random generation limits
    int HI = 10;
    int LO = 1;

    // Main loop
    while(true) {
        // Generate random data
        speed = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
        rpm = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
        steering_pos = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
        throttle_pos = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
        brake_pressure = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));

        std::string dataline = "(NOW(), " + std::to_string(speed) + ", "
            + std::to_string(rpm) + ", " + std::to_string(steering_pos) + ", "
            + std::to_string(throttle_pos) + ", " + std::to_string(brake_pressure) + ");";

        //std::string command = "docker exec -it timescaledb PGPASSWORD='password' "
        std::string command = "docker exec timescaledb "
            "psql --command=\"INSERT INTO vehicle_data VALUES " + dataline + "\" postgresql://datawriter:password@localhost:5432/postgres";
            // WORKS "psql \"host=localhost port=5432 dbname=postgres user=datawriter password=password\"; "
            //"psql --username datawriter --dbname postgres " 
            //"psql \"postgresql://datawriter:password@postgres/postgres\" "
            //"psql postgresql://[datawriter[:password]@][localhost[:5432]"
            //"INSERT INTO vehicle_data VALUES " +
            //dataline;

        // Add data to server
        system(command.c_str());

        // Wait 1 second
        sleep_for(seconds(1));

        std::cout << "Adding data: " << dataline << std::endl;
    }
}