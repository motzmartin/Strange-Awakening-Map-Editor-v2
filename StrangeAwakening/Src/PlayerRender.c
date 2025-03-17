#include "PlayerRender.h"

void PlayerRender_Draw(Player* player,
	SDL_Renderer* renderer,
	SDL_Texture* sprite,
	Vector cameraCentered)
{
	IntegerRender_DrawTexture(renderer,
		sprite,
		Vector_Scale(player->sprite, 16),
		Vector_New(16, 16),
		Vector_Sub(VectorConversion_FromVectorF(player->pos), cameraCentered),
		Vector_New(48, 48));
}
