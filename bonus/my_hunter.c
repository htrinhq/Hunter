/*
** EPITECH PROJECT, 2017
** my_hunter.c
** File description:
** Duck Hunt
*/

#include <SFML/Graphics.h>
#include <SFML/Config.h>
#include <SFML/System/InputStream.h>
#include <SFML/System/Vector2.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

float randomy()
{
	srand(time(NULL));

	int i = rand() % 400;
	return (i);
}

sfRenderWindow *create_window(sfRenderWindow *window)
{
	sfVideoMode video_mode = {1200, 760, 32};
	window = sfRenderWindow_create(video_mode, "My Hunter", sfDefaultStyle, NULL);
	return (window);
}

sfSprite *create_background(sfSprite *sprite, sfTexture *texture)
{
	sfImage *background;
	background = sfImage_createFromFile("background.png");
	texture = sfTexture_createFromImage(background, NULL);
	sprite = sfSprite_create();
	sfSprite_setTexture(sprite, texture, sfTrue);
	return (sprite);
}

void move_rect(sfIntRect *rect, int *offset, int max_value)
{
	*offset = *offset + 1;
	if (*offset == 80)
		(*rect).left = 110;
	if (*offset == 160)
	 	(*rect).left = 220;
	if (*offset == max_value) {
		(*rect).left = 0;
		*offset = 0;
	}
}

sfSprite *create_bird(sfSprite *bird, sfIntRect rect)
{
	sfImage *pigeon;
	sfTexture *oiseau;

	pigeon = sfImage_createFromFile("spritesheet.png");
	oiseau = sfTexture_createFromImage(pigeon, NULL);
	bird = sfSprite_create();
	sfSprite_setTexture(bird, oiseau, sfTrue);
	return (bird);
}

sfSprite *reverse_bird(sfSprite *bird, sfIntRect rect)
{
	sfImage *pigeon;
	sfTexture *oiseau;

	pigeon = sfImage_createFromFile("spritesheet.png");
	sfImage_flipHorizontally(pigeon);
	oiseau = sfTexture_createFromImage(pigeon, NULL);
	bird = sfSprite_create();
	sfSprite_setTexture(bird, oiseau, sfTrue);
	return (bird);
}

void get_clicked(sfSprite *(*bird),sfVector2f *origin, sfEvent event, float *rand_y, float *movex, sfVector2f *move)
{
	if (event.mouseButton.x >= sfSprite_getPosition(*bird).x && event.mouseButton.x <= (sfSprite_getPosition(*bird).x + 110) &&
event.mouseButton.y >= sfSprite_getPosition(*bird).y && event.mouseButton.y <= (sfSprite_getPosition(*bird).y + 110)) {
		sfSprite_setPosition(*bird, *origin);
		*rand_y = randomy();
		(*origin).y = *rand_y;
		*movex = *movex + 0.1;
		(*move).x = *movex;
	}
}

void events(sfRenderWindow *window, sfSprite *(*bird), sfVector2f *origin, float *rand_y, float *movex, sfVector2f *move)
{
	sfEvent event;

	while (sfRenderWindow_pollEvent(window, &event)) {
		if (event.type == sfEvtClosed)
			sfRenderWindow_close(window);
		if (event.type == sfEvtMouseButtonPressed) {
			if (event.mouseButton.button == sfMouseLeft) {
				get_clicked(bird, origin, event, rand_y, movex, move);
			}
		}
	}
}

void bird_move(sfSprite *(*bird), sfVector2f *move, float movex)
{
	if (sfSprite_getPosition(*bird).x >= 1090) {
		(*move).x = -movex;
	} else if (sfSprite_getPosition(*bird).x <= 0)
		(*move).x = movex;
}

void bird_flip(sfSprite *(*bird), sfIntRect rect, sfRenderWindow *window, float rand_y, sfVector2f origin)
{
	sfVector2f position = {1090, rand_y};
	if (sfSprite_getPosition(*bird).x >= 1090) {
		*bird = reverse_bird(*bird, rect);
		sfSprite_setTextureRect(*bird, rect);
		sfRenderWindow_drawSprite(window, *bird, NULL);
		sfSprite_setPosition(*bird, position);
	} else if (sfSprite_getPosition(*bird).x <= 0) {
		*bird = create_bird(*bird, rect);
		sfSprite_setTextureRect(*bird, rect);
		sfRenderWindow_drawSprite(window, *bird, NULL);
		sfSprite_setPosition(*bird, origin);
	}
}


int my_hunter(sfIntRect rect)
{
	float rand_y = randomy();
	sfVector2f origin = {0, rand_y};
	sfEvent event;
	sfTexture *texture;
	float movex = 0.4;
	sfVector2f move = {movex, 0};
	sfRenderWindow *window;
	window = create_window(window);
	sfSprite *background;
	sfSprite *bird = create_bird(bird, rect);
	sfSprite_setPosition(bird, origin);
	background = create_background(background, texture);
	int offset = 0;

	while (sfRenderWindow_isOpen(window)) {
		sfRenderWindow_display(window);
		sfRenderWindow_drawSprite(window, background, NULL);
		sfRenderWindow_drawSprite(window, bird, NULL);
		sfSprite_setTextureRect(bird, rect);
		move_rect(&rect, &offset, 240);
		sfSprite_move(bird, move);
		bird_flip(&bird, rect, window, rand_y, origin);
		bird_move(&bird, &move, movex);
		events(window, &bird, &origin, &rand_y, &movex, &move);
	}
	sfSprite_destroy(background);
	//sfTexture_destroy(texture);
	sfRenderWindow_destroy(window);
	return (0);
}

int main(void)
{
	sfIntRect rect;

	rect.top = 0;
	rect.left = 0;
	rect.width = 110;
	rect.height = 110;

	my_hunter(rect);
	return (0);
}
