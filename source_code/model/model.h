#include <stdlib.h>
#include <stdio.h>
#include <math.h>


typedef struct Spaceship 
{
    int pos_x, pos_y;
    int height, width;
    float speed; // {2; 8}
    float velocity; // {1/2 init speed; 2x init speed}
} Spaceship;

typedef struct Planet 
{
    int pos_x, pos_y;
    int radius;
    int orbit;
    int mass;
    int orbit_duration;
} Planet;

typedef struct Star 
{
    int pos_x, pos_y;
    int radius;
} Star;

typedef struct SolarSystem 
{
    int NB_PLANET;
    Star sun;
    Planet * planets;
} SolarSystem;

typedef struct Entry 
{
    int pos_x, pos_y;
    int height, width;
} Entry;

typedef struct Universe 
{
    int win_height, win_width;
    Entry start, end;
    int nb_solar_system;
    SolarSystem* solar_systems;
} Universe;




