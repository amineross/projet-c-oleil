#include "model.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

Universe* file(char* file_name)
{
	FILE* file = fopen(file_name, "r");
	if (file == NULL)
	{
		printf("Error: file not found\n");
		exit(1);
	}

	Universe* universe = (Universe*)malloc(sizeof(Universe));
	assert(universe);
	universe->start = (Start*)malloc(sizeof(Start));
	assert(universe->start);
	universe->finish = (Finish*)malloc(sizeof(Finish));
	assert(universe->finish);

	char line[9] = { 0 };

	
	(void)fscanf(file, "%s %d %d", line, &universe->win_width, &universe->win_height);
	char line2[6] = { 0 };
	(void)fscanf(file, "%s %d %d", line2, &universe->start->pos_x, &universe->start->pos_y);
	printf("%d %d\n", universe->start->pos_x, universe->start->pos_y);
	if (universe->start->pos_x < 0 || universe->start->pos_x > universe->win_width || universe->start->pos_y < 0 || universe->start->pos_y > universe->win_height)
	{
		printf("Error: fermeture du fichier\n");
		exit(1);
	}
	char line3[4] = { 0 };
	(void)fscanf(file, "%s %d %d", line3, &universe->finish->pos_x, &universe->finish->pos_y);
	printf("%d %d\n", universe->finish->pos_x, universe->finish->pos_y);
	if (universe->finish->pos_x < 0 || universe->finish->pos_x > universe->win_height || universe->finish->pos_y < 0 || universe->finish->pos_y > universe->win_height)
	{
		printf("Error: fermeture du fichier\n");
		exit(1);
	}

	char nbsystem[13] = { 0 };
	(void)fscanf(file, "%s %d", nbsystem, &universe->nb_solar_systems);
	if (universe->nb_solar_systems < 0)
	{
		printf("Error\n");
		exit(1);
	}

	Solar_system* solar_system = (Solar_system*)calloc(universe->nb_solar_systems, sizeof(Solar_system));
	for (int i = 0; i < universe->nb_solar_systems; i++)
	{
		universe->solar_systems = solar_system;
	}
	assert(solar_system);
	char star_pos_s[9] = { 0 };
	char star_radius_s[12] = { 0 };
	char nbplanet_s[10] = { 0 };
	char planetradius_s[14] = { 0 };
	char planetorbit_s[13] = { 0 };

	for (int i = 0; i < universe->nb_solar_systems; i++)
	{
		(void)fscanf(file, "%s %d %d", star_pos_s, &solar_system[i].sun.pos_x, &solar_system[i].sun.pos_y);
		if (solar_system[i].sun.pos_x < 0 || solar_system[i].sun.pos_x > universe->win_width || solar_system[i].sun.pos_y < 0 || solar_system[i].sun.pos_y > universe->win_height)
		{
			printf("Error\n");
			exit(1);
		}
		(void)fscanf(file, "%s %d", star_radius_s, &solar_system[i].sun.radius);
		if (solar_system[i].sun.radius < 0)
		{
			printf("Error\n");
			exit(1);
		}
		(void)fscanf(file, "%s %d", nbplanet_s, &solar_system[i].nb_planets);
		if (solar_system[i].nb_planets < 0)
		{
			printf("Error\n");
			exit(1);
		}
		Planet* planets = (Planet*)calloc(solar_system[i].nb_planets, sizeof(Planet));
		assert(planets);
		for (int j = 0; j < solar_system[i].nb_planets; j++)
		{
			(void)fscanf(file, "%s %d", planetradius_s, &planets[j].radius_mass_orbital_period);
			if (planets[j].radius_mass_orbital_period < 0 || planets[j].radius_mass_orbital_period >= universe->win_width || planets[j].radius_mass_orbital_period >= universe->win_height)
			{
				printf("Error\n");
				exit(1);
			}
			(void)fscanf(file, "%s %d", planetorbit_s, &planets[j].orbit_radius);
			if (planets[j].orbit_radius >= universe->win_width || planets[j].orbit_radius >= universe->win_height)
			{
				printf("Error\n");
				exit(1);
			}
		}
		universe->solar_systems[i].planets = planets;

	}
	
	fclose(file);
	return universe;
}

void free_universe(Universe* universe)
{
	for (int i = 0; i < universe->nb_solar_systems; i++)
	{
		free(universe->solar_systems[i].planets);
	}
	free(universe->solar_systems);
	free(universe);
}

Game* Game_New()
{
	Game* self = (Game*)calloc(1, sizeof(Game));
	assert(self);
	self->universe = file("config.txt");
	self->spaceship = Spaceship_New(self->universe->start->pos_x, self->universe->start->pos_y);
	self->state = GAME_IN_PROGRESS;
	//Input* input = Input_New();
	return self;
}

void Game_UpdateState(Game* self)
{
	if ((self->spaceship->pos_x == self->universe->finish->pos_x) && (self->spaceship->pos_y == self->universe->finish->pos_y))
	{
		self->state = GAME_IS_OVER;
	}
}

Spaceship* Spaceship_New(int pos_x, int pos_y)
{
	Spaceship* self = (Spaceship*)calloc(1, sizeof(Spaceship));
	assert(self);
	self->pos_x = pos_x;
	self->pos_y = pos_y;
	self->velocity = 5;
	return self;
}
