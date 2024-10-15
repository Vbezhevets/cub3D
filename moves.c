#include "cub3d.h"

void    move_forward(t_scene *scene, double	angle, int x_dir, int y_dir)
{
	scene->p->x += fabs(cos(angle)) * STEP * x_dir;
	scene->p->y += fabs(sin(angle)) * STEP * y_dir;
}

void    move_back(t_scene *scene, double angle, int x_dir, int y_dir)
{
	scene->p->x -= fabs(cos(angle)) * STEP * x_dir;
	scene->p->y -= fabs(sin(angle)) * STEP * y_dir;
}

void    move_left(t_scene *scene, double angle)
{
	int	reverse;

	if ((scene->p->angle + PI / 2) > 2 * PI)
	{
		angle =  scene->p->angle - PI / 2;
		reverse = -1;
	}
	else 
	{
		reverse = 1;
		angle = scene->p->angle + PI / 2 ;
	}

	move_forward(scene, angle,  get_x_dir(angle) * reverse,  get_y_dir(angle) * reverse);
}


void    move_right(t_scene *scene, double angle)
{
	int	reverse;

	if ((scene->p->angle + PI / 2) > 2 * PI)
	{
		angle =  scene->p->angle - PI / 2;
		reverse = -1;
	}
	else 
	{
		reverse = 1;
		angle = scene->p->angle + PI / 2 ;
	}
	move_back(scene, angle, get_x_dir(angle) * reverse,  get_y_dir(angle)  * reverse);
}

void    turn_left(t_scene *scene)
{
	scene->p->angle =  scene->p->angle + PI / 20; // radians
	scene->p->angle = update_ang(scene->p->angle);
}

void    turn_right(t_scene *scene)
{
	scene->p->angle = scene->p->angle - PI / 20;
	scene->p->angle = update_ang(scene->p->angle);
}