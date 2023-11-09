#include <SDL.h>
#include <cstdio>
#include <iostream>
#include <SDL.h>
#include <cstdio>

//��������� ��������� ������ ����
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
SDL_Renderer* ren=NULL;
SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;

void DeInit(int error)
{
	if (ren != 0) SDL_DestroyRenderer(ren);
	if (window != 0) SDL_DestroyWindow(window);
	SDL_Quit();
	exit(error);
}

void Init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL �� ���� �����������! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		
		window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN
			| SDL_WINDOW_RESIZABLE);
		if (window == NULL)
		{
			printf("���� �� ����� ���� �������! SDL_Error: %s\n", SDL_GetError());
			DeInit(1);
			system("pause");
			
		}
		else
		{
			/*//�������� �����������
			screenSurface = SDL_GetWindowSurface(window);

			//��������� �� ����� ������
			SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0x19, 0xb2, 0xFF));

			//��������� �����������
			SDL_UpdateWindowSurface(window);*/

			//���� ��� �������
			ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (!ren)
			{
				printf("Renderer ������! SDL_Error: %s\n", SDL_GetError());
				DeInit(1);
				system("pause");
			}
			
		}
	}
}

int main(int argc, char* args[])
{
	Init();
	SDL_SetRenderDrawColor(ren, 255, 185, 232, 255);
	SDL_RenderClear(ren);
	
	SDL_Delay(5000);
	DeInit(0);

	return 0;
}