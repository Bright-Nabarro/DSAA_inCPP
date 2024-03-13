TARGET = app
OBJECTS = test.o
CC = g++ -std=c++20 -g -O0 -Wall

$(TARGET): $(OBJECTS)
	$(CC) $^ -o $@

DEPS = $(OBJECTS:.o=.d)
-include $(DEPS)

$(OBJECTS): %.o : %.cpp
	$(CC) -c $< -o $@

$(DEPS): %.d : %.cpp
	$(CC) -MM $< -o $@

.PHONY: clean
clean:
	rm -f $(TARGET) $(OBJECTS) $(DEPS)