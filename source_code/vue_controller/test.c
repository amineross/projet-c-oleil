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
#define NB_SOLAR_SYSTEM 4


SDL_Window*           window = NULL;
SDL_Renderer*       renderer = NULL;
int               is_running = false;
int          last_frame_time;
float             delta_time;
Universe            universe;
Entry                  start;
Entry                    end;
Spaceship                 sp;



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
    last_frame_time = SDL_GetTicks();


    // Universe
    universe.win_width = 1080;
    universe.win_height = 720;
    start.pos_x = 400;
    start.pos_y = 600;
    end.pos_x = 600;
    end.pos_y = 300;
    end.width = 10;
    end.height = 10;
    universe.start = start;
    universe.end = end;
    universe.nb_solar_system = NB_SOLAR_SYSTEM;
    

    // SolarSystems
    universe.solar_systems = malloc(universe.nb_solar_system*sizeof(SolarSystem));
    for (int i = 0; i<universe.nb_solar_system; i++)
    {
        int nb_planets = 2;
        Star sun;
        Planet* planets = malloc(nb_planets*sizeof(Planet));
    }

    // Spaceship
    sp.height = 10;
    sp.width = 10;
    sp.pos_x = start.pos_x;
    sp.pos_y = start.pos_y;
    sp.velocity = 100;

    // Suns of each solar system
    int x = 100;
    int y = 100;
    for (int i = 0; i<universe.nb_solar_system; i++)
    {
        Star s;
        s.pos_x = x;
        s.pos_y = y;
        s.radius = 30;
        printf("SUN: %d %d %d\n", s.pos_x, s.pos_y, s.radius);
        universe.solar_systems[i].sun = s;

        x += 100;
        y += 100;
    }
    
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
            sp.pos_x += (20 * delta_time * sp.velocity);   //
        if (e.key.keysym.sym == SDLK_q)     // <-
            sp.pos_x -= (20 * delta_time * sp.velocity);   // 
        if (e.key.keysym.sym == SDLK_s)     // DOWN
            sp.pos_y += (20 * delta_time * sp.velocity);   //
        if (e.key.keysym.sym == SDLK_z)     // UP
            sp.pos_y -= (20 * delta_time * sp.velocity);   //
            
        break;
    }
}

void update()
{
    // TODO: CAP FRAME RATE
    

    // int wait = FRAME_TIME - (SDL_GetTicks() - last_frame_time);

    // if (wait > 0 && wait <= FRAME_TIME)
    // {
    //     SDL_Delay(wait);
    // }
    Uint32 current_time = SDL_GetTicks();
    delta_time = (current_time - last_frame_time) / 1000.0f;

    last_frame_time = current_time;

    printf("%f %d\n", delta_time, last_frame_time);
 
}

void render()
{
    // Background : BLACK
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Player : RED
    SDL_Rect spaceship_rect = {
        sp.pos_x,
        sp.pos_y,
        sp.width,
        sp.height
    };
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &spaceship_rect);

    // End
    SDL_Rect end_rect = {
        end.pos_x,
        end.pos_y,
        end.width,
        end.height
    };

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &end_rect);

    // Sun
    for (int i = 0; i<universe.nb_solar_system; i++)
    {
        // printf("%d %d %d\n", star_arr[i].pos_x, star_arr[i].pos_y, star_arr[i].radius);
        filledCircleRGBA(renderer, universe.solar_systems[i].sun.pos_x, universe.solar_systems[i].sun.pos_y, universe.solar_systems[i].sun.radius, 255, 255, 0, 255);
    }
    


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
