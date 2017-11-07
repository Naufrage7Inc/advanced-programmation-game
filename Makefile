LIBS=-lSDL2-2.0
CXX := gcc

all: clean game

%.o: %.c
	$(CXX) -g -c $< -o obj/$@

game: main.o engine.o character.o map.o tile.o
	@echo ""
	@echo "** Building the game **"
	@echo ""
	$(CXX) -g -o bin/game obj/*.o $(LIBS)

clean:
	@echo "** Cleaning **"
	@echo ""
	rm -f bin/game obj/*.o
