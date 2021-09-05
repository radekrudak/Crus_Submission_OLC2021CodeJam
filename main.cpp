#include "Game.h"

int main()
{
	GameJam game;
	if (game.Construct(256, 240, 4, 4))
		game.Start();
	return 0;
}
