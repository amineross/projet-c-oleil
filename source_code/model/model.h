#pragma once
#ifdef _WIN32
#  define INLINE inline
#else
#  define INLINE static inline
#endif

typedef struct {
    /* XY coordinates */
    int pos_x, pos_y;
    /* the radius of the planet =
    = its mass = its orbital period */
    int radius_mass_orbital_period;
    /* the orbit of the planet*/
    int orbit_radius;
}Planet;

typedef struct {
    /* XY coordinates */
    int pos_x, pos_y;
    /* the radius of the star */
    int radius;
}Star;

typedef struct {
    /* the center of the solar system*/
    Star sun;
    /* the total number of planets in the solar system */
    int nb_planets;
    /* the planets register */
    Planet* planets;
}Solar_system;

typedef struct {
    /* XY coordinates */
    int pos_x, pos_y;
    /* default dimensions of the spaceship */
    int height, width;
    /* the velocity of the spaceship */
    int velocity;
}Spaceship;

typedef struct {
    /* XY coordinates */
    int pos_x, pos_y;
    /* default dimensions*/
    int height, width;

}Start;

typedef struct {
    /* XY coordinates */
    int pos_x, pos_y;
    /* default dimensions*/
    int height, width;

}Finish;

typedef struct {
    /* the total number of solar systems in the universe */
    int nb_solar_systems;
    /* the solar systems register */
    Solar_system* solar_systems;
    Start* start;
    Finish* finish;
    int win_height, win_width;
}Universe;

typedef struct Game_s
{
    Universe* universe;
    Spaceship* spaceship;
    /// @brief Etat de la partie.
    /// Les valeurs possibles sont définies dans GameState.
    int state;
} Game;

typedef enum GameState_e
{
    /// @brief Indique que la partie est en cours.
    GAME_IN_PROGRESS,
    /// @brief Indique que la partie s'est terminée.
    GAME_IS_OVER
} GameState;

Universe* file(char* file_name);
void free_universe(Universe* universe);
Game* Game_New();
void Game_UpdateState(Game* self);
Spaceship* Spaceship_New(int pos_x, int pos_y);
int update_planets(Planet* planet, Star* sun, int height, float delta_time);

INLINE int Game_GetState(Game* self)
{
    return self->state;
}
