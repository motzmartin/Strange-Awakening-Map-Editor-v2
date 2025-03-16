#include "Player.h"

Player* Player_Create()
{
	Player* player = calloc(1, sizeof(Player));
	if (!player) return NULL;

	return player;
}

void Player_Update(Player* player, Uint8* keyboard, DynamicArray* collisions, float elapsed)
{
	player->counter += elapsed;

	player->acc = VectorF_New(0.f, 0.f);

	if (keyboard[SDL_SCANCODE_A] != keyboard[SDL_SCANCODE_D])
	{
		player->acc.x = keyboard[SDL_SCANCODE_A] ? -1.f : 1.f;
	}

	if (keyboard[SDL_SCANCODE_W] != keyboard[SDL_SCANCODE_S])
	{
		player->acc.y = keyboard[SDL_SCANCODE_W] ? -1.f : 1.f;
	}

	player->acc = VectorF_Scale(VectorF_Normalize(player->acc), elapsed * 150.f);

	VectorF prevPos = player->pos;

	player->pos.x += player->acc.x;
	Player_ProcessCollisionsX(player, collisions);

	player->pos.y += player->acc.y;
	Player_ProcessCollisionsY(player, collisions);

	if (VectorF_AreEqual(player->pos, prevPos))
	{
		player->sprite.x = 0;

		if (player->acc.x > 0.f) player->sprite.y = 3;
		else if (player->acc.x < 0.f) player->sprite.y = 1;
		else if (player->acc.y > 0.f) player->sprite.y = 0;
		else if (player->acc.y < 0.f) player->sprite.y = 2;

		player->counter = 0.f;
	}
	else
	{
		player->sprite.x = (int)(player->counter * 6.f) % 4 + 1;

		if (player->pos.x > prevPos.x) player->sprite.y = 3;
		else if (player->pos.x < prevPos.x) player->sprite.y = 1;
		else if (player->pos.y > prevPos.y) player->sprite.y = 0;
		else if (player->pos.y < prevPos.y) player->sprite.y = 2;
	}
}

Box* Player_IsColliding(Player* player, DynamicArray* collisions)
{
	for (int i = 0; i < DynamicArray_GetSize(collisions); i++)
	{
		Box* collision = DynamicArray_Get(collisions, i);

		if (player->pos.x + 45.f > (float)collision->pos.x * 12.f &&
			player->pos.x + 3.f < (float)(collision->pos.x + collision->size.x) * 12.f &&
			player->pos.y + 48.f > (float)collision->pos.y * 12.f &&
			player->pos.y + 48.f < (float)(collision->pos.y + collision->size.y) * 12.f)
		{
			return collision;
		}
	}

	return NULL;
}

void Player_ProcessCollisionsX(Player* player, DynamicArray* collisions)
{
	Box* collision = Player_IsColliding(player, collisions);

	if (collision)
	{
		if (player->acc.x < 0.f)
		{
			player->pos.x = (float)(collision->pos.x + collision->size.x) * 12.f - 3.f;
		}
		else if (player->acc.x > 0.f)
		{
			player->pos.x = (float)collision->pos.x * 12.f - 45.f;
		}
	}
}

void Player_ProcessCollisionsY(Player* player, DynamicArray* collisions)
{
	Box* collision = Player_IsColliding(player, collisions);

	if (collision)
	{
		if (player->acc.y < 0.f)
		{
			player->pos.y = (float)(collision->pos.y + collision->size.y) * 12.f - 48.f;
		}
		else if (player->acc.y > 0.f)
		{
			player->pos.y = (float)collision->pos.y * 12.f - 48.f;
		}
	}
}

void Player_Free(Player* player)
{
	free(player);
}
