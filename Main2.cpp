#include <SDL.h>
#include <iostream>

using namespace std;

int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480;

enum KeyPress
{
    
    KEY_PRESS_UP,
    KEY_PRESS_DOWN,
    KEY_PRESS_LEFT,
    KEY_PRESS_RIGHT
    
};


static SDL_Window* win = NULL;
static SDL_Renderer* ren = NULL;
static SDL_Surface * screenSurtface = NULL;

bool init() {
    bool ok = true;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        cout << "Can't init SDL: " << SDL_GetError() << endl;
    }

    win = SDL_CreateWindow("Snake", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (win == NULL) {
        cout << "Can't create window: " << SDL_GetError() << endl;
        ok = false;
    }

    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    if (ren == NULL) {
        cout << "Can't create renderer: " << SDL_GetError() << endl;
        ok = false;
    }
    return ok;
}
void quit() 
{
    if (win)
    {
        SDL_DestroyWindow(win);
        win = NULL;
    }

    
    if (ren)
    {
        SDL_DestroyRenderer(ren);
        ren = NULL;
    }

    SDL_Quit();
}


int main(int arhc, char** argv)
{
    if (!init())
    {
        quit();
        system("pause");
        return 1;
    }
    bool ex = false;
    // SDL_Color col = {0xBE, 0xBE, 0xBE};
     //SDL_SetRenderDrawColor(ren, 0xBE, 0xBE, 0xBE, 0x00);
     //SDL_RenderClear(ren);
    screenSurtface = SDL_LoadBMP("Fon.bmp");

    SDL_Event e;
    SDL_SetRenderDrawColor(ren, 0xA9, 0x00, 0xA9, 0xA9);

    SDL_Rect rect1 = { 0, 0, SCREEN_HEIGHT / 10, SCREEN_HEIGHT / 10 };
    SDL_RenderDrawRect(ren, &rect1);

    SDL_Rect rect2 = { 5, 5, SCREEN_HEIGHT / 10 - 10, SCREEN_HEIGHT / 10 - 10 };
    SDL_RenderFillRect(ren, &rect2);

    SDL_RenderDrawLine(ren, 10, 70, 640 - 10, 70);

    for (int i = 10; i <= 640 - 10; i += 4) {
        SDL_RenderDrawPoint(ren, i, 90);
    }

    SDL_RenderPresent(ren);

    SDL_Delay(5000);
    while (ex)
    {
        //Handle events on queue
        while (SDL_PollEvent(&e) != 0)
        {
            //User requests quit
            if (e.type == SDL_QUIT)
            {
                ex = true;
            }
            //User presses a key
            else if (e.type == SDL_KEYDOWN)
            {
                //Select surfaces based on key press
             /*  switch (e.key.keysym.sym)
                {
                case SDLK_UP:
                    gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
                    break;

                case SDLK_DOWN:
                    gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
                    break;

                case SDLK_LEFT:
                    gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
                    break;

                case SDLK_RIGHT:
                    gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
                    break;

                default:
                    gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
                    break;
                }*/
            }
        }

        quit();
        return 0;
    }
}