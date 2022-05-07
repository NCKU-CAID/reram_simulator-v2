main: cell.o tile.o main.o format
	g++ -o main main.o cell.o tile.o
cell.o: cell.cpp cell.h
	g++ -c cell.cpp
tile.o: tile.cpp tile.h
	g++ -c tile.cpp
main.o: main.cpp cell.h tile.h
	g++ -c main.cpp
clean:
	rm main*.o

format:
	@echo "format all files"
	@find . -name '*.h' -or -name '*.hpp' -or -name '*.cpp' | xargs clang-format -i -style=file $1