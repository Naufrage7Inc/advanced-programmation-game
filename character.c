#include "character.h"


Character CharacterCreate( const SDL_Surface* surface, const Coord position, const Size size ) {
    Character character;

    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = size.w;
    rect.h = size.h;

    character.srcRect = rect;

    character.surface = surface;
    character.position = position;
    character.size = size;
    character.direction = DOWN;

    return character;
}
