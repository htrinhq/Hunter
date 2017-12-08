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

void move_liferect(sfIntRect *liferect)
{
	if ((*liferect).left == 0 || (*liferect).left == 60)
	 	(*liferect).left = (*liferect).left + 60;
	//else if ((*liferect).left == 120)
	//	(*liferect).left == 0;
}

void move_rect(sfIntRect *rect, math_t *math, int max_value)
{
	math->offset = math->offset + 1;
	if (math->offset == 80)
		(*rect).left = 110;
	if (math->offset == 160)
	 	(*rect).left = 220;
	if (math->offset == max_value) {
		(*rect).left = 0;
		math->offset = 0;
	}
}
