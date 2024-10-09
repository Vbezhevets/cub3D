#include "cub3d.h"

void    move_forward(t_scene *scene, double	angle)
{
	scene->p->x += fabs(cos(angle)) * STEP * scene->p->x_dir;
	scene->p->y += fabs(sin(angle)) * STEP * scene->p->y_dir;
}
void    move_back(t_scene *scene, double angle)
{
	scene->p->x -= fabs(cos(angle)) * STEP * scene->p->x_dir;
	scene->p->y -= fabs(sin(angle)) * STEP * scene->p->y_dir;
}

void    move_left(t_scene *scene, double angle)
{
		angle = scene->p->angle -  PI / 2;
	// angle = fmod(scene->p->angle, PI / 2);
	scene->p->x -= fabs(cos(angle)) * STEP;
	scene->p->y -= fabs(sin(angle)) * STEP;
}

void    move_right(t_scene *scene, double angle)
{
	angle = scene->p->angle -  PI / 2;
	// angle = fmod(scene->p->angle, PI / 2);
	scene->p->x += fabs(cos(angle)) * STEP ;
	scene->p->y += fabs(sin(angle)) * STEP ;
}

void    turn_left(t_scene *scene)
{
	scene->p->angle =  scene->p->angle + PI / 10; // radians
}

void    turn_right(t_scene *scene)
{
	scene->p->angle =  scene->p->angle - PI / 10;
}