#include "Player.h"

void Player::Update(Uint8* keyboard)
{
	if (keyboard[SDL_SCANCODE_LEFT])
	{
		pos.x -= 1.f;
	}

	if (keyboard[SDL_SCANCODE_UP])
	{
		pos.y -= 1.f;
	}

	if (keyboard[SDL_SCANCODE_RIGHT])
	{
		pos.x += 1.f;
	}

	if (keyboard[SDL_SCANCODE_DOWN])
	{
		pos.y += 1.f;
	}
}

void Player::Draw(SDL_Renderer* renderer)
{
	SDL_FRect rect = { pos.x, pos.y, 16.f, 16.f };
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	SDL_RenderRect(renderer, &rect);
}

float Player::GetY() const
{
	return pos.y;
}
