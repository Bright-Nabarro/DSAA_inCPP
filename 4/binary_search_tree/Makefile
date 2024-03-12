CC = g++
C_FLAGS = -std=c++20 -g -Og -Wall
TARGET = app
OBJECTS = test.o
DEPS = $(OBJECTS:.o=.d)

$(TARGET): $(OBJECTS)
	$(CC) $(C_FLAGS) $^ -o $@

-include $(DEPS)

$(OBJECTS): %.o: %.cpp
	$(CC) $(C_FLAGS) -c $< -o $@

$(DEPS): %.d : %.cpp
	$(CC) $(C_FLAGS) -MM $< -o $@

.PHONY: clean
clean:
	rm -f $(TARGET) $(OBJECTS) $(DEPS)