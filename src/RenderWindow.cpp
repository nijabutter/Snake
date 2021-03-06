#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "RenderWindow.hpp"
#include "Entity.hpp"
RenderWindow::RenderWindow(const char* title, int w, int h)
	:window(NULL), renderer(NULL)

{
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);

	if (!window) {
		std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;
		return;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	
}

SDL_Texture* RenderWindow::loadTexture(const char* filePath)
{
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(renderer, filePath);

	if (!texture) {
		std::cout << "Failed to load texture (" << filePath << ") Error: " << SDL_GetError() << std::endl;
		return NULL;
	}
	return texture;
}

void RenderWindow::cleanUp()
{
	SDL_DestroyWindow(window);
}

void RenderWindow::clear()
{
	SDL_RenderClear(renderer);
}

void RenderWindow::render(Entity& entity)
{
	SDL_Rect src;
	src.x = entity.getCurrentFrame().x;
	src.y = entity.getCurrentFrame().y;
	src.w = entity.getCurrentFrame().w;
	src.h = entity.getCurrentFrame().h;

	SDL_Rect dst;
	dst.x = entity.getPos().x * 2;
	dst.y = entity.getPos().y * 2;
	dst.w = entity.getCurrentFrame().w * 2;
	dst.h = entity.getCurrentFrame().h * 2;
	SDL_RenderCopy(renderer, entity.getTexture(), &src, &dst);	
}

void RenderWindow::display()
{
	SDL_RenderPresent(renderer);
}