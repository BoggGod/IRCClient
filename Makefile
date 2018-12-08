# Compiler
CC=g++
# Directories and files
SOURCE_DIR =src
SOURCE_DIR=src
SUB_DIR=src/CustomCommands
SUB_DIR2=src/Functions
SUB_DIR3=src/Models
SUB_DIR4=src/Api
SOURCE_FILES=$(wildcard $(SOURCE_DIR)/*.cpp)
SUB_FILES=$(wildcard $(SUB_DIR)/*.cpp)
SUB_FILES2=$(wildcard $(SUB_DIR2)/*.cpp)
SUB_FILES3=$(wildcard $(SUB_DIR3)/*.cpp)
SUB_FILES4=$(wildcard $(SUB_DIR4)/*.cpp)
OBJECTS=$(SOURCE_FILES:.cpp=.o)
OBJECTS2=$(SUB_FILES:.cpp=.o)
OBJECTS3=$(SUB_FILES2:.cpp=.o)
OBJECTS4=$(SUB_FILES3:.cpp=.o)
OBJECTS5=$(SUB_FILES4:.cpp=.o)
# Flags
CXXFLAGS += -std=c++11 -g
CFLAGS=-c -Wall -I$(SOURCE_DIR)
LDFLAGS=-lpthread -lcpprest -lssl -lcrypto -lboost_system  -lboost_thread -lboost_chrono
# Executable
EXECUTABLE=ircclient
#------------------START------------------#
all: $(SOURCE_FILES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) $(OBJECTS2) $(OBJECTS3) $(OBJECTS4) $(OBJECTS5)
	$(CC) -o $@ $(OBJECTS) $(OBJECTS2) $(OBJECTS3) $(OBJECTS4) $(OBJECTS5) $(LDFLAGS) 

.cpp.o:
	$(CC) $(CXXFLAGS) $(CFLAGS) $< -o $@

clean:
	rm -rf $(SOURCE_DIR)/*.o $(EXECUTABLE)
	rm -rf $(SUB_DIR)/*.o
	rm -rf $(SUB_DIR2)/*.o
	rm -rf $(SUB_DIR3)/*.o
	rm -rf $(SUB_DIR4)/*.o
