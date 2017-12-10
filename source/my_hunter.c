/*
** EPITECH PROJECT, 2017
** my_hunter.c
** File description:
** Duck Hunt
*/

#include <SFML/Graphics.h>
#include <SFML/Config.h>
#include <SFML/Audio.h>
#include <SFML/System.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "hunt.h"

void before_while(math_t *math, svt_t *media)
{
	fill_math(math);
	fill_media(media);
	sfSprite_setPosition(media->bird, math->origin);
	sfSprite_setPosition(media->heart, math->vectheart);
	sfMusic_play(media->tetris);
	sfMusic_setLoop(media->tetris, 1);
}

void set_window(math_t *math, svt_t *media)
{
	math->mouse.x = sfMouse_getPositionRenderWindow(media->window).x - 12;
	math->mouse.y = sfMouse_getPositionRenderWindow(media->window).y - 12;
	sfRenderWindow_setMouseCursorVisible(media->window, 0);
	drawsprites(media);
	sfSprite_setPosition(media->cursor, math->mouse);
	sfSprite_setTextureRect(media->bird, math->rect);
}

void is_miss(math_t *math, svt_t *media)
{
	if (math->miss <= 2) {
		sfRenderWindow_drawSprite(media->window, media->heart, NULL);
		sfSprite_setTextureRect(media->heart, math->liferect);
		displayscore(media->window, media->font);
		sfRenderWindow_display(media->window);
	} else {
		sfMusic_stop(media->tetris);
		gomenu(media, math);
		if (math->try >= 200)
		math->try = 0;
	}
}

int my_hunter(math_t *math)
{
	svt_t *media = malloc(sizeof(svt_t));

	before_while(math, media);
	while (sfRenderWindow_isOpen(media->window)) {
		set_window(math, media);
		is_miss(math, media);
		move_rect(math, 240);
		sfSprite_move(media->bird, math->move);
		bird_flip(media, math);
		bird_move(media, math);
		if (math->miss <= 2)
			events(media, math);
	}
	destroy(media);
	free(math);
	free(media);
	return (0);
}
