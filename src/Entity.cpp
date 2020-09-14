#include <SDL2/SDL.h>
#include "Entity.hpp"

Entity::Entity(Vector2 pos, SDL_Texture* texture)
:pos(pos), texture(texture)
{
	currentFrame.x = 0.0;
	currentFrame.y = 0.0;
	currentFrame.w = 16.0;
	currentFrame.h = 16.0;
}

SDL_Texture* Entity::getTexture()
{
	return texture;
}

SDL_Rect Entity::getCurrentFrame()
{
	return currentFrame;
}

void Entity::setCurrentFrameX(int x)
{
	currentFrame.x = x;
}

void Entity::setCurrentFrameY(int y)
{
	currentFrame.y = y;
}

void Entity::setPos(Vector2 newPosition)
{
	pos = newPosition;
}

void Entity::setX(int newX)
{
	pos.x = newX;
}

void Entity::setY(int newY)
{
	pos.y = newY;
}

void Entity::moveRight(int amount)
{
	pos.x += amount;
}

void Entity::moveLeft(int amount)
{
	pos.x -= amount;
}

void Entity::moveUp(int amount)
{
	pos.y -= amount;
}

void Entity::moveDown(int amount)
{
	pos.y += amount;
}