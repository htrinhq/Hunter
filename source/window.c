/*
** EPITECH PROJECT, 2017
** window.c
** File description:
** window functions
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

float randomy()
{
	srand(time(NULL));

	int i = rand() % 400;
	return (i);
}

sfRenderWindow *create_window(svt_t *media)
{
	sfVideoMode video_mode = {1200, 760, 32};
	media->window = sfRenderWindow_create(video_mode, "My Hunter", sfDefaultStyle, NULL);
	return (media->window);
}

sfSprite *create_background(svt_t *media)
{
	sfImage *background;
	background = sfImage_createFromFile("source/images/background.png");
	media->texture = sfTexture_createFromImage(background, NULL);
	media->sprite = sfSprite_create();
	sfSprite_setTexture(media->sprite, media->texture, sfTrue);
	return (media->sprite);
}

void move_liferect(math_t *math)
{
	if (((*math).liferect).left == 0 || ((*math).liferect).left == 60)
	 	((*math).liferect).left = ((*math).liferect).left + 60;
}

void move_rect(math_t *math, int max_value)
{
	math->offset = math->offset + 1;
	if (math->offset == 80)
		((*math).rect).left = 110;
	if (math->offset == 160)
	 	((*math).rect).left = 220;
	if (math->offset == max_value) {
		((*math).rect).left = 0;
		math->offset = 0;
	}
}
