#include "DependencyManager.h"

#include <iostream>
#include <cstdlib>

void DependencyManager::addDependency(
    const std::string& service,
    const std::string& dependency)
{
    dependencies[service].push_back(dependency);
}

bool DependencyManager::checkDependencies(
    const std::string& service) const
{
    auto it = dependencies.find(service);

    if (it == dependencies.end())
    {
        return true;
    }

    for (const auto& dependency : it->second)
    {
        std::string command = "pgrep -x \"" + dependency + "\" > /dev/null 2>&1";

        if (std::system(command.c_str()) != 0)
        {
            return false;
        }
    }

    return true;
}

void DependencyManager::showDependencies(
    const std::string& service) const
{
    auto it = dependencies.find(service);

    if (it == dependencies.end())
    {
        std::cout << "No dependencies configured.\n";
        return;
    }

    std::cout << "Dependencies for " << service << ":\n";

    for (const auto& dependency : it->second)
    {
        std::string command =
            "pgrep -x \"" + dependency + "\" > /dev/null 2>&1";

        bool running = (std::system(command.c_str()) == 0);

        std::cout << "  - " << dependency << " : "
                  << (running ? "RUNNING" : "NOT RUNNING")
                  << '\n';
    }
}
