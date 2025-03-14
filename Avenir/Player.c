#include "Player.h"

Player* Player_Create()
{
	Player* player = calloc(1, sizeof(Player));
	if (!player) return NULL;

	return player;
}

void Player_Update(Player* player, Uint8* keyboard, Uint64 elapsed)
{
	player->count += elapsed;

	VectorF acceleration = { 0 };

	if (keyboard[SDL_SCANCODE_A] != keyboard[SDL_SCANCODE_D])
	{
		acceleration.x = keyboard[SDL_SCANCODE_A] ? -1.f : 1.f;
	}

	if (keyboard[SDL_SCANCODE_W] != keyboard[SDL_SCANCODE_S])
	{
		acceleration.y = keyboard[SDL_SCANCODE_W] ? -1.f : 1.f;
	}

	acceleration = VectorF_Scale(VectorF_Normalize(acceleration), elapsed * 1.5e-7f);

	VectorF prevPos = player->pos;
	player->pos = VectorF_Add(player->pos, acceleration);

	if (prevPos.x == player->pos.x && prevPos.y == player->pos.y)
	{
		player->sprite.x = 0;
	}
	else
	{
		player->sprite.x = player->count / 125000000 % 4 + 1;

		if (player->pos.x > prevPos.x) player->sprite.y = 3;
		else if (player->pos.x < prevPos.x) player->sprite.y = 1;
		else if (player->pos.y > prevPos.y) player->sprite.y = 0;
		else if (player->pos.y < prevPos.y) player->sprite.y = 2;
	}
}

void Player_Free(Player* player)
{
	free(player);
}
