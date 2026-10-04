#include "SystemMonitor.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sys/utsname.h>

void SystemMonitor::showKernelInfo()
{
    struct utsname systemInfo;

    if (uname(&systemInfo) == 0)
    {
        std::cout << "\n--- Kernel Information ---\n";
        std::cout << "System       : " << systemInfo.sysname << '\n';
        std::cout << "Kernel       : " << systemInfo.release << '\n';
        std::cout << "Architecture : " << systemInfo.machine << '\n';
    }
    else
    {
        std::cout << "Unable to read kernel information.\n";
    }
}

void SystemMonitor::showCpuInfo()
{
    std::ifstream file("/proc/cpuinfo");

    if (!file)
    {
        std::cout << "Unable to read CPU information.\n";
        return;
    }

    std::string line;
    int processorCount = 0;
    std::string modelName;

    while (std::getline(file, line))
    {
        if (line.find("processor") == 0)
        {
            processorCount++;
        }

        if (modelName.empty() &&
            line.find("model name") == 0)
        {
            std::size_t position = line.find(':');

            if (position != std::string::npos)
            {
                modelName = line.substr(position + 2);
            }
        }
    }

    std::cout << "\n--- CPU Information ---\n";
    std::cout << "CPU Model      : " << modelName << '\n';
    std::cout << "Logical CPUs   : " << processorCount << '\n';
}

void SystemMonitor::showMemoryInfo()
{
    std::ifstream file("/proc/meminfo");

    if (!file)
    {
        std::cout << "Unable to read memory information.\n";
        return;
    }

    std::string line;
    std::string totalMemory;
    std::string freeMemory;

    while (std::getline(file, line))
    {
        if (line.find("MemTotal:") == 0)
        {
            totalMemory = line;
        }

        if (line.find("MemAvailable:") == 0)
        {
            freeMemory = line;
        }
    }

    std::cout << "\n--- Memory Information ---\n";
    std::cout << "Total Memory : " << totalMemory << '\n';
    std::cout << "Available    : " << freeMemory << '\n';
}

void SystemMonitor::showSystemInfo()
{
    std::cout << "\n=================================\n";
    std::cout << "       SYSTEM INFORMATION\n";
    std::cout << "=================================\n";

    showKernelInfo();
    showCpuInfo();
    showMemoryInfo();
}
