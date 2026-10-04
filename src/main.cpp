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

    for (int i = 1; i <= 20; i++)
    {
        sleep(2);

        if (service.monitorOnce())
        {
            std::cout << "Monitor " << i
                      << ": Service is RUNNING.\n";
        }
        else
        {
            std::cout << "Monitor " << i
                      << ": Service failure detected!\n";

            std::cout << "Attempting automatic recovery...\n";

            if (service.restart())
            {
                std::cout << "Recovery successful. Service restarted.\n";
            }
            else
            {
                std::cout << "Recovery failed.\n";
                return 1;
            }
        }
    }

    return 0;
}
