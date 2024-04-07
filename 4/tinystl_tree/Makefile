CC = g++
C_FLAG = -g -Wall -O0 -std=c++20
TARGET = app
OBJECTS = test_tree.o
HEADER = avl_tree.h
SRC = $(OBJECTS:.o=.cpp)

$(TARGET): $(OBJECTS)
	$(CC) $(C_FLAG) $^ -o $@

$(OBJECTS): $(SRC) $(HEADER)
	$(CC) $(C_FLAG) -c $< -o $@

.PHONY: clean

clean:
	rm -f $(TARGET) $(OBJECTS)