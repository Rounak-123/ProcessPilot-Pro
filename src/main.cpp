#include <iostream>
#include <unistd.h>
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

    std::cout << "[2] Service started.\n";

    sleep(2);

    std::cout << "[3] Restarting service...\n";

    if (service.restart())
    {
        std::cout << "[4] Service restarted successfully.\n";
    }
    else
    {
        std::cout << "Failed to restart service.\n";
    }

    return 0;
}
