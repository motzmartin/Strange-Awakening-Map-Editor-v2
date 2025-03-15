#include "Player.h"

Player* Player_Create()
{
	Player* player = calloc(1, sizeof(Player));
	if (!player) return NULL;

	return player;
}

void Player_Update(Player* player,
	Uint64 elapsed,
	Uint8* keyboard,
	Box** collisions,
	int collisionsCursor)
{
	player->count += elapsed;

	player->acc = VectorF_New(0.f, 0.f);

	if (keyboard[SDL_SCANCODE_A] != keyboard[SDL_SCANCODE_D])
	{
		player->acc.x = keyboard[SDL_SCANCODE_A] ? -1.f : 1.f;
	}

	if (keyboard[SDL_SCANCODE_W] != keyboard[SDL_SCANCODE_S])
	{
		player->acc.y = keyboard[SDL_SCANCODE_W] ? -1.f : 1.f;
	}

	player->acc = VectorF_Scale(VectorF_Normalize(player->acc), elapsed * 1.5e-7f);

	VectorF prevPos = player->pos;

	player->pos.x += player->acc.x;
	Player_ProcessCollisionsX(player, collisions, collisionsCursor);

	player->pos.y += player->acc.y;
	Player_ProcessCollisionsY(player, collisions, collisionsCursor);

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

Box* Player_IsColliding(Player* player, Box** collisions, int collisionsCursor)
{
	for (int i = 0; i < collisionsCursor; i++)
	{
		Box* collision = collisions[i];

		if (player->pos.x > (float)collision->pos.x * 12.f - 48.f &&
			player->pos.x < (float)(collision->pos.x + collision->size.x) * 12.f &&
			player->pos.y > (float)collision->pos.y * 12.f - 48.f &&
			player->pos.y < (float)(collision->pos.y + collision->size.y) * 12.f - 36.f)
		{
			return collision;
		}
	}

	return NULL;
}

void Player_ProcessCollisionsX(Player* player, Box** collisions, int collisionsCursor)
{
	Box* collision = Player_IsColliding(player, collisions, collisionsCursor);

	if (collision)
	{
		if (player->acc.x < 0.f)
		{
			player->pos.x = (float)(collision->pos.x + collision->size.x) * 12.f;
		}
		else if (player->acc.x > 0.f)
		{
			player->pos.x = (float)collision->pos.x * 12.f - 48.f;
		}
	}
}

void Player_ProcessCollisionsY(Player* player, Box** collisions, int collisionsCursor)
{
	Box* collision = Player_IsColliding(player, collisions, collisionsCursor);

	if (collision)
	{
		if (player->acc.y < 0.f)
		{
			player->pos.y = (float)(collision->pos.y + collision->size.y) * 12.f - 36.f;
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
