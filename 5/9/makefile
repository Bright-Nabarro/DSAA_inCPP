C_DEFAULT = g++ -std=c++20 -g
WORDSRC = ../../word_generator
VPATH = $(WORDSRC):../testPrimer
TARGET = app
OBJECTS = three_hash.o test.o 
WORD_OBJ = words_generator.o 

$(TARGET): $(OBJECTS) $(WORD_OBJ) next_prime.o
	$(C_DEFAULT) $^ -o $@

$(OBJECTS): %.o: %.cpp
	$(C_DEFAULT) -c $< -o $@

$(WORD_OBJ): %.o: $(WORDSRC)/%.cpp
	$(C_DEFAULT) -c $< -o $@

next_prime.o: %.o: %.cpp
	$(C_DEFAULT) -c ../testPrimer/$< -o $@

.PHONY: clean
clean:
	rm -f *.o app