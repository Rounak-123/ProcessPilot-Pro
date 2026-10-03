#ifndef SERVICE_MANAGER_H
#define SERVICE_MANAGER_H

#include <string>
#include <sys/types.h>

class ServiceManager
{
private:
    std::string serviceName;
    pid_t processId;

public:
    ServiceManager(const std::string& name);

    bool start();
    bool stop();
    bool restart();
    bool isRunning();
    bool monitorOnce();
};

#endif
