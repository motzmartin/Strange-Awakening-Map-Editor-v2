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

	Vector prevPos = player->pos;
	Vector acceleration = { 0 };

	if (keyboard[SDL_SCANCODE_A] != keyboard[SDL_SCANCODE_D])
	{
		if (keyboard[SDL_SCANCODE_A]) acceleration.x = -1.f;
		else acceleration.x = 1.f;
	}

	if (keyboard[SDL_SCANCODE_W] != keyboard[SDL_SCANCODE_S])
	{
		if (keyboard[SDL_SCANCODE_W]) acceleration.y = -1.f;
		else acceleration.y = 1.f;
	}

	acceleration = Vector_Scale(Vector_Normalize(acceleration), elapsed * 0.15f);
	player->pos = Vector_Add(player->pos, acceleration);

	if (player->pos.x > prevPos.x) player->sprite.y = 48.f;
	else if (player->pos.x < prevPos.x) player->sprite.y = 16.f;
	else if (player->pos.y > prevPos.y) player->sprite.y = 0.f;
	else if (player->pos.y < prevPos.y) player->sprite.y = 32.f;

	if (prevPos.x == player->pos.x && prevPos.y == player->pos.y)
	{
		player->sprite.x = 0.f;
	}
	else
	{
		player->sprite.x = (float)(player->count % 500 / 125 + 1) * 16.f;
	}
}

void Player_Free(Player* player)
{
	free(player);
}
