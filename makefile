CXX = g++
CXXFLAGS = -Wall -I./include -L./lib
LIBS = -lraylib -lopengl32 -lgdi32 -lwinmm
SRC = c++.cpp BFS.cpp FDS.cpp RAM.cpp
TARGET = main
TARGET1 = main.exe

build:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(LIBS)
	./$(TARGET1)

all: build
