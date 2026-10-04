#ifndef DEPENDENCY_MANAGER_H
#define DEPENDENCY_MANAGER_H

#include <string>
#include <map>
#include <vector>

class DependencyManager
{
private:
    std::map<std::string, std::vector<std::string>> dependencies;

public:
    void addDependency(
        const std::string& service,
        const std::string& dependency
    );

    bool checkDependencies(
        const std::string& service
    ) const;

    void showDependencies(
        const std::string& service
    ) const;
};

#endif
