CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude

TARGET = processpilot

SRC = src/main.cpp \
      src/ServiceManager.cpp \
      src/DependencyManager.cpp \
      src/Logger.cpp \
      src/SystemMonitor.cpp \
      src/KernelInterface.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)
