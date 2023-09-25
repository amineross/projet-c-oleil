#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "../model/model.h"

#define true            1
#define false           0
#define SCREEN_WIDTH    1080
#define SCREEN_HEIGHT   720
#define FPS             60
#define FRAME_TIME      (1000 / FPS)


SDL_Window*           window = NULL;
SDL_Renderer*       renderer = NULL;
int               is_running = false;
Spaceship                 sp;
int          last_frame_time;
float             delta_time;


int init_window()
{

    window = SDL_CreateWindow(
                "Hello World!",
                SDL_WINDOWPOS_CENTERED,
                SDL_WINDOWPOS_CENTERED,
                SCREEN_WIDTH,
                SCREEN_HEIGHT,
                SDL_WINDOW_SHOWN);
    
    if (!window)
    {
        printf("Window creation failed\n");
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer)
    {
        printf("Renderer creation failed\n");
        return false;
    }

    return true;
}

void setup()
{
    sp.height = 10;
    sp.width = 10;
    sp.pos_x = SCREEN_WIDTH / 2;
    sp.pos_y = SCREEN_HEIGHT / 2;
}

void process_input()
{
    SDL_Event e;
    SDL_PollEvent(&e);

    switch (e.type)
    {
    case SDL_QUIT:
        is_running = false;
        break;
    case SDL_KEYDOWN:
        if (e.key.keysym.sym == SDLK_ESCAPE)
            is_running = false;
        if (e.key.keysym.sym == SDLK_d)     // ->
            sp.pos_x += (1 * delta_time);   //
        if (e.key.keysym.sym == SDLK_q)     // <-
            sp.pos_x -= (1 * delta_time);   // 
        if (e.key.keysym.sym == SDLK_s)     // DOWN
            sp.pos_y += (1 * delta_time);   //
        if (e.key.keysym.sym == SDLK_z)     // UP
            sp.pos_y -= (1 * delta_time);   //
            
        break;
    }
}

void update()
{
    // TODO: CAP FRAME RATE
    // last_frame_time = SDL_GetTicks();

    // int wait = FRAME_TIME - (SDL_GetTicks() - last_frame_time);

    // if (wait > 0 && wait <= FRAME_TIME)
    // {
    //     SDL_Delay(wait);
    // }

    delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0;
 
}

void render()
{
    // Background : BLACK
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Player : RED
    SDL_Rect player = {
        sp.pos_x,
        sp.pos_y,
        sp.width,
        sp.height
    };
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &player);

    filledCircleColor(renderer, 150, 40, 30, 0xFFFF0000);


    SDL_RenderPresent(renderer);
}


int main()
{
    SDL_Init(SDL_INIT_VIDEO);

    init_window();
    

    is_running = true;


    setup();

    while (is_running == true)
    {
        process_input();
        update();
        render();
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    return 0;  
}
