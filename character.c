#include "constants.h"
#include "character.h"


Character* CharacterCreate( const char* imagePath, const Coord position ) {
    Character* character = malloc( sizeof( Character ) );

    SDL_Rect rect = { 0, 0, SIZE_BLOCK, SIZE_BLOCK };
    character->rectSrc = rect;

    character->surfaceTileset = LoadBMP( imagePath );
    character->position = position;
    character->direction = DOWN;

    return character;
}


void CharacterDraw( const Character* character, SDL_Surface* surface ) {
    SDL_Rect dst = { character->position.x * SIZE_BLOCK, character->position.y * SIZE_BLOCK, SIZE_BLOCK, SIZE_BLOCK };
    SDL_BlitSurface( character->surfaceTileset, &( character->rectSrc ), surface, &dst );
}


void CharacterMove( Character* character, const Direction direction, const Map* map ) {
    character->direction = direction;

    SDL_Rect rect = { 0, 0, SIZE_BLOCK, SIZE_BLOCK};

    switch ( direction ) {
        case LEFT:
            if ( character->position.x > 0 ) {
                character->position.x -= 1;
                rect.y = 1 * SIZE_BLOCK;
                character->rectSrc = rect;
            }
            break;
        case RIGHT:
            if ( character->position.x < N_BLOCKS_X - 1 ) {
                character->position.x += 1;
                rect.y = 2 * SIZE_BLOCK;
                character->rectSrc = rect;
            }
            break;
        case UP:
            if ( character->position.y > 0 ) {
                character->position.y -= 1;
                rect.y = 3 * SIZE_BLOCK;
                character->rectSrc = rect;
            }
            break;
        case DOWN:
            if ( character->position.y < N_BLOCKS_Y - 1 ) {
                character->position.y += 1;
                character->rectSrc = rect;
            }
            break;
    }
}


void CharacterTeleport( Character* character ) {
    int x = rand() % 2 * ( N_BLOCKS_X - 1 );
    int y = rand() % 2 * ( N_BLOCKS_Y - 1 );

    if ( x == character->position.x && y == character->position.y ) {
        if ( rand() % 2 ) {
            if ( x == N_BLOCKS_X - 1 )
                x = 0;
            else
                x = N_BLOCKS_X - 1;
        } else {
            if ( y == N_BLOCKS_Y - 1 )
                y = 0;
            else
                y = N_BLOCKS_Y - 1;
        }
    }
    character->position.x = x;
    character->position.y = y;
}


void CharacterFree( Character* character ) {
    SDL_FreeSurface( character->surfaceTileset );
    free( character );
}
