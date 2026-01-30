# The compiler we are using
CXX = g++

# Compiler flags (-g for debugging, -Wall for warnings)
CXXFLAGS = -g -Wall

# The name of the final program
TARGET = finalproject

# The files involved
SRCS = main.cpp HashTable.cpp
HEADERS = HashTable.hpp

# Rule: "make" or "make all" will run this
all: $(TARGET)

# Rule: How to build the target
$(TARGET): $(SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

# Rule: "make clean" deletes the program and text files so you can start fresh
clean:
	rm -f $(TARGET) rawdata.txt encrypteddata.txt