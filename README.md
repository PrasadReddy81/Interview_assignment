# Real-Time Sensor Data Processing and Steering Control

This is a C++ program that simulates real-time data processing from multiple sensors (accelerometer, gyroscope, and obstacle detection) and allows steering input from the user. It processes and logs both sensor data and user commands in real-time using multithreading.

## Features
- Real-time steering control through keyboard input (W, A, S, D, M keys).
- Real-time processing of accelerometer, gyroscope, and obstacle detection data.
- Thread-safe logging of both user input and sensor data into a `log.txt` file.
- Multithreading to allow concurrent processing of user input and sensor data.
- Automatic system stop and restart based on obstacle detection or user input.

## Prerequisites
To run this program, you need the following:
- A C++ compiler with C++11 (or higher) support, such as `g++`.
- POSIX-compliant operating system (Linux, macOS) for the `getch()` function.
  - **Note**: This program uses `termios` for non-blocking input, which is not supported on Windows out of the box.

## Compiling the Program


`g++ -std=c++11 -o trial1 trial1.cpp -lpthread`
This command:

To compile a C++ program with the options used, the following command is issued: g++ -std=c++11 -o trial1 trial1.cpp -lpthread. Let's analyze it to understand the need of each part:

* g++: This is the example of the GNU C++ developed by FSF which is employed to convert C++ source code files into a binary executable.

* -std=c++11: This option enables the compiler to support a version C++11 standard. C++11 has many new features that are used in your code and are not supported in the standard libraries prior to this version (for example std::thread, std::atomic, std::lock_guard, etc.). Without this, the compiler could default to a version of the C++ standard older than this version thus resulting in errors.

* -o trial1: This option when provided forces the compiler to create an executable file called trial1. If you do not supply this, then a.out or a similar default output file name for your system will be the default name of the output.

* trial1.cpp: This is the C++ source file that you are compiling. This time, trials.cpp is the program that your compiling.

* -lpthread: This option is used to link the pthread library which is also known as POSIX threads library. Your program runs multithreads, instances being std::thread, hence the -lpthread flag should be used for linking threading library under Linux operating system. Otherwise, the linker would have no idea how to address its multi-thread functions.

#### After running this command:
If there are no errors, the executable trial1 will be created.
You can verify the creation of the executable by listing files in the directory:


You should see trial1 in the list.

Running the executable:

To run the generated executable, use:


    ./trial1
    
This will execute your program.

Compiles trial1.cpp using the C++11 standard.
Links with the pthread library for multithreading support.
Running the Program
Once compiled, run the program as follows:


    ./trial1
  
#### Input
The following keys are used for user input (steering control):

  W: Move Forward
  S: Move Reverse
  A: Turn Left
  D: Turn Right
  M: BRAKE (Stop the system)
  
#### Output
The program displays the following information in the terminal and logs it in log.txt:

User commands (e.g., "Forward", "BRAKE").
Sensor data (accelerometer, gyroscope, obstacle detection).
Special messages, such as "OBSTACLE DETECTED" or "STOPPED", when triggered by the system.
File Structure
trial1.cpp: The main C++ program that runs the simulation.
accelerometer.csv, gyro.csv, obstacle.csv: The CSV files containing simulated sensor data (you need to provide these files).
log.txt: A log file where all feedback and events are recorded.
Example CSV Format
Ensure that your CSV files follow this format:

#### accelerometer.csv:

    Timestamp,Accel_X,Accel_Y,Accel_Z
    Accelerator Timestamp: 1.71857E+12, Accelerator: 0.3907766940425339, -0.172633975, 0.4692011844719466
...
#### gyro.csv:

  Timestamp,Gyro_X,Gyro_Y,Gyro_Z
  Gyro Timestamp: 1.71857E+12, Gyro: 163.14170277922682, -85.56966001, -78.27850842
...
#### obstacle.csv:

  Obstacle_Value
  0 OBSTACLE NOT DETECTED
  1 OBSTACLE DETECTED

...
Obstacle_Value can be 0 (no obstacle) or 1 (obstacle detected).
Logging
All events, including user inputs and sensor data, are logged into a log.txt file located in the same directory as the program. This file will be created if it doesn't exist or appended to if it does.

### License
This project is open-source and available under the MIT License.



### Summary:
- The `README.md` provides an overview of the project.
- It explains the features, how to compile, how to run the program, and provides information about the CSV file formats required.
- It also describes how logging works, and what is expected in the output.

Let me know if you want to modify anything or add additional sections!
