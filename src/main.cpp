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

    std::cout << "Starting service...\n";

    if (!service.start())
    {
        std::cout << "Failed to start service.\n";
        return 1;
    }

    std::cout << "Service started.\n";

    for (int i = 1; i <= 5; i++)
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
                      << ": Service has EXITED.\n";
            break;
        }
    }

    return 0;
}
