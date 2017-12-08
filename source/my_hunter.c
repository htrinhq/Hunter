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

void get_clicked(sfEvent event, sfIntRect rect, sfIntRect *liferect, svt_t *media, math_t *math)
{

	if (event.mouseButton.x >= sfSprite_getPosition((*media).bird).x &&\
	 event.mouseButton.x <= (sfSprite_getPosition((*media).bird).x + 110) &&\
	 event.mouseButton.y >= sfSprite_getPosition((*media).bird).y &&\
	 event.mouseButton.y <= (sfSprite_getPosition((*media).bird).y + 110)) {
		math->shot = math->shot + 1;
		sfMusic_play(media->shoot);
		sfSprite_setPosition(media->bird, math->origin);
		math->rand_y = randomy();
		((*math).origin).y = math->rand_y;
		math->movex = math->movex + 0.1;
		((*math).move).x = math->movex;
		media->bird = create_bird(media);
		sfSprite_setTextureRect(media->bird, rect);
		sfRenderWindow_drawSprite(media->window, media->bird, NULL);
		sfSprite_setPosition(media->bird, math->origin);
		if (math->shot == 8 && (*liferect).left != 0) {
			(*liferect).left = (*liferect).left - 60;
			math->shot = 0;
			math->miss = math->miss - 1;
		}
	} else if (!(event.mouseButton.x >= sfSprite_getPosition((*media).bird).x &&\
	 event.mouseButton.x <= (sfSprite_getPosition((*media).bird).x + 110) &&\
	 event.mouseButton.y >= sfSprite_getPosition((*media).bird).y &&\
	 event.mouseButton.y <= (sfSprite_getPosition((*media).bird).y + 110))) {
		sfMusic_play(media->duck);
		move_liferect(liferect);
		math->shot = 0;
		math->miss = math->miss + 1;
	}
}

void events(sfIntRect rect, sfIntRect *liferect, svt_t *media, math_t *math)
{
	sfEvent event;

	while (sfRenderWindow_pollEvent(media->window, &event)) {
		if (event.type == sfEvtClosed)
			sfRenderWindow_close(media->window);
		if (event.type == sfEvtMouseButtonPressed) {
			if (event.mouseButton.button == sfMouseLeft) {
				get_clicked(event, rect, liferect, media, math);
			}
		}
	}
}

void bird_move(svt_t *media, math_t *math)
{
	if (sfSprite_getPosition(((*media).bird)).x >= 1200) {
		((*math).move).x = -math->movex;
	} else if (sfSprite_getPosition(((*media).bird)).x <= -110)
		((*math).move).x = math->movex;
}

void bird_flip(sfIntRect rect, svt_t *media, math_t *math)
{
	math->position.x = 1200;
	math->position.y = math->rand_y;
	if (sfSprite_getPosition((*media).bird).x >= 1200) {
		media->bird = reverse_bird(media);
		sfSprite_setTextureRect(media->bird, rect);
		sfSprite_setPosition(media->bird, math->position);
		sfRenderWindow_drawSprite(media->window, media->bird, NULL);
	} else if (sfSprite_getPosition((*media).bird).x <= -110) {
		media->bird = create_bird(media);
		sfSprite_setTextureRect(media->bird, rect);
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

void overmenu(sfIntRect liferect, svt_t *media)
{
	sfEvent event;

	while (sfRenderWindow_pollEvent(media->window, &event)) {
		if (event.type == sfEvtClosed)if (event.mouseButton.x >= sfSprite_getPosition((*media).bird).x &&\
	 	event.mouseButton.x <= (sfSprite_getPosition((*media).bird).x + 110) &&\
	 	event.mouseButton.y >= sfSprite_getPosition((*media).bird).y &&\
	 	event.mouseButton.y <= (sfSprite_getPosition((*media).bird).y + 110)) {
			sfRenderWindow_close(media->window);
			if (event.type == sfEvtKeyPressed) {
				if (sfKeyboard_isKeyPressed(sfKeyReturn)) {
					sfRenderWindow_drawSprite(media->window, media->background, NULL);
					sfRenderWindow_drawSprite(media->window, media->heart, NULL);
					sfSprite_setTextureRect(media->heart, liferect);
					displayscore(media->window, media->font);
					sfRenderWindow_display(media->window);
				}
			}
		}
	}
}

void gomenu(sfIntRect rect, svt_t *media, math_t *math)
{
	//media->game_over;
	//media->try_again;
	math->middle.x = 340;
	math->middle.y = 250;
	math->tryagain.x = 350;
	math->tryagain.y = 350;
	media->game_over = sfText_create();
	media->try_again = sfText_create();
	math->try = math->try + 1;
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
	overmenu(rect, media);
}

int my_hunter(sfIntRect rect, sfIntRect liferect)
{
	svt_t *media = malloc(sizeof(svt_t));
	math_t *math = malloc(sizeof(math_t));
	math->try = 0;
	math->shot = 0;
	math->miss = 0;
	math->offset = 0;
	math->movex = 0.4;
	math->rand_y = randomy();
	math->move.x = math->movex;
	math->move.y = 0;
	math->origin.x = -110;
	math->origin.y = math->rand_y;
	math->vectheart.x = 1100;
	math->vectheart.y = 670;
	media->font = sfFont_createFromFile("source/police/game_over.ttf");
	media->shoot = sfMusic_createFromFile("source/sounds/Mario-coin-sound.wav");
	media->duck = sfMusic_createFromFile("source/sounds/duck-quack6.wav");
	media->tetris = sfMusic_createFromFile("source/sounds/tetris.wav");
	media->window = create_window(media);
	media->cursor = create_cursor(media);
	media->background = create_background(media);
	media->bird = create_bird(media);
	media->heart = create_life(media);
	sfSprite_setPosition(media->bird, math->origin);
	sfSprite_setPosition(media->heart, math->vectheart);

	sfMusic_play(media->tetris);
	sfMusic_setLoop(media->tetris, 1);
	while (sfRenderWindow_isOpen(media->window)) {
		math->mouse.x = sfMouse_getPositionRenderWindow(media->window).x - 12;
		math->mouse.y = sfMouse_getPositionRenderWindow(media->window).y - 12;
		sfRenderWindow_setMouseCursorVisible(media->window, 0);
		drawsprites(media);
		sfSprite_setPosition(media->cursor, math->mouse);
		sfSprite_setTextureRect(media->bird, rect);
		if (math->miss <= 2) {
			sfRenderWindow_drawSprite(media->window, media->heart, NULL);
			sfSprite_setTextureRect(media->heart, liferect);
			displayscore(media->window, media->font);
			sfRenderWindow_display(media->window);
		} else {
			sfMusic_stop(media->tetris);
			gomenu(rect, media, math);
			if (math->try >= 200)
				math->try = 0;
		}
		move_rect(&rect, math, 240);
		sfSprite_move(media->bird, math->move);
		bird_flip(rect, media, math);
		bird_move(media, math);
		if (math->miss <= 2)
			events(rect, &liferect, media, math);
	}
	destroy(media);
	free(math);
	free(media);
	return (0);
}

int main(void)
{
	sfIntRect rect;
	rect.top = 0;
	rect.left = 0;
	rect.width = 110;
	rect.height = 110;

	sfIntRect liferect;
	liferect.top = 0;
	liferect.left = 0;
	liferect.width = 60;
	liferect.height = 60;

	my_hunter(rect, liferect);
	return (0);
}
