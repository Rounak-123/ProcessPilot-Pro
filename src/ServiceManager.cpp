#include "ServiceManager.h"

#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include "ServiceManager.h"

#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cerrno>
#include <cstring>

ServiceManager::ServiceManager(const std::string& name)
    : serviceName(name), processId(0)
{
}

bool ServiceManager::start()
{
    if (isRunning())
    {
        std::cout << "Service is already running. PID: "
                  << processId << std::endl;
        return false;
    }

    pid_t pid = fork();

    if (pid < 0)
    {
        std::cerr << "Failed to create process: "
                  << std::strerror(errno) << std::endl;
        return false;
    }

    if (pid == 0)
    {
        execlp(
            serviceName.c_str(),
            serviceName.c_str(),
            "30",
            static_cast<char*>(nullptr)
        );

        std::cerr << "Failed to start service: "
                  << std::strerror(errno) << std::endl;

        _exit(EXIT_FAILURE);
    }

    processId = pid;

    std::cout << "Service started successfully. PID: "
              << processId << std::endl;

    return true;
}

bool ServiceManager::stop()
{
    if (!isRunning())
    {
        std::cout << "Service is not running." << std::endl;
        return false;
    }

    if (kill(processId, SIGTERM) == 0)
    {
        std::cout << "Stop signal sent to PID: "
                  << processId << std::endl;

        processId = 0;
        return true;
    }

    std::cerr << "Failed to stop service: "
              << std::strerror(errno) << std::endl;

    return false;
}

bool ServiceManager::restart()
{
    std::cout << "Restarting service..." << std::endl;

    if (isRunning())
    {
        if (!stop())
        {
            std::cerr << "Failed to stop service." << std::endl;
            return false;
        }

        sleep(1);
    }

    return start();
}

bool ServiceManager::isRunning()
{
    if (processId <= 0)
    {
        return false;
    }

    if (kill(processId, 0) == 0)
    {
        return true;
    }

    if (errno == ESRCH)
    {
        processId = 0;
        return false;
    }

    return false;
}
