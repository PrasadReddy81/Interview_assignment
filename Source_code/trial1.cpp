#include <iostream>
#include <fstream>
#include <thread>
#include <atomic>
#include <chrono>
#include <mutex>
#include <termios.h>
#include <unistd.h>
#include <sstream> 

std::atomic<bool> stop_flag(false);
std::atomic<bool> reset_flag(false);
std::mutex mtx;

char getch() {
    char buf = 0;
    struct termios old = {0};
    if (tcgetattr(0, &old) < 0) {
        perror("tcsetattr()");
    }
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0) {
        perror("tcsetattr ICANON");
    }
    if (read(0, &buf, 1) < 0) {
        perror("read()");
    }
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0) {
        perror("tcsetattr ~ICANON");
    }
    return buf;
}

void listenSteeringInput(std::ofstream& log_file) {
    while (true) {
        char ch = getch();
        std::lock_guard<std::mutex> lock(mtx);

        if (ch == 'W' || ch == 'w') {
            std::cout << "Forward" << std::endl;
            log_file << "Forward" << std::endl; // Log the command
        } else if (ch == 'S' || ch == 's') {
            std::cout << "Reverse" << std::endl;
            log_file << "Reverse" << std::endl; // Log the command
        } else if (ch == 'A' || ch == 'a') {
            std::cout << "Left" << std::endl;
            log_file << "Left" << std::endl; // Log the command
        } else if (ch == 'D' || ch == 'd') {
            std::cout << "Right" << std::endl;
            log_file << "Right" << std::endl; // Log the command
        } else if (ch == 'M' || ch == 'm') {
            stop_flag = true;
            std::cout << "BRAKE" << std::endl;
            log_file << "BRAKE" << std::endl; // Log the command
        }
    }
}

void processData(const std::string& accel_file, const std::string& gyro_file, const std::string& obstacle_file) {
    std::ofstream log_file("log.txt", std::ios::app); // Open log file in append mode
    if (!log_file.is_open()) {
        std::cerr << "Error opening log file!" << std::endl;
        return;
    }

    while (true) { // Outer loop to allow restarting after stopping
        std::ifstream accelerometer(accel_file);
        std::ifstream gyro(gyro_file);
        std::ifstream obstacle(obstacle_file);

        std::string accel_line, gyro_line, obstacle_line;

        // Skip header rows
        std::getline(accelerometer, accel_line);
        std::getline(gyro, gyro_line);
        std::getline(obstacle, obstacle_line);

        while (std::getline(accelerometer, accel_line) && std::getline(gyro, gyro_line) && std::getline(obstacle, obstacle_line)) {
            std::lock_guard<std::mutex> lock(mtx);

            std::string timestamp, accel_x, accel_y, accel_z;
            std::string timestamp_gyro, gyro_x, gyro_y, gyro_z;
            int obstacle_value;

            std::stringstream accel_ss(accel_line);
            std::getline(accel_ss, timestamp, ',');
            std::getline(accel_ss, accel_x, ',');
            std::getline(accel_ss, accel_y, ',');
            std::getline(accel_ss, accel_z, ',');

            std::stringstream gyro_ss(gyro_line);
            std::getline(gyro_ss, timestamp_gyro, ',');
            std::getline(gyro_ss, gyro_x, ',');
            std::getline(gyro_ss, gyro_y, ',');
            std::getline(gyro_ss, gyro_z, ',');

            obstacle_value = std::stoi(obstacle_line);
            if (obstacle_value == 1) {
                std::string log_msg = "OBSTACLE DETECTED\n";
                log_msg += "Accelerator Timestamp: " + timestamp + ", Accelerator: " + accel_x + ", " + accel_y + ", " + accel_z + "\n";
                log_msg += "Gyro Timestamp: " + timestamp_gyro + ", Gyro: " + gyro_x + ", " + gyro_y + ", " + gyro_z + "\n";

                std::cout << log_msg;
                log_file << log_msg;

                if (stop_flag) {
                    std::cout << "STOPPED" << std::endl;
                    log_file << "STOPPED" << std::endl; // Log the STOPPED message
                    reset_flag = true;
                    break;
                }
            } else {
                std::cout << "OBSTACLE NOT DETECTED" << std::endl;
                log_file << "OBSTACLE NOT DETECTED" << std::endl;
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }

        if (reset_flag) {
            std::cout << "Restarting data processing..." << std::endl;
            log_file << "Restarting data processing..." << std::endl;
            stop_flag = false;
            reset_flag = false;
            continue; // Restart the outer loop
        }

        break; // Exit the outer loop if no reset is required
    }

    log_file.close(); // Close the log file
}

int main() {
    std::string accel_file = "accelerometer.csv";
    std::string gyro_file = "gyro.csv";
    std::string obstacle_file = "obstacle.csv";
    
    std::ofstream log_file("log.txt", std::ios::app); // Open log file in main
    if (!log_file.is_open()) {
        std::cerr << "Error opening log file!" << std::endl;
        return 1;
    }

    std::thread data_thread(processData, accel_file, gyro_file, obstacle_file);
    std::thread steering_thread(listenSteeringInput, std::ref(log_file)); // Pass log file to steering thread
    data_thread.join();
    steering_thread.join();

    log_file.close(); // Close the log file before exiting
    return 0;
}
