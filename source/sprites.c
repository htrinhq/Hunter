/*
** EPITECH PROJECT, 2017
** sprites.c
** File description:
** sprite creation functions
*/

#include <SFML/Graphics.h>
#include <SFML/Config.h>
#include <SFML/Audio.h>
#include <SFML/System.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include "hunt.h"

sfSprite *create_bird(svt_t *media)
{
	sfImage *pigeon;
	sfTexture *oiseau;

	pigeon = sfImage_createFromFile("source/images/spritesheet.png");
	oiseau = sfTexture_createFromImage(pigeon, NULL);
	media->bird = sfSprite_create();
	sfSprite_setTexture(media->bird, oiseau, sfTrue);
	return (media->bird);
}

sfSprite *create_life(svt_t *media)
{
	sfImage *Ilife;
	sfTexture *Tlife;

	Ilife = sfImage_createFromFile("source/images/life.png");
	Tlife = sfTexture_createFromImage(Ilife, NULL);
	media->heart = sfSprite_create();
	sfSprite_setTexture(media->heart, Tlife, sfTrue);
	return (media->heart);
}

sfSprite *create_cursor(svt_t *media)
{
	sfImage *Icursor;
	sfTexture *Tcursor;

	Icursor = sfImage_createFromFile("source/images/cursor.png");
	Tcursor = sfTexture_createFromImage(Icursor, NULL);
	media->cursor = sfSprite_create();
	sfSprite_setTexture(media->cursor, Tcursor, sfTrue);
	return (media->cursor);
}

sfSprite *reverse_bird(svt_t *media)
{
	sfImage *pigeon;
	sfTexture *oiseau;

	pigeon = sfImage_createFromFile("source/images/spritesheet.png");
	sfImage_flipHorizontally(pigeon);
	oiseau = sfTexture_createFromImage(pigeon, NULL);
	media->bird = sfSprite_create();
	sfSprite_setTexture(media->bird, oiseau, sfTrue);
	return (media->bird);
}
