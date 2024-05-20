TARGET = app
OBJ	= polynomial.o test.o
C_DEFAULT = g++ -g -Wall -std=c++20

$(TARGET): $(OBJ)
	$(C_DEFAULT) $^ -o $@

$(OBJ): %.o : %.cpp
	$(C_DEFAULT) -c $< -o $@

.PHONY:
	clean

clean:
	rm -f $(OBJ) $(TARGET)

