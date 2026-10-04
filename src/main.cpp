#include <iostream>
#include <string>

#include "ServiceManager.h"
#include "DependencyManager.h"
#include "Logger.h"

void showMenu()
{
    std::cout << "\n=================================\n";
    std::cout << "       PROCESSPILOT PRO\n";
    std::cout << " Linux Service Supervisor\n";
    std::cout << "=================================\n";
    std::cout << "1. Start Service\n";
    std::cout << "2. Stop Service\n";
    std::cout << "3. Restart Service\n";
    std::cout << "4. Check Service Status\n";
    std::cout << "5. Show Dependencies\n";
    std::cout << "6. Exit\n";
    std::cout << "=================================\n";
    std::cout << "Enter choice: ";
}

int main()
{
    ServiceManager service("sleep");

    DependencyManager dependencyManager;

    dependencyManager.addDependency("sleep", "systemd");

    Logger::info("ProcessPilot Pro started");

    std::cout << "\nProcessPilot Pro started.\n";

    int choice;

    while (true)
    {
        showMenu();
        std::cin >> choice;

        switch (choice)
        {
            case 1:
            {
                if (!dependencyManager.checkDependencies("sleep"))
                {
                    std::cout << "Cannot start service.\n";
                    std::cout << "Required dependencies are not available.\n";

                    Logger::warning(
                        "Service startup blocked due to dependency failure"
                    );

                    break;
                }

                if (service.start())
                {
                    std::cout << "Service started.\n";
                    Logger::info("Service started successfully");
                }
                else
                {
                    std::cout << "Failed to start service.\n";
                    Logger::error("Failed to start service");
                }

                break;
            }

            case 2:
            {
                if (service.stop())
                {
                    std::cout << "Service stopped.\n";
                    Logger::info("Service stopped");
                }
                else
                {
                    std::cout << "Failed to stop service.\n";
                    Logger::warning("Failed to stop service");
                }

                break;
            }

            case 3:
            {
                if (service.restart())
                {
                    std::cout << "Service restarted.\n";
                    Logger::info("Service restarted successfully");
                }
                else
                {
                    std::cout << "Failed to restart service.\n";
                    Logger::error("Failed to restart service");
                }

                break;
            }

            case 4:
            {
                if (service.isRunning())
                {
                    std::cout << "Service is RUNNING.\n";
                }
                else
                {
                    std::cout << "Service is NOT RUNNING.\n";
                }

                break;
            }

            case 5:
            {
                dependencyManager.showDependencies("sleep");
                break;
            }

            case 6:
            {
                std::cout << "Exiting ProcessPilot Pro.\n";
                Logger::info("ProcessPilot Pro stopped");
                return 0;
            }

            default:
            {
                std::cout << "Invalid choice.\n";
                break;
            }
        }
    }

    return 0;
}
