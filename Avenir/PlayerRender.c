#include "PlayerRender.h"

void PlayerRender_Draw(Player* player,
	SDL_Renderer* renderer,
	SDL_Texture* sprite,
	Vector cameraPos)
{
	SDL_FRect srcRect = { player->sprite.x, player->sprite.y, 16.f, 16.f };
	SDL_FRect dstRect =
	{
		floorf(player->pos.x) - cameraPos.x,
		floorf(player->pos.y) - cameraPos.y,
		48.f,
		48.f
	};
	SDL_RenderTexture(renderer, sprite, &srcRect, &dstRect);
}
