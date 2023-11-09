
#include "SDL.h"
#include<iostream>
#include "Snake.h"


using namespace std;
#pragma region GLOBAL_VARIABLE
SDL_Color fieldColor{ 0x80, 0xff, 0x66, 0xaa };
SDL_Color snakeColor{ 0xcc, 0x00, 0x00, 0xff };
SDL_Color targetColor{ 0x11, 0x05, 0xfe, 0xff };
const int SCREEN_WIDTH = 720;
const int SCREEN_HEIGHT = 720;
SDL_Window* window = NULL;
SDL_Renderer* render = NULL;
SDL_Texture* tex = NULL;
const int N=16, M=16;
int delay=300;

#pragma endregion 

#pragma region FUNCTION_AND_STRUCTURES
bool Init()
{
	
	window = SDL_CreateWindow("Snake",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		cout << "create window error\n";
		return false;
	}
	render = SDL_CreateRenderer(window, -1, 0);
	if (render == NULL)
	{
		cout << "create render error\n";
		return false;
	}
	return true;
}

bool Load_Background()
{
	SDL_Surface* fon = NULL;
	fon = SDL_LoadBMP("fon.bmp");
	if (fon == NULL)
	{
		cout << "load bmp error\n";
		return false;
	}
	tex = SDL_CreateTextureFromSurface(render, fon);
	SDL_FreeSurface(fon);
	if (tex == NULL)
	{
		cout << "create surface tex error\n";
		return false;
	}
	return true;
}

bool drawField( int ** field)
{
	SDL_RenderCopy(render, tex, NULL, NULL);
	SDL_SetRenderDrawBlendMode(render, SDL_BLENDMODE_BLEND);
	int rectDim = SCREEN_HEIGHT / 17;
	for (unsigned i{0}; i < N; ++i)
	{
		for (unsigned j{0}; j < M; ++j)
		{
			switch (field[i][j])
			{
			case 0:
				SDL_SetRenderDrawColor(render, fieldColor.r, fieldColor.g, fieldColor.b, fieldColor.a);
				break;
			case 1:
				SDL_SetRenderDrawColor(render, snakeColor.r, snakeColor.g, snakeColor.b, snakeColor.a);
				break;
			case 2:
				SDL_SetRenderDrawColor(render, targetColor.r, targetColor.g, targetColor.b, targetColor.a);
				break;

			}
				
			SDL_Rect rect2 = { i * rectDim+28, j * rectDim+28, rectDim - 4, rectDim - 4 };
			SDL_RenderFillRect(render, &rect2);
		}
	}
	

	

	

	SDL_RenderPresent(render);
	
	return true;
}

void Quit()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(render);
	SDL_DestroyTexture(tex);
	SDL_Quit();
}
#pragma endregion

int main(int argc, char* args[])
{
	Snake snake(N, M);
	Direction dir = UP;
	if (Init())
	{
		

		SDL_Event e;		
		bool quit = false;
		srand(time(0));
		while (!quit)
		{   
			drawField(snake.getField());
			SDL_Delay(snake.delay);
			
			while (SDL_PollEvent(&e))
			{
				if (e.type == SDL_QUIT)
				{
					quit = true;
				}
				if (e.type == SDL_KEYDOWN)
				{
					if (e.type == SDL_KEYDOWN)
					{
						if (e.key.keysym.sym == SDLK_UP) {
							dir = UP;
						}
						if (e.key.keysym.sym == SDLK_DOWN) {
							dir = DOWN;
						}
						if (e.key.keysym.sym == SDLK_RIGHT) {
							dir = RIGHT;
						}
						if (e.key.keysym.sym == SDLK_LEFT) {
							dir = LEFT;
						}
					}
				}
				
			}
			snake.move(dir);
			SDL_RenderPresent(render);
		}
		
		Quit();
	}
	
	return 0;
}