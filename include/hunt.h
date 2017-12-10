/*
** EPITECH PROJECT, 2017
** hunter.h
** File description:
** hunter.h
*/

#ifndef HUNT_H_
#define  HUNT_H_

struct media {
        sfFont *font;
        sfText *game_over;
        sfText *try_again;
        sfMusic *shoot;
        sfMusic *duck;
        sfMusic *tetris;
        sfTexture *texture;
        sfRenderWindow *window;
        sfSprite *cursor;
        sfSprite *background;
        sfSprite *bird;
        sfSprite *heart;
        sfSprite *sprite;
};

typedef struct media svt_t;

struct math {
        int try;
        int shot;
        int miss;
        int offset;
        float movex;
        float rand_y;
        sfVector2f move;
        sfVector2f mouse;
        sfVector2f origin;
        sfVector2f vectheart;
        sfVector2f middle;
        sfVector2f tryagain;
        sfVector2f position;
	sfIntRect rect;
	sfIntRect liferect;
};

typedef struct math math_t;

float randomy(void);
sfRenderWindow *create_window(svt_t *media);
sfSprite *create_background(svt_t *media);
void move_liferect(math_t *math);
void move_rect(math_t *math, int max_value);
sfSprite *create_bird(svt_t *media);
sfSprite *create_life(svt_t *media);
sfSprite *create_cursor(svt_t *media);
sfSprite *reverse_bird(svt_t *media);
void displayscore(sfRenderWindow *window, sfFont *font);
void destroy(svt_t *media);
void drawsprites(svt_t *media);
void bird_flip(svt_t *media, math_t *math);
void bird_move(svt_t *media, math_t *math);
void new_bird(math_t *math, svt_t *media);
void get_clicked(sfEvent event, svt_t *media, math_t *math);
void in_events(svt_t *media, math_t *math, sfEvent event);
void events(svt_t *media, math_t *math);
void go_event(sfEvent event, svt_t *media, math_t *math);
void overwhile(sfEvent event, svt_t *media, math_t *math);
void overmenu(math_t *math, svt_t *media);
void gomenu(svt_t *media, math_t *math);
void key_pressed(svt_t *media, math_t *math);
void fill_math_2(math_t *math, svt_t *media);
void fill_math(math_t *math);
void fill_media(svt_t *media);
int my_hunter(math_t *math);
void is_miss(math_t *math, svt_t *media);
void set_window(math_t *math, svt_t *media);
void before_while(math_t *math, svt_t *media);

#endif
