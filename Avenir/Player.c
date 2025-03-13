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

	Vector acceleration = { 0 };

	if (keyboard[SDL_SCANCODE_A] != keyboard[SDL_SCANCODE_D])
	{
		acceleration.x = keyboard[SDL_SCANCODE_A] ? -1.f : 1.f;
	}

	if (keyboard[SDL_SCANCODE_W] != keyboard[SDL_SCANCODE_S])
	{
		acceleration.y = keyboard[SDL_SCANCODE_W] ? -1.f : 1.f;
	}

	acceleration = Vector_Scale(Vector_Normalize(acceleration), elapsed * 1.5E-7F);

	Vector prevPos = player->pos;
	player->pos = Vector_Add(player->pos, acceleration);

	if (prevPos.x == player->pos.x && prevPos.y == player->pos.y)
	{
		player->sprite.x = 0.f;
	}
	else
	{
		player->sprite.x = (float)(player->count / 125000000 % 4 + 1) * 16.f;

		if (player->pos.x > prevPos.x) player->sprite.y = 48.f;
		else if (player->pos.x < prevPos.x) player->sprite.y = 16.f;
		else if (player->pos.y > prevPos.y) player->sprite.y = 0.f;
		else if (player->pos.y < prevPos.y) player->sprite.y = 32.f;
	}
}

void Player_Free(Player* player)
{
	free(player);
}
