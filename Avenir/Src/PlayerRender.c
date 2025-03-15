#include "PlayerRender.h"

void PlayerRender_Draw(Player* player,
	SDL_Renderer* renderer,
	SDL_Texture* sprite,
	Vector cameraCentered)
{
	SDL_Rect srcRect = { player->sprite.x * 16, player->sprite.y * 16, 16, 16 };
	SDL_Rect dstRect =
	{
		(int)floorf(player->pos.x) - cameraCentered.x,
		(int)floorf(player->pos.y) - cameraCentered.y,
		48,
		48
	};
	IntegerRender_DrawSprite(renderer, sprite, srcRect, dstRect);
}
