C_DEFAULT = g++ -std=c++20 -Wall -g
OBJECT = test.o
TARGET = app

$(TARGET): $(OBJECT)
	$(C_DEFAULT) $^ -o $@

$(OBJECT): %.o: %.cpp
	$(C_DEFAULT) -c $< -o $@

.PHONY:
	clean

clean:
	-rm -f $(TARGET) $(OBJECT)