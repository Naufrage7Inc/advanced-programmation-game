#include "constants.h"
#include "character.h"


Character* CharacterCreate( const char *imagePath, const Coord position ) {
    Character *character = malloc_trace ( sizeof( Character ) );

    SDL_Rect rect = { 0, 0, SIZE_BLOCK, SIZE_BLOCK };

    character->rectSrc = rect;

    character->surfaceTileset = LoadBMP ( imagePath );
    character->position       = position;
    character->direction      = DOWN;

    return character;
}

void CharacterDraw( const Character *character, SDL_Surface *surface ) {
    SDL_Rect dst =
    { character->position.x * SIZE_BLOCK, character->position.y * SIZE_BLOCK,
      SIZE_BLOCK,                         SIZE_BLOCK };

    SDL_BlitSurface ( character->surfaceTileset,
                      &( character->rectSrc ),
                      surface,
                      &dst );
}

void CharacterMove( Character *character, const Direction direction ) {
    character->direction = direction;

    SDL_Rect rect = { 0, 0, SIZE_BLOCK, SIZE_BLOCK };

    switch ( direction ) {
    case LEFT:

        if ( character->position.x > 0 ) {
            character->position.x -= 1;
            rect.y                 = 1 * SIZE_BLOCK;
            character->rectSrc     = rect;
        }
        break;

    case RIGHT:

        if ( character->position.x < N_BLOCKS_X - 1 ) {
            character->position.x += 1;
            rect.y                 = 2 * SIZE_BLOCK;
            character->rectSrc     = rect;
        }
        break;

    case UP:

        if ( character->position.y > 0 ) {
            character->position.y -= 1;
            rect.y                 = 3 * SIZE_BLOCK;
            character->rectSrc     = rect;
        }
        break;

    case DOWN:

        if ( character->position.y < N_BLOCKS_Y - 1 ) {
            character->position.y += 1;
            character->rectSrc     = rect;
        }
        break;
    }
}

void CharacterFree( Character *character ) {
    SDL_FreeSurface ( character->surfaceTileset );
    free_trace ( character );
}

Coord CharacterGetCoord( Character *character ) {
    return character->position;
}

void CharacterSetCoord( Character *character, Coord position ) {
    character->position = position;
}

bool IsThereCharacterAtPosition( const Coord position, Character *character, TList characters ) {
    if ( ( CharacterGetCoord ( character ).x == position.x ) && ( CharacterGetCoord ( character ).y == position.y ) ) {
        return true;
    } else if ( !IsEmpty ( characters ) ) {
        if ( ( CharacterGetCoord ( (Character *)Head ( characters ) ).x == position.x ) &&
             ( CharacterGetCoord ( (Character *)Head ( characters ) ).y == position.y ) ) {
            return true;
        } else {
            return IsThereCharacterAtPosition ( position, character, Rest ( characters ) );
        }
    }
}
