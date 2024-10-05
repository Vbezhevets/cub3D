#include "cub3d.h"

void    move_forward(t_scene *scene)
{
	printf("forward\n");
}
void    move_back(t_scene *scene)
{
	printf("back\n");
}

void    move_left(t_scene *scene)
{
	printf("left\n");
}

void    move_right(t_scene *scene)
{
	printf("right\n");
}

void    turn_left(t_scene *scene)
{
	scene->p->angle =  scene->p->angle - PI / 10;
}

void    turn_right(t_scene *scene)
{
	scene->p->angle =  scene->p->angle + PI / 10;
}