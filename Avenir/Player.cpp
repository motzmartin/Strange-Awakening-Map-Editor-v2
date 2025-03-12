#include "Player.h"

void Player::Update(Uint8* keyboard)
{
	if (keyboard[SDL_SCANCODE_LEFT])
	{
		x -= 2;
	}

	if (keyboard[SDL_SCANCODE_UP])
	{
		y -= 2;
	}

	if (keyboard[SDL_SCANCODE_RIGHT])
	{
		x += 2;
	}

	if (keyboard[SDL_SCANCODE_DOWN])
	{
		y += 2;
	}
}

void Player::Draw(SDL_Renderer* renderer)
{
	SDL_Rect rect = { x, y, 16, 16 };
	SDL_FRect rectF;
	SDL_RectToFRect(&rect, &rectF);

	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	SDL_RenderFillRect(renderer, &rectF);
}

int Player::GetY() const
{
	return y;
}
