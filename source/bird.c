/*
** EPITECH PROJECT, 2017
** bird.c
** File description:
** bird
*/

#include <SFML/Graphics.h>
#include <SFML/Config.h>
#include <SFML/Audio.h>
#include <SFML/System.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "hunt.h"

void bird_move(svt_t *media, math_t *math)
{
	if (sfSprite_getPosition(((*media).bird)).x >= 1200) {
		((*math).move).x = -math->movex;
	} else if (sfSprite_getPosition(((*media).bird)).x <= -110)
		((*math).move).x = math->movex;
}

void bird_flip(svt_t *media, math_t *math)
{
	math->position.x = 1200;
	math->position.y = math->rand_y;
	if (sfSprite_getPosition((*media).bird).x >= 1200) {
		media->bird = reverse_bird(media);
		sfSprite_setTextureRect(media->bird, math->rect);
		sfSprite_setPosition(media->bird, math->position);
		sfRenderWindow_drawSprite(media->window, media->bird, NULL);
	} else if (sfSprite_getPosition((*media).bird).x <= -110) {
		media->bird = create_bird(media);
		sfSprite_setTextureRect(media->bird, math->rect);
		sfSprite_setPosition(media->bird, math->origin);
		sfRenderWindow_drawSprite(media->window, media->bird, NULL);
	}
}

void drawsprites(svt_t *media)
{
	sfRenderWindow_drawSprite(media->window, media->background, NULL);
	sfRenderWindow_drawSprite(media->window, media->bird, NULL);
	sfRenderWindow_drawSprite(media->window, media->cursor, NULL);
}


void destroy(svt_t *media)
{
	sfMusic_destroy(media->shoot);
	sfMusic_destroy(media->duck);
	sfMusic_destroy(media->tetris);
	sfSprite_destroy(media->background);
	sfRenderWindow_destroy(media->window);
}

void displayscore(sfRenderWindow *window, sfFont *font)
{
	sfText *tscore;
	sfVector2f bottomleft = {10, 660};

	tscore = sfText_create();
	sfText_setString(tscore, "score ");
	sfText_setFont(tscore, font);
	sfText_setCharacterSize(tscore, 50);
	sfText_setPosition(tscore, bottomleft);
	sfRenderWindow_drawText(window, tscore, NULL);
}
