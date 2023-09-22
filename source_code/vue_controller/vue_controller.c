#include <stdio.h>
#include <SDL2/SDL.h>
#include "SDL2/SDL2_gfxPrimitives.h"
#include <stdbool.h>

#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 720

SDL_Window* g_window = NULL;
SDL_Renderer* g_renderer = NULL;

bool init()
{
    bool success = true;

    if ( SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Init failed: %s\n", SDL_GetError());
        success = false;
    } else 
    {
        g_window = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

        if (g_window == NULL)
        {
            printf("Window create failed: %s\n", SDL_GetError());
            success = false;
        } else 
        {
            g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (g_renderer == NULL)
            {
                SDL_DestroyWindow(g_window);
                printf("Renderer init failed %s\n", SDL_GetError());
                success = false;
            }
        }
    }
    return success;
}

bool load_media()
{
    bool success = true;
    
    // g_hello_world = SDL_LoadBMP("cat.bmp");
    // if (g_hello_world == NULL)
    // {
    //     printf("Image load failed: %s", SDL_GetError());
    //     success = false;
    // }
    return success;
}

void close()
{
    SDL_DestroyWindow(g_window);
    g_window = NULL;

    SDL_DestroyRenderer(g_renderer);
    g_renderer = NULL;

    SDL_Quit();
}

int main(int argc, char* args[])
{
    if (!init())
    {
        printf("Init failed\n");
    } else 
    {
        SDL_SetRenderDrawColor(g_renderer, 0, 0, 0xFF, 0xFF);
        SDL_RenderClear(g_renderer);

        thickLineColor(g_renderer, 540, 360, 30, 78, 77, 0xFF00FF00);

        SDL_RenderPresent(g_renderer);
    }
    close();
    return 0;
}

