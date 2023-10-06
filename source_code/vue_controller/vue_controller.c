#include <stdio.h>
#include <stdbool.h>
#include "model.h"
#include "vue_controller.h"
#include <SDL.h>
#include "SDL2_gfxPrimitives.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
int          last_frame_time;
float             delta_time;
bool update_planets_start = false;

#define FPS             60
#define FRAME_TIME      (1000 / FPS)

int init_window(Game* game)
{
    window = SDL_CreateWindow(
        "FPS: % d\n",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        game->universe->win_width,
        game->universe->win_height,
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

void setup(Game* game)
{
    game->spaceship->height = 10;
    game->spaceship->width = 10;
    game->spaceship->pos_x = game->universe->start->pos_x;
    game->spaceship->pos_y = game->universe->start->pos_y;
    game->universe->start->width = 10;
    game->universe->start->height = 10;
    game->universe->finish->width = 10;
    game->universe->finish->height = 10;
}

void process_input(Game* game)
{
    SDL_Event e;
    SDL_PollEvent(&e);

    switch (e.type)
    {
    case SDL_QUIT:
        game->state = GAME_IS_OVER;
        break;
    case SDL_KEYDOWN:
        if (e.key.keysym.sym == SDLK_ESCAPE)
            game->state = GAME_IS_OVER;
        if (e.key.keysym.sym == SDLK_d)     // ->
            game->spaceship->pos_x += 5;   //
        if (e.key.keysym.sym == SDLK_q)     // <-
            game->spaceship->pos_x -= 5;   // 
        if (e.key.keysym.sym == SDLK_s)     // DOWN
            game->spaceship->pos_y += 5;   //
        if (e.key.keysym.sym == SDLK_z)     // UP
            game->spaceship->pos_y -= 5;   //
        if (e.key.keysym.sym == SDLK_SPACE) // SPACE
            update_planets_start = true;//
        break;
    }
}

void update(Game* game)
{
    //TODO: CAP FRAME RATE
    last_frame_time = SDL_GetTicks();

    int wait = FRAME_TIME - (SDL_GetTicks() - last_frame_time);

    if (wait > 0 && wait <= FRAME_TIME)
    {
        SDL_Delay(wait);
    }

    delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0;

   if (update_planets_start)
    {
        for (int i = 0; i < game->universe->nb_solar_systems; i++)
        {
            for (int j = 0; j < game->universe->solar_systems[i].nb_planets; j++)
            {
                int period = game->universe->solar_systems[i].planets[j].radius_mass_orbital_period;
                int nb_point_on_cercle = FPS * period;
                time = time + (float)period / nb_point_on_cercle;
                int update = update_planets(&(game->universe->solar_systems[i].planets[j]), &(game->universe->solar_systems[i].sun), time);
            }
        }
    }
}

void render(Game* game)
{   
    // Background : BLACK
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    //Rect start
    rectangleRGBA(renderer, game->universe->start->pos_x, game->universe->start->pos_y, game->universe->start->pos_x + game->universe->start->width, game->universe->start->pos_y + game->universe->start->height, 255, 255, 255, 255);
    //Rect player
    boxRGBA(renderer, game->spaceship->pos_x, game->spaceship->pos_y, game->spaceship->pos_x + game->spaceship->width, game->spaceship->pos_y + game->spaceship->height, 255, 0, 0, 255);
    //Rect finish
    rectangleRGBA(renderer, game->universe->finish->pos_x, game->universe->finish->pos_y, game->universe->finish->pos_x + game->universe->finish->height, game->universe->finish->pos_y + game->universe->finish->width, 255, 255, 255, 255);

    for (int i = 0; i < game->universe->nb_solar_systems; i++)
    {
        filledCircleRGBA(renderer, game->universe->solar_systems[i].sun.pos_x, game->universe->solar_systems[i].sun.pos_y, game->universe->solar_systems[i].sun.radius, 255, 215, 0, 255);
        for (int j = 0; j < game->universe->solar_systems[i].nb_planets; j++)
        {
            filledCircleRGBA(renderer, game->universe->solar_systems[i].planets[j].pos_x, game->universe->solar_systems[i].planets[j].pos_y, game->universe->solar_systems[i].planets[j].radius_mass_orbital_period, 0, 10, 255, 255);
        }
    }
    SDL_RenderPresent(renderer);
}

void destroy_window()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
