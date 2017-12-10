/*
** EPITECH PROJECT, 2017
** event.c
** File description:
** event functions
*/

#include <SFML/Graphics.h>
#include <SFML/Config.h>
#include <SFML/Audio.h>
#include <SFML/System.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "hunt.h"

void in_events(svt_t *media, math_t *math, sfEvent event)
{
	if (event.type == sfEvtClosed)
		sfRenderWindow_close(media->window);
	if (event.type == sfEvtMouseButtonPressed) {
		if (event.mouseButton.button == sfMouseLeft) {
			get_clicked(event, media, math);
		}
	}
}

void events(svt_t *media, math_t *math)
{
	sfEvent event;

	while (sfRenderWindow_pollEvent(media->window, &event)) {
		in_events(media, math, event);
	}
}

void new_bird(math_t *math, svt_t *media)
{
	math->shot = math->shot + 1;
	sfMusic_play(media->shoot);
	sfSprite_setPosition(media->bird, math->origin);
	math->rand_y = randomy();
	((*math).origin).y = math->rand_y;
	math->movex = math->movex + 0.1;
	((*math).move).x = math->movex;
	media->bird = create_bird(media);
	sfSprite_setTextureRect(media->bird, math->rect);
	sfRenderWindow_drawSprite(media->window, media->bird, NULL);
	sfSprite_setPosition(media->bird, math->origin);
	if (math->shot == 8 && ((*math).liferect).left != 0) {
		((*math).liferect).left = ((*math).liferect).left - 60;
		math->shot = 0;
		math->miss = math->miss - 1;
	}
}

void get_clicked(sfEvent event, svt_t *media, math_t *math)
{
	if (event.mouseButton.x >= sfSprite_getPosition((*media).bird).x &&\
	 event.mouseButton.x <= (sfSprite_getPosition((*media).bird).x + 110) &&\
	 event.mouseButton.y >= sfSprite_getPosition((*media).bird).y &&\
	 event.mouseButton.y <= (sfSprite_getPosition((*media).bird).y + 110)) {
		new_bird(math, media);
	} else if (!(event.mouseButton.x >= sfSprite_getPosition((*media).bird).x &&\
	 event.mouseButton.x <= (sfSprite_getPosition((*media).bird).x + 110) &&\
	 event.mouseButton.y >= sfSprite_getPosition((*media).bird).y &&\
	 event.mouseButton.y <= (sfSprite_getPosition((*media).bird).y + 110))) {
		sfMusic_play(media->duck);
		move_liferect(math);
		math->shot = 0;
		math->miss = math->miss + 1;
	}
}
