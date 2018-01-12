LIBS=-lSDL2 -lSDL2_ttf -lSDL2_mixer
CXX := gcc

Release: all

all: game

%.o: src/%.c
	$(CXX) -g -c $< -o obj/$@

game: main.o engine.o character.o map.o tile.o list.o player.o
	@echo ""
	@echo "** Building the game **"
	@echo ""
	$(CXX) -g -o bin/game obj/*.o $(LIBS)
	@echo ""
	@echo "Lancez le jeu depuis ce repertoire avec la commande : bin/game"

clean:
	@echo "** Cleaning **"
	@echo ""
	rm -f bin/game obj/*.o
