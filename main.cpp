#include "Game.h"

int main()
{
	GameJam game;
	if (game.Construct(256*1.5f, 240*1.5f, 4, 4))
		game.Start();
	return 0;
}
