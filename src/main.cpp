#include <iostream>
#include "ServiceManager.h"

int main()
{
    std::cout << "=================================\n";
    std::cout << "       ProcessPilot Pro\n";
    std::cout << " Linux Service Supervisor\n";
    std::cout << "=================================\n\n";

    ServiceManager service("sleep");

    std::cout << "[1] Starting service...\n";

    if (!service.start())
    {
        std::cout << "Failed to start service.\n";
        return 1;
    }

    std::cout << "[2] Checking service status...\n";

    if (service.isRunning())
    {
        std::cout << "Service is RUNNING.\n";
    }
    else
    {
        std::cout << "Service is NOT RUNNING.\n";
    }

    std::cout << "[3] Stopping service...\n";

    if (service.stop())
    {
        std::cout << "Service stopped.\n";
    }
    else
    {
        std::cout << "Failed to stop service.\n";
    }

    std::cout << "[4] Final status...\n";

    if (service.isRunning())
    {
        std::cout << "Service is still RUNNING.\n";
    }
    else
    {
        std::cout << "Service is NOT RUNNING.\n";
    }

    return 0;
}
