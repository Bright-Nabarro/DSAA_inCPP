TARGET = app
OBJ = test.o string_hash.o next_prime.o words_generator.o
C_DEFAULT = g++ -Wall -std=c++20 -g

$(TARGET): $(OBJ)
	$(C_DEFAULT) $^ -o $@

$(OBJ): %.o : %.cpp
	$(C_DEFAULT) -c $< -o $@

.PHONY:
	clean

clean:
	rm -f $(OBJ) $(TARGET)