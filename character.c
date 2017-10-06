
#include "constants.h"
#include "character.h"


Character CharacterCreate( const char* imagePath, const Coord position ) {
    Character character;

    SDL_Rect rect = {3 * 48, 0, SIZE_BLOCK, SIZE_BLOCK};
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


void CharacterMove( Character* character, int direction ) {
    character->direction = direction;

    SDL_Rect rect = {3 * 48, 0, SIZE_BLOCK, SIZE_BLOCK};

    switch ( direction ) {
    case LEFT:
        if ( character->position.x > 0 ) {
            character->position.x -= 1;
            rect.y = 1 * 48;
            character->srcRect = rect;
        }
        break;
    case RIGHT:
        if ( character->position.x < N_BLOCKS_X - 1 ) {
            character->position.x += 1;
            rect.y = 2 * 48;
            character->srcRect = rect;
        }
        break;
    case UP:
        if ( character->position.y > 0 ) {
            character->position.y -= 1;
            rect.y = 3 * 48;
            character->srcRect = rect;
        }
        break;
    case DOWN:
        if ( character->position.y < N_BLOCKS_Y - 1 ) {
            character->position.y += 1;
            character->srcRect = rect;
        }
        break;
    }
}
