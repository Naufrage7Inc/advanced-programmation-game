LIBS=-lSDL2 -lSDL2_ttf -lSDL2_mixer
CXX := gcc

Release: all

all: clean game

%.o: %.c
	$(CXX) -g -c $< -o obj/$@

game: main.o engine.o character.o map.o tile.o list.o
	@echo ""
	@echo "** Building the game **"
	@echo ""
	$(CXX) -g -o bin/game obj/*.o $(LIBS)

clean:
	@echo "** Cleaning **"
	@echo ""
	rm -f bin/game obj/*.o
