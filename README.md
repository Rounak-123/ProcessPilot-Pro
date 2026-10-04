# ProcessPilot Pro

## Linux Service Supervisor

ProcessPilot Pro is a Linux-based service supervision and monitoring system developed using C++ and Linux system programming concepts.

The project demonstrates service management, process monitoring, dependency checking, automatic recovery, system monitoring, logging, and Linux kernel module development.

## Objectives

- Manage Linux processes and services
- Start, stop and restart services
- Monitor service health
- Detect service failures
- Perform automatic recovery
- Check service dependencies
- Maintain application logs
- Display Linux system and hardware information
- Demonstrate Linux kernel module development

## Technologies

- Linux
- C++17
- Linux System Calls
- `/proc` filesystem
- `uname()`
- POSIX process management
- Git
- Linux Kernel Modules
- Make

## Project Structure

```text
ProcessPilot-Pro/
├── driver/
│   ├── Makefile
│   └── processpilot_driver.c
│
├── include/
│   ├── DependencyManager.h
│   ├── Logger.h
│   ├── ServiceManager.h
│   └── SystemMonitor.h
│
├── src/
│   ├── DependencyManager.cpp
│   ├── Logger.cpp
│   ├── ServiceManager.cpp
│   ├── SystemMonitor.cpp
│   └── main.cpp
│
├── docs/
│   ├── Stage1_Project_Introduction.md
│   └── Stage2_PRD.md
│
├── tests/
├── logs/
├── Makefile
└── README.md

Features
Service Management
- Start service
- Stop service
- Restart service
- Check service status
Process Monitoring
ProcessPilot monitors the managed service and detects whether it is running.
Automatic Recovery
If a service failure is detected, ProcessPilot attempts to restart the service automatically.
Dependency Management
Before starting the service, ProcessPilot checks whether required dependencies are available.
Logging
Important events are recorded with timestamps and log levels.
Example:
[INFO] Service started successfully
[WARNING] Service failure detected
[INFO] Automatic recovery started
[INFO] Automatic recovery successful

System Monitoring
The project reads Linux system information including:
- Kernel information
- CPU information
- Memory information
- System architecture
Linux Kernel Module
A basic Linux kernel module is included to demonstrate kernel-level programming.
Build the module:
cd driver
make

Load the module:
sudo insmod processpilot_driver.ko

Check the module:
lsmod | grep processpilot

View kernel messages:
sudo dmesg | tail -n 10

Unload the module:
sudo rmmod processpilot_driver

Build and Run
From the project root:
g++ -std=c++17 -Iinclude src/main.cpp src/ServiceManager.cpp src/DependencyManager.cpp src/Logger.cpp src/SystemMonitor.cpp -o processpilot

Run:
./processpilot

Concepts Demonstrated
- Linux process management
- C++ object-oriented programming
- Process IDs
- Signals
- Process monitoring
- Dependency management
- File handling
- Linux /proc filesystem
- System calls
- Logging
- Error handling
- Linux kernel modules
- Hardware and software interaction
- Git version control
Limitations
- Command-line interface only
- Basic dependency configuration
- Basic kernel module implementation
- Advanced systemd integration is not implemented
Future Improvements
- Systemd service integration
- CPU and memory threshold alerts
- Advanced dependency graphs
- Web-based monitoring dashboard
- Persistent configuration
- Advanced kernel-driver communication
- Notification system
Project Information
Project: ProcessPilot Pro
Type: Individual Capstone Project
Platform: Linux
Language: C++17
Domain: Linux System Programming and Service Management
