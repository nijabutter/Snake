#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
	#include <Windows.h>
#elif __unix__
	#include <unistd.h>
#endif
#include "RenderWindow.hpp"
#include "Entity.hpp"

void pause(double amount)
{
	#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
		Sleep(amount);
	#elif __unix__
		sleep(amount);
	#endif
}

Vector2 getNewFruitPos() {
	return Vector2((rand() % 20) * 16, (rand() % 20) * 16);
}

int main(int argc, char* args[])
{
	std::cout<<"Initializing...";
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cout << "SDL_INIT ERROR: " << SDL_GetError() << std::endl;
		return 1;
	}
	if (!(IMG_Init(IMG_INIT_PNG))) {
		std::cout << "IMG_INIT ERROR: " << SDL_GetError() << std::endl;
		return 1;
	}
	std::cout<<" Done"<<std::endl;

	int score = 2;
	int width = 640;
	int height = 640;
	int moveAmount = 16;
	bool showGrid = true;

	RenderWindow window("Snake", width, height);
	
	SDL_Texture* grassTexture = window.loadTexture("grid.png");
	SDL_Texture* manTexture = window.loadTexture("snake-head.png");
	SDL_Texture* bodyTexture = window.loadTexture("snake-body.png");
	SDL_Texture* fruitTexture = window.loadTexture("fruit.png");

	Entity man = Entity(Vector2(80, 160), manTexture);
	Entity fruit = Entity(Vector2(240, 160), fruitTexture);
	std::vector<Entity> grid;
	std::vector<Entity> snake;

	for (int i = 0; i < score; i++) {
		snake.push_back(Entity(Vector2(64-(i*16), 160), bodyTexture));
	}

	for (int y=0;y<(height/32);y++) {
		for (int x=0;x<(width/32);x++){
			grid.push_back(Entity(Vector2(x*16, y*16), grassTexture));
		}
	}

	// for (int i=0;i<width/16;i++) {
	// 	entities.push_back(Entity(Vector2(i*16, (height/2)-16), grassTexture));
	// }
	bool isRunning = true;
	enum eDirection
	{
		STOP = 0,
		LEFT, RIGHT, UP, DOWN
	};
	eDirection dir = STOP;
	SDL_Event event;
	while (isRunning) {
		
		while (SDL_PollEvent(&event)) {
			switch (event.type)
			{
			case SDL_QUIT:
				isRunning = false;
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.scancode)
				{
					case SDL_SCANCODE_W:
					case SDL_SCANCODE_UP:
						if (dir != DOWN)
							dir = UP;
						break;
					case SDL_SCANCODE_A:
					case SDL_SCANCODE_LEFT:
						if (dir != RIGHT)
							dir = LEFT;
						break;
					case SDL_SCANCODE_S:
					case SDL_SCANCODE_DOWN:
						if (dir != UP)
							dir = DOWN;
						break;
					case SDL_SCANCODE_D:
					case SDL_SCANCODE_RIGHT:
						if (dir != LEFT)
							dir = RIGHT;
						break;
					case SDL_SCANCODE_SPACE:
						showGrid = !showGrid;
					default:
						break;
				}
				break;
			}
		} // end check for event
		Vector2 prevPos = snake[0].getPos();
		Vector2 prevPos2 = Vector2(0, 0);
		snake[0].setPos(man.getPos());
		for (int i = 1; i <= score; i++) {
			prevPos2 = snake[i].getPos();
			snake[i].setPos(prevPos);
			prevPos = prevPos2;
		}

		switch (dir)
		{
			case UP:
			if (man.getPos().y > 0)
				man.moveUp(moveAmount);
			else
				isRunning = false;
			break;
			case DOWN:
			if (man.getPos().y < (height/2)-16)
				man.moveDown(moveAmount);
			else
				isRunning = false;
			break;
			case LEFT:
			if (man.getPos().x > 0)
				man.moveLeft(moveAmount);
			else
				isRunning = false;
			break;
			case RIGHT:
			if (man.getPos().x < (width/2)-16)
				man.moveRight(moveAmount);
			else
				isRunning = false;
			default:
			break;
		}
		
		if (man.getPos().x == fruit.getPos().x && man.getPos().y == fruit.getPos().y) {
			fruit.setPos(getNewFruitPos());
			score++;
			printf("%s\n", "+1");
			snake.push_back(Entity(Vector2(-16, 0), bodyTexture));
		}
		window.clear();
		
		if (showGrid)
			for (Entity& cell : grid)
				window.render(cell);
		
		for (Entity& s : snake) {
			if (s.getPos().x == man.getPos().x && s.getPos().y == man.getPos().y && dir != STOP) {
				printf("%s\n", "Game Over!");
				isRunning = false;
				//gameOver = true;
				break;
			}
			window.render(s);
		}


		

		window.render(man);
		window.render(fruit);
		window.display();
		pause(180);
	} // end is running

	window.cleanUp();
	SDL_Quit();
	return 0;
}

