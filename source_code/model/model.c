#include "model.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

#define M_PI 3.14159265358979323846

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

	char nbsystem[17] = { 0 };
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
	free(universe->start);
	free(universe->finish);
	free(universe->solar_systems);
	free(universe);
}

Game* Game_New()
{
	Game* self = (Game*)calloc(1, sizeof(Game));
	assert(self);
	self->universe = file("config.txt");
	self->spaceship = Spaceship_New(self->universe->start->pos_x, self->universe->start->pos_y);
	for (int i = 0; i < self->universe->nb_solar_systems; i++)
	{
		for (int j = 0; j < self->universe->solar_systems[i].nb_planets; j++)
		{
			self->universe->solar_systems[i].planets[j].pos_x = self->universe->solar_systems[i].sun.pos_x;
			self->universe->solar_systems[i].planets[j].pos_y = self->universe->solar_systems[i].sun.pos_y - abs(self->universe->solar_systems[i].planets[j].orbit_radius);
		}
	}
	self->state = GAME_IN_PROGRESS;

	return self;
}

void Game_UpdateState(Game* self)
{
	int dx = self->spaceship->pos_x - self->universe->finish->pos_x;
	int dy = self->spaceship->pos_y - self->universe->finish->pos_y;
	int distance = sqrt(pow(dx, 2) + pow(dy, 2));

	if (distance <= 5)
		self->state = GAME_IS_OVER;

	for (int i = 0; i < self->universe->nb_solar_systems; i++)
	{
		if (self->spaceship->pos_x >= self->universe->solar_systems[i].sun.pos_x - self->universe->solar_systems[i].sun.radius
			&& self->spaceship->pos_x <= self->universe->solar_systems[i].sun.pos_x + self->universe->solar_systems[i].sun.radius
			&& self->spaceship->pos_y >= self->universe->solar_systems[i].sun.pos_y - self->universe->solar_systems[i].sun.radius
			&& self->spaceship->pos_y <= self->universe->solar_systems[i].sun.pos_y + self->universe->solar_systems[i].sun.radius)
		{
			self->state = GAME_IS_OVER;
		}

		for (int j = 0; j < self->universe->solar_systems[i].nb_planets; j++)
		{
			if (self->spaceship->pos_x >= self->universe->solar_systems[i].planets[j].pos_x - self->universe->solar_systems[i].planets[j].radius_mass_orbital_period 
				&& self->spaceship->pos_x <= self->universe->solar_systems[i].planets[j].pos_x + self->universe->solar_systems[i].planets[j].radius_mass_orbital_period 
				&& self->spaceship->pos_y >= self->universe->solar_systems[i].planets[j].pos_y - self->universe->solar_systems[i].planets[j].radius_mass_orbital_period 
				&& self->spaceship->pos_y <= self->universe->solar_systems[i].planets[j].pos_y + self->universe->solar_systems[i].planets[j].radius_mass_orbital_period)
			{
				self->state = GAME_IS_OVER;
			}
		}
	}

	if (self->spaceship->pos_x < 0)
	{
		self->spaceship->pos_x = self->universe->win_width;
	}
	if (self->spaceship->pos_x > self->universe->win_width)
	{
		self->spaceship->pos_x = 0;
	}
	if (self->spaceship->pos_y < 0)
	{
		self->spaceship->pos_y = self->universe->win_height;
	}
	if (self->spaceship->pos_y > self->universe->win_height)
	{
		self->spaceship->pos_y = 0;
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

int update_planets(Planet* planet, Star* sun, float delta_time)
{
	if (!planet) return -1;
	int positive = 1;
	float orbital_angular_velocity = 0;

	if (planet->orbit_radius < 0) positive = 0;

	orbital_angular_velocity = 2 * (float)M_PI / planet->radius_mass_orbital_period;

	if (positive == 1) {
		orbital_angular_velocity = -orbital_angular_velocity;
	}

	planet->pos_x = sun->pos_x + abs(planet->orbit_radius) * cos(orbital_angular_velocity * delta_time - (float)M_PI/2);
	planet->pos_y = sun->pos_y + abs(planet->orbit_radius) * sin(orbital_angular_velocity * delta_time - (float)M_PI/2);
	return 0;
}
