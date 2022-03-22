#include "Game.h"
#include "StringID.h"

#define CUTE_SOUND_FORCE_SDL
#define CUTE_SOUND_IMPLEMENTATION
#include <cute_sound.h>

int main(int argv, char** args)
{
	Game game(StringID::windowTitle.c_str());
    if(game.init()) {
        game.startGameLoop();
    }

	return 0;
}