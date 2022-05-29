MAINS := main.cpp
NON_FUNC := test_parser.cpp conv.cpp
ALLSRC := $(wildcard *.cpp)
SRC := $(filter-out $(NON_FUNC),$(ALLSRC))
ALLOBJ := $(ALLSRC:.cpp=.o)
OBJ := $(SRC:.cpp=.o)

CXX := g++
CXXFLAGS := -fopenmp -O3 -std=c++17 -w -g  # -w disables warnings

.PHONY: clean all format
#all: clean $(MAINS:.cpp=) format
all: clean $(MAINS:.cpp=)

$(MAINS:.cpp=): $(OBJ) 
	$(CXX) $(CXXFLAGS) $^ -o $@ -lstdc++fs -lboost_program_options
%.o: %.cpp %.h
	$(CXX) -c $(CXXFLAGS) $< -o $@

clean:
	$(RM) $(MAINS:.cpp=)
	$(RM) $(ALLOBJ)


# main: cell.o tile.o main.o format
# 	g++ -o main main.o cell.o tile.o
# conv: cell.o tile.o conv.o format
# 	g++ -o conv conv.o cell.o tile.o


# conv.o: conv.cpp cell.h tile.h
# 	g++ -c -g conv.cpp
# cell.o: cell.cpp cell.h
# 	g++ -c -g cell.cpp
# tile.o: tile.cpp tile.h
# 	g++ -c -g tile.cpp
# main.o: main.cpp cell.h tile.h
# 	g++ -c -g main.cpp

# clean:
# 	rm $(ALLOBJ)

format:
	@echo "format all files"
	@find . -name '*.h' -or -name '*.hpp' -or -name '*.cpp' | xargs clang-format -i -style=file $1