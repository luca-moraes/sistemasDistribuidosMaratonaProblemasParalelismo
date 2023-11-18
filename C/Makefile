# the compiler: gcc for C program, define as g++ for C++
CC = g++

# compiler flags:
#  -Ofast     - this flag includes all O3 flag optimization + some others
#  -Wall  - this flag is used to turn on most compiler warnings
CFLAGS  = -Ofast -Wall

# The build target 
TARGET = npbonacci

all: $(TARGET)

$(TARGET): $(TARGET).cpp
			$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).cpp

clean:
			$(RM) $(TARGET)