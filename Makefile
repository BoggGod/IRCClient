# Compiler
CC=g++
# Directories and files
SOURCE_DIR =src
SOURCE_DIR=src
SUB_DIR=src/CustomCommands
SUB_DIR2=src/Functions
SOURCE_FILES=$(wildcard $(SOURCE_DIR)/*.cpp)
SUB_FILES=$(wildcard $(SUB_DIR)/*.cpp)
SUB_FILES2=$(wildcard $(SUB_DIR2)/*.cpp)
OBJECTS=$(SOURCE_FILES:.cpp=.o)
OBJECTS2=$(SUB_FILES:.cpp=.o)
OBJECTS3=$(SUB_FILES2:.cpp=.o)
# Flags
CXXFLAGS += -std=c++11
CFLAGS=-c -Wall -I$(SOURCE_DIR)
LDFLAGS=-lpthread
# Executable
EXECUTABLE=ircclient
#------------------START------------------#
all: $(SOURCE_FILES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) $(OBJECTS2) $(OBJECTS3)
	$(CC) -o $@ $(OBJECTS) $(OBJECTS2) $(OBJECTS3) $(LDFLAGS)

.cpp.o:
	$(CC) $(CXXFLAGS) $(CFLAGS) $< -o $@

clean:
	rm -rf $(SOURCE_DIR)/*.o $(EXECUTABLE)
	rm -rf $(SUB_DIR)/*.o
	rm -rf $(SUB_DIR2)/*.o
