#pragma once
#include <SDL2/SDL.h>

#include "Math.hpp"

class Entity
{
public:
	Entity(Vector2 pos, SDL_Texture* texture);
	Vector2& getPos()
	{
		return pos;
	}
	SDL_Texture* getTexture();
	SDL_Rect getCurrentFrame();
	void setCurrentFrameX(int x);
	void setCurrentFrameY(int y);
	void setPos(Vector2 newPosition);
	void setX(int newX);
	void setY(int newY);

	void moveRight(int amount);
	void moveLeft(int amount);
	void moveUp(int amount);
	void moveDown(int amount);	
private:
	Vector2 pos;
	float x, y;
	SDL_Rect currentFrame;
	SDL_Texture* texture;
};