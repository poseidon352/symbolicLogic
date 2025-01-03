CXX = g++
CXXFLAGS = -std=c++20 -Wall
LDFLAGS =

SRC = booleanExpression.cpp TruthTable.cpp Parser.cpp Node.cpp main.cpp
OBJ = $(SRC:.cpp=.o)
EXEC = parser

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(LDFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)

.PHONY: all clean