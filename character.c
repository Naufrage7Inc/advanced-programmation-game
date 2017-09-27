#include "constants.h"
#include "character.h"


Character CharacterCreate( const char* imagePath, const Coord position ) {
    Character character;

    SDL_Rect rect = {0, 0, SIZE_BLOCK, SIZE_BLOCK};
    character.srcRect = rect;

    character.surface = LoadBMP( imagePath );
    character.position = position;
    character.direction = DOWN;

    return character;
}


void CharacterDraw( const Character* character, SDL_Surface* surface ) {
    SDL_Rect dst = { character->position.x * SIZE_BLOCK, character->position.y * SIZE_BLOCK, SIZE_BLOCK, SIZE_BLOCK };
    SDL_BlitSurface( character->surface, &( character->srcRect ), surface, &dst );
}
