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
};

typedef struct math math_t;

float randomy(void);
sfRenderWindow *create_window(svt_t *media);
sfSprite *create_background(svt_t *media);
void move_liferect(sfIntRect *liferect);
void move_rect(sfIntRect *rect, math_t *math, int max_value);
sfSprite *create_bird(svt_t *media);
sfSprite *create_life(svt_t *media);
sfSprite *create_cursor(svt_t *media);
sfSprite *reverse_bird(svt_t *media);

#endif
