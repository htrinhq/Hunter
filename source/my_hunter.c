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

void move_liferect(sfIntRect *liferect)
{
	if ((*liferect).left == 0 || (*liferect).left == 60)
	 	(*liferect).left = (*liferect).left + 60;
	//else if ((*liferect).left == 120)
	//	(*liferect).left == 0;
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

sfSprite *create_bird(sfSprite *bird/*, sfIntRect rect*/)
{
	sfImage *pigeon;
	sfTexture *oiseau;

	pigeon = sfImage_createFromFile("spritesheet.png");
	oiseau = sfTexture_createFromImage(pigeon, NULL);
	bird = sfSprite_create();
	sfSprite_setTexture(bird, oiseau, sfTrue);
	return (bird);
}

sfSprite *create_life(sfSprite *heart)
{
	sfImage *Ilife;
	sfTexture *Tlife;

	Ilife = sfImage_createFromFile("life.png");
	Tlife = sfTexture_createFromImage(Ilife, NULL);
	heart = sfSprite_create();
	sfSprite_setTexture(heart, Tlife, sfTrue);
	return (heart);
}

sfSprite *create_cursor(sfSprite *cursor)
{
	sfImage *Icursor;
	sfTexture *Tcursor;

	Icursor = sfImage_createFromFile("cursor.png");
	Tcursor = sfTexture_createFromImage(Icursor, NULL);
	cursor = sfSprite_create();
	sfSprite_setTexture(cursor, Tcursor, sfTrue);
	return (cursor);
}

sfSprite *reverse_bird(sfSprite *bird/*, sfIntRect rect*/)
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

void get_clicked(sfSprite *(*bird),sfVector2f *origin, sfEvent event, float *rand_y, float *movex, sfVector2f *move, sfRenderWindow *window, sfIntRect rect, sfMusic *shoot, sfMusic *duck, sfIntRect *liferect, int *shot, int *miss)
{

	if (event.mouseButton.x >= sfSprite_getPosition(*bird).x &&\
	 event.mouseButton.x <= (sfSprite_getPosition(*bird).x + 110) &&\
	 event.mouseButton.y >= sfSprite_getPosition(*bird).y &&\
	 event.mouseButton.y <= (sfSprite_getPosition(*bird).y + 110)) {
		*shot = *shot + 1;
		sfMusic_play(shoot);
		sfSprite_setPosition(*bird, *origin);
		*rand_y = randomy();
		(*origin).y = *rand_y;
		*movex = *movex + 0.1;
		(*move).x = *movex;
		*bird = create_bird(*bird/*, rect*/);
		sfSprite_setTextureRect(*bird, rect);
		sfRenderWindow_drawSprite(window, *bird, NULL);
		sfSprite_setPosition(*bird, *origin);
		if (*shot == 8 && (*liferect).left != 0) {
			(*liferect).left = (*liferect).left - 60;
			*shot = 0;
			*miss = *miss - 1;
		}
	} else if (!(event.mouseButton.x >= sfSprite_getPosition(*bird).x &&\
	 event.mouseButton.x <= (sfSprite_getPosition(*bird).x + 110) &&\
	 event.mouseButton.y >= sfSprite_getPosition(*bird).y &&\
	 event.mouseButton.y <= (sfSprite_getPosition(*bird).y + 110))) {
		sfMusic_play(duck);
		move_liferect(liferect);
		*shot = 0;
		*miss = *miss + 1;
	}
}


void events(sfRenderWindow *window, sfSprite *(*bird), sfVector2f *origin, float *rand_y, float *movex, sfVector2f *move, sfIntRect rect, sfMusic *shoot, sfMusic *duck, sfIntRect *liferect, int *shot, int *miss)
{
	sfEvent event;

	while (sfRenderWindow_pollEvent(window, &event)) {
		if (event.type == sfEvtClosed)
			sfRenderWindow_close(window);
		if (event.type == sfEvtMouseButtonPressed) {
			if (event.mouseButton.button == sfMouseLeft) {
				get_clicked(bird, origin, event, rand_y, movex, move, window, rect, shoot, duck, liferect, shot, miss);
			}
		}
	}
}

void bird_move(sfSprite *(*bird), sfVector2f *move, float movex)
{
	if (sfSprite_getPosition(*bird).x >= 1200) {
		(*move).x = -movex;
	} else if (sfSprite_getPosition(*bird).x <= -110)
		(*move).x = movex;
}

void bird_flip(sfSprite *(*bird), sfIntRect rect, sfRenderWindow *window, float rand_y, sfVector2f origin)
{
	sfVector2f position = {1200, rand_y};
	if (sfSprite_getPosition(*bird).x >= 1200) {
		*bird = reverse_bird(*bird/*, rect*/);
		sfSprite_setTextureRect(*bird, rect);
		sfSprite_setPosition(*bird, position);
		sfRenderWindow_drawSprite(window, *bird, NULL);
	} else if (sfSprite_getPosition(*bird).x <= -110) {
		*bird = create_bird(*bird/*, rect*/);
		sfSprite_setTextureRect(*bird, rect);
		sfSprite_setPosition(*bird, origin);
		sfRenderWindow_drawSprite(window, *bird, NULL);
	}
}

void drawsprites(sfRenderWindow *window, sfSprite *background, sfSprite *bird, sfSprite *cursor)
{
	sfRenderWindow_drawSprite(window, background, NULL);
	sfRenderWindow_drawSprite(window, bird, NULL);
	sfRenderWindow_drawSprite(window, cursor, NULL);
}


void destroy(sfMusic *shoot, sfMusic *duck, sfMusic *tetris, sfSprite *background, sfRenderWindow *window)
{
	sfMusic_destroy(shoot);
	sfMusic_destroy(duck);
	sfMusic_destroy(tetris);
	sfSprite_destroy(background);
	sfRenderWindow_destroy(window);
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

void overmenu(sfRenderWindow *window/*, sfIntRect rect*/, sfIntRect liferect, sfSprite *heart, sfFont *font, sfSprite *background)
{
	sfEvent event;

	while (sfRenderWindow_pollEvent(window, &event)) {
		if (event.type == sfEvtClosed)
		sfRenderWindow_close(window);
		if (event.type == sfEvtKeyPressed) {
			if (sfKeyboard_isKeyPressed(sfKeyReturn)) {
				sfRenderWindow_drawSprite(window, background, NULL);
				sfRenderWindow_drawSprite(window, heart, NULL);
				sfSprite_setTextureRect(heart, liferect);
				displayscore(window, font);
				sfRenderWindow_display(window);
			}
		}
	}
}

void gomenu(sfRenderWindow *window, int *try, sfFont *font, sfIntRect rect, sfIntRect liferect, sfSprite *heart, sfSprite *background)
{
	sfText *game_over;
	sfText *try_again;
	sfVector2f middle = {340, 250};
	sfVector2f tryagain = {150, 350};
	game_over = sfText_create();
	try_again = sfText_create();

	*try = *try + 1;
	sfText_setString(game_over, "GAME OVER");
	if (*try >= 100)
	sfText_setString(try_again, "Press Enter to Try Again");
	sfText_setFont(game_over, font);
	sfText_setFont(try_again, font);
	sfText_setCharacterSize(game_over, 80);
	sfText_setCharacterSize(try_again, 50);
	sfText_setPosition(game_over, middle);
	sfText_setPosition(try_again, tryagain);
	sfRenderWindow_drawText(window, game_over, NULL);
	sfRenderWindow_drawText(window, try_again, NULL);
	sfRenderWindow_display(window);
	overmenu(window, rect/*, liferect*/, heart, font, background);
}

int my_hunter(sfIntRect rect, sfIntRect liferect)
{
	int try = 0;
	int shot = 0;
	//int scoreit = 0;
	int miss = 0;
	int offset = 0;
	float movex = 0.4;
	float rand_y = randomy();
	sfFont *font = sfFont_createFromFile("game_over.ttf");
	sfVector2f move = {movex, 0};
	sfVector2f mouse;
	sfVector2f origin = {-110, rand_y};
	sfVector2f vectheart = {1100, 670};
	//sfEvent event;
	sfMusic *shoot = sfMusic_createFromFile("Mario-coin-sound.wav");
	sfMusic *duck = sfMusic_createFromFile("duck-quack6.wav");
	sfMusic *tetris = sfMusic_createFromFile("tetris.wav");
	sfTexture *texture;
	sfRenderWindow *window;
	window = create_window(window);
	sfSprite *cursor = create_cursor(cursor);
	sfSprite *background = create_background(background, texture);
	sfSprite *bird = create_bird(bird/*, rect*/);
	sfSprite *heart = create_life(heart);
	sfSprite_setPosition(bird, origin);
	sfSprite_setPosition(heart, vectheart);

	sfMusic_play(tetris);
	sfMusic_setLoop(tetris, 1);
	while (sfRenderWindow_isOpen(window)) {
		mouse.x = sfMouse_getPositionRenderWindow(window).x - 12;
		mouse.y = sfMouse_getPositionRenderWindow(window).y - 12;
		sfRenderWindow_setMouseCursorVisible(window, 0);
		drawsprites(window, background, bird, cursor);
		sfSprite_setPosition(cursor, mouse);
		sfSprite_setTextureRect(bird, rect);
		if (miss <= 2) {
			sfRenderWindow_drawSprite(window, heart, NULL);
			sfSprite_setTextureRect(heart, liferect);
			displayscore(window, font);
			sfRenderWindow_display(window);
		} else {
			sfMusic_stop(tetris);
			gomenu(window, &try, font, rect, liferect, heart, background);
			if (try >= 200)
				try = 0;
		}
		move_rect(&rect, &offset, 240);
		sfSprite_move(bird, move);
		bird_flip(&bird, rect, window, rand_y, origin);
		bird_move(&bird, &move, movex);
		if (miss <= 2)
			events(window, &bird, &origin, &rand_y, &movex, &move, rect, shoot, duck, &liferect, &shot, &miss);
	}
	destroy(shoot, duck, tetris, background, window);
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
