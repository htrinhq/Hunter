/*
** EPITECH PROJECT, 2017
** game_over.c
** File description:
** game over functions
*/

#include <SFML/Graphics.h>
#include <SFML/Config.h>
#include <SFML/Audio.h>
#include <SFML/System.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "hunt.h"

void key_pressed(svt_t *media, math_t *math)
{
	if (sfKeyboard_isKeyPressed(sfKeyReturn)) {
		sfRenderWindow_drawSprite(media->window, media->background, NULL);
		sfRenderWindow_drawSprite(media->window, media->heart, NULL);
		sfSprite_setTextureRect(media->heart, math->liferect);
		displayscore(media->window, media->font);
		sfRenderWindow_display(media->window);
	}
}

void go_event(sfEvent event, svt_t *media, math_t *math)
{
	sfRenderWindow_close(media->window);
	if (event.type == sfEvtKeyPressed) {
		key_pressed(media, math);
	}
}

void overwhile(sfEvent event, svt_t *media, math_t *math)
{
	if (event.type == sfEvtClosed)
		sfRenderWindow_close(media->window);
	if (event.mouseButton.x >= sfSprite_getPosition((*media).bird).x &&\
	event.mouseButton.x <= (sfSprite_getPosition((*media).bird).x + 110) &&\
	event.mouseButton.y >= sfSprite_getPosition((*media).bird).y &&\
	event.mouseButton.y <= (sfSprite_getPosition((*media).bird).y + 110)) {
		go_event(event, media, math);
	}
}

void overmenu(math_t *math, svt_t *media)
{
	sfEvent event;

	while (sfRenderWindow_pollEvent(media->window, &event)) {
		overwhile(event, media, math);
	}
}

void gomenu(svt_t *media, math_t *math)
{
	fill_math_2(math, media);
	sfText_setString(media->game_over, "GAME OVER");
	if (math->try >= 100)
		sfText_setString(media->try_again, "Press Enter to try Again");
	sfText_setFont(media->game_over, media->font);
	sfText_setFont(media->try_again, media->font);
	sfText_setCharacterSize(media->game_over, 80);
	sfText_setCharacterSize(media->try_again, 50);
	sfText_setPosition(media->game_over, math->middle);
	sfText_setPosition(media->try_again, math->tryagain);
	sfRenderWindow_drawText(media->window, media->game_over, NULL);
	sfRenderWindow_drawText(media->window, media->try_again, NULL);
	sfRenderWindow_display(media->window);
	overmenu(math, media);
}
