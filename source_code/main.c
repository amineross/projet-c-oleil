#include <stdio.h>
#include <stdbool.h>
#include "model.h"
#include "SDL.h"
#include "SDL2_gfxPrimitives.h"
#include "vue_controller.h"
#include <time.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    int start = 0;
    int x = 0;
    srand(time(NULL));
    x = rand () % 2;
	Game* game = Game_New();
    SDL_Init(SDL_INIT_VIDEO);
    init_window(game);
    setup(game);
    bool random_spaceship_initialized = false;
    while (Game_GetState(game) == GAME_IN_PROGRESS)
    {
        process_input(game);
        update(game);
        render(game);
        Game_UpdateState(game);
        if (game->update_planets_start && !random_spaceship_initialized)
        {
            random_spaceship_angle(game->spaceship);
            random_spaceship_initialized = true;
        }
        if (game->update_planets_start)
        {
            if (x == 0)
            {
                game->spaceship->pos_x += game->spaceship->velocity * cos(game->spaceship->angle);
                game->spaceship->pos_y -= game->spaceship->velocity * sin(game->spaceship->angle);
            }
            else
            {
                game->spaceship->pos_x -= game->spaceship->velocity * cos(game->spaceship->angle);
                game->spaceship->pos_y -= game->spaceship->velocity * sin(game->spaceship->angle);
            }
           
        }
    }
    free_universe(game->universe);
    destroy_window();
    return 0;
}
