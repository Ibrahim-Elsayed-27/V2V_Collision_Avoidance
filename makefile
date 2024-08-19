# Compiler settings
CXX = g++
CXXFLAGS = -std=c++17 -Wall -I. -Icomm_manager -Icomm_manager/spi -Ifeatures -Ifeatures/BSW -Ifeatures/DNPW -Ifeatures/EEBL -Ifeatures/FCW -Ifeatures/IMA -Isensor_manager -ISensors -ISensors/Drivers -IConfig -I/usr/local/include -pg

# Find source files, transform into object file paths
SRCDIR = .
OBJDIR = obj
BINDIR = bin

SOURCES := $(wildcard $(SRCDIR)/APP/*.cpp $(SRCDIR)/lib/*.cpp $(SRCDIR)/comm_manager/*.cpp $(SRCDIR)/comm_manager/spi/*.cpp $(SRCDIR)/features/*.cpp $(SRCDIR)/features/BSW/*.cpp $(SRCDIR)/features/DNPW/*.cpp $(SRCDIR)/features/EEBL/*.cpp $(SRCDIR)/features/FCW/*.cpp $(SRCDIR)/features/IMA/*.cpp $(SRCDIR)/sensor_manager/*.cpp $(SRCDIR)/Sensors/*.cpp $(SRCDIR)/Sensors/Drivers/*.cpp)

OBJECTS := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

# Default target
all: $(BINDIR)/app

# Detect the architecture
ARCH := $(shell uname -m)

LDFLAGS = -L/usr/local/lib -lpigpio -pthread -lrt -pg
CXXFLAGS += -D__arm__


# Link the object files into a binary
$(BINDIR)/app: $(OBJECTS)
	mkdir -p $(@D)
	$(CXX) $(OBJECTS) $(LDFLAGS) -o $@

# Compile source files into object files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up the build
clean:
	rm -rf $(OBJDIR) $(BINDIR)

.PHONY: all clean
