#include "KernelInterface.h"

#include <iostream>
#include <fstream>
#include <string>

void KernelInterface::showKernelStatus()
{
    const std::string devicePath = "/dev/processpilot";

    std::ifstream device(devicePath);

    if (!device)
    {
        std::cerr << "\nUnable to open " << devicePath << '\n';
        std::cerr << "Make sure the ProcessPilot kernel module is loaded.\n";
        std::cerr << "You may need to run the application with sudo.\n";
        return;
    }

    std::string status;

    std::getline(device, status);

    std::cout << "\n========== KERNEL COMPONENT ==========\n";
    std::cout << "Device : " << devicePath << '\n';
    std::cout << "Status : " << status << '\n';
    std::cout << "======================================\n";
}
