CXX = g++
CFLAGS = -fdiagnostics-color=always -g

CWD = $(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))

CPP_SRCS = $(wildcard src/*.cpp src/*/*.cpp)

INCLUDE = -I$(CWD)\SDL\include -I$(CWD)\include

LDFLAGS = -L$(CWD)\SDL\build

LIBS = -lmingw32 -lSDL2

TARGET = main
BUILD_DIR = build/

$(TARGET):
	$(CXX) $(CFLAGS) $(INCLUDE) $(LIBS) $(LDFLAGS) -o $(BUILD_DIR)$(TARGET) $(CPP_SRCS)
