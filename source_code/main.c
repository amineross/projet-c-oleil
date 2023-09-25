#include <stdio.h>
#include <stdbool.h>
#include "model.h"
#include "SDL.h"
#include "SDL2_gfxPrimitives.h"

#define FPS             60
#define FRAME_TIME      (1000 / FPS)

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
int          last_frame_time;
float             delta_time;
int init_window(Game* game)
{

    window = SDL_CreateWindow(
        "Hello World!",
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
            game->spaceship->pos_x += (1 * delta_time);   //
        if (e.key.keysym.sym == SDLK_q)     // <-
            game->spaceship->pos_x -= (1 * delta_time);   // 
        if (e.key.keysym.sym == SDLK_s)     // DOWN
            game->spaceship->pos_y += (1 * delta_time);   //
        if (e.key.keysym.sym == SDLK_z)     // UP
            game->spaceship->pos_y -= (1 * delta_time);   //

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

void render(Game* game)
{
    // Background : BLACK
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Player : RED
    SDL_Rect player = {
        game->spaceship->pos_x,
        game->spaceship->pos_y,
        game->spaceship->width,
        game->spaceship->height
    };
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &player);

    for (int i = 0; i < game->universe->nb_solar_systems; i++)
    {
        filledCircleRGBA(renderer, game->universe->solar_systems[i].sun.pos_x, game->universe->solar_systems[i].sun.pos_y, game->universe->solar_systems[i].sun.radius, 255, 215, 0, 255);
        for (int j = 0; j < game->universe->solar_systems[i].nb_planets; j++)
        {
            filledCircleRGBA(renderer, game->universe->solar_systems[i].sun.pos_x, game->universe->solar_systems[i].sun.pos_y - (game->universe->solar_systems[i].sun.radius + 50), game->universe->solar_systems[i].planets[j].radius_mass_orbital_period, 0, 10, 255, 255);
        }
    }
    //filledCircleColor(renderer, game., 40, 30, 0xFFFF0000);


    SDL_RenderPresent(renderer);
}

int main(int argc, char* argv[])
{
   // SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Hello World", "yay", NULL);
	Game* game = Game_New();

	while (Game_GetState(game) == GAME_IN_PROGRESS)
	{
        SDL_Init(SDL_INIT_VIDEO);
        init_window(game);
        setup(game);

        process_input(game);
        update();
        render(game);
        printf("%d %d\n", game->spaceship->pos_x, game->spaceship->pos_y);
        Game_UpdateState(game);
        
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);
        SDL_Quit();
	}
    return 0;
}
