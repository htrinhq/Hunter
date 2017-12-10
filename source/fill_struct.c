/*
** EPITECH PROJECT, 2017
** fill_struct.c
** File description:
** fill struct functions
*/

#include <SFML/Graphics.h>
#include <SFML/Config.h>
#include <SFML/Audio.h>
#include <SFML/System.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "hunt.h"

void fill_math_2(math_t *math, svt_t *media)
{
	math->middle.x = 340;
	math->middle.y = 250;
	math->tryagain.x = 350;
	math->tryagain.y = 350;
	media->game_over = sfText_create();
	media->try_again = sfText_create();
	math->try = math->try + 1;
}

void fill_math(math_t *math)
{
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
}

void fill_media(svt_t *media)
{
	media->font = sfFont_createFromFile("source/police/game_over.ttf");
	media->shoot = sfMusic_createFromFile("source/sounds/Mario-coin-sound.wav");
	media->duck = sfMusic_createFromFile("source/sounds/duck-quack6.wav");
	media->tetris = sfMusic_createFromFile("source/sounds/tetris.wav");
	media->window = create_window(media);
	media->cursor = create_cursor(media);
	media->background = create_background(media);
	media->bird = create_bird(media);
	media->heart = create_life(media);
}
