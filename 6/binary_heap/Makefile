CC = g++
C_FLAG = -std=c++20 -g -Wall
OBJECTS = test.o
TARGET = app
HEADER = binary_heap.hpp
SRC = $(OBJECTS:.o=.cpp)

$(TARGET): $(OBJECTS)
	$(CC) $(C_FLAG) $^ -o $@

$(OBJECTS): $(SRC) $(HEADER)
	$(CC) $(C_FLAG) -c $(SRC) -o $@

.PHONY: clean
clean:
	rm -f $(TARGET) $(OBJECTS)