#include "SystemMonitor.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sys/sysinfo.h>
#include <unistd.h>

void SystemMonitor::showSystemInfo()
{
    std::cout << "\n========== SYSTEM INFORMATION ==========\n";

    struct sysinfo info;

    if (sysinfo(&info) == 0)
    {
        unsigned long long totalRAM =
            static_cast<unsigned long long>(info.totalram) * info.mem_unit;

        unsigned long long freeRAM =
            static_cast<unsigned long long>(info.freeram) * info.mem_unit;

        std::cout << "Total RAM : "
                  << totalRAM / (1024 * 1024)
                  << " MB\n";

        std::cout << "Free RAM  : "
                  << freeRAM / (1024 * 1024)
                  << " MB\n";

        std::cout << "Uptime    : "
                  << info.uptime / 3600
                  << " hours\n";
    }
    else
    {
        std::cout << "Unable to read system information.\n";
    }

    std::ifstream cpuInfo("/proc/cpuinfo");

    if (cpuInfo)
    {
        std::string line;

        while (std::getline(cpuInfo, line))
        {
            if (line.find("model name") == 0)
            {
                std::cout << "CPU       : "
                          << line.substr(line.find(':') + 2)
                          << '\n';
                break;
            }
        }
    }

    std::ifstream versionFile("/proc/version");

    if (versionFile)
    {
        std::string version;
        std::getline(versionFile, version);

        std::cout << "Kernel    : "
                  << version
                  << '\n';
    }

    long cores = sysconf(_SC_NPROCESSORS_ONLN);

    std::cout << "CPU Cores : "
              << cores
              << '\n';

    std::cout << "========================================\n";
}
