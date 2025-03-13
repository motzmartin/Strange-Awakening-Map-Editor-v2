#include "PlayerRender.h"

void PlayerRender_Draw(Player* player, SDL_Renderer* renderer)
{
	SDL_FRect rect = { player->pos.x, player->pos.y, 16.f, 16.f };
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	SDL_RenderRect(renderer, &rect);
}
