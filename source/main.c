/*
** EPITECH PROJECT, 2017
** main.c
** File description:
** main
*/

#include <SFML/Graphics.h>
#include <SFML/Config.h>
#include <SFML/Audio.h>
#include <SFML/System.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "hunt.h"

int main(void)
{
	math_t *math = malloc(sizeof(math_t));
	
	((*math).rect).top = 0;
	((*math).rect).left = 0;
	((*math).rect).width = 110;
	((*math).rect).height = 110;
	((*math).liferect).top = 0;
	((*math).liferect).left = 0;
	((*math).liferect).width = 60;
	((*math).liferect).height = 60;
	my_hunter(math);
	return (0);
}
