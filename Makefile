CC = g++
CFLAGS = --std=c++20 -Wall -Werror -pedantic -g
LIB = -lboost_unit_test_framework -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

DEPS = Sokoban.hpp

OBJECTS = Sokoban.o
MAIN_OBJECTS = main.o $(OBJECTS)
TEST_OBJECTS = test.o $(OBJECTS)

PROGRAM = Sokoban
TEST_PROGRAM = test
STAT_LIB = Sokoban.a

.PHONY: all clean lint

all: $(PROGRAM) $(TEST_PROGRAM) $(STAT_LIB)

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<

$(PROGRAM): $(MAIN_OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

$(TEST_PROGRAM): $(TEST_OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

$(STAT_LIB): $(OBJECTS)
	ar rcs $@ $^

clean:
	rm -f *.o $(PROGRAM) $(STAT_LIB) $(TEST_PROGRAM)

lint:
	cpplint *.cpp *.hpp
