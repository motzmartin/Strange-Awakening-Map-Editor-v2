#include "Player.h"

Player* Player_Create()
{
	Player* player = calloc(1, sizeof(Player));
	if (!player) return NULL;

	return player;
}

void Player_Update(Player* player, Uint8* keyboard)
{
	if (keyboard[SDL_SCANCODE_LEFT])
	{
		player->pos.x -= 1.f;
	}

	if (keyboard[SDL_SCANCODE_UP])
	{
		player->pos.y -= 1.f;
	}

	if (keyboard[SDL_SCANCODE_RIGHT])
	{
		player->pos.x += 1.f;
	}

	if (keyboard[SDL_SCANCODE_DOWN])
	{
		player->pos.y += 1.f;
	}
}

void Player_Free(Player* player)
{
	free(player);
}
