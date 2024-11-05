#include <math.h>
#include <stdio.h>
#include "cub3d.h"



int init_player(t_scene *scene, char direct, int y,  int x)
{
	t_player	*p;

	p = malloc(sizeof(t_player));
	if (!p)
		return (1);
	p->y = y * SEGM + SEGM / 2;
    p->x = x * SEGM + SEGM / 2;
	if (direct == 'N')
		p->angle = PI / 2;
	if (direct == 'E')
		p->angle = 0;
	if (direct == 'W')
		p->angle = PI;
	if (direct == 'S')
		p->angle = PI * 1.5;
	scene->p = p;
	return (0);
}

int find_next_vert(t_scene *scene, t_ray *ray, int from_x, int from_y)
{
	double		dist_to_next_vert_intersect;
	int			dist_to_next_vert_x;

 	ray->next_vert_x = (int)((from_x / SEGM) + ray->x_dir) * SEGM;
	dist_to_next_vert_x = fabs(from_x - ray->next_vert_x);
	update_dir(scene, ray);
	dist_to_next_vert_intersect = fabs(dist_to_next_vert_x / cos(ray->angle));
	ray->next_vert_y = (int)(dist_to_next_vert_intersect * fabs(sin(ray->angle)) * ray->y_dir + (from_y));

	return (dist_to_next_vert_intersect);
}

int find_next_hor(t_scene *scene, t_ray *ray, int from_x, int from_y)
{
	double		dist_to_next_hor_intersect;
	int			dist_to_next_hor_y;

	ray->next_hor_y = ((int)(from_y / SEGM + ray->y_dir)) * SEGM;
	dist_to_next_hor_y = fabs(from_y - ray->next_hor_y);
	update_dir(scene, ray);
	dist_to_next_hor_intersect = fabs(dist_to_next_hor_y / cos(ray->angle + PI / 2));
	ray->next_hor_x = (int)(dist_to_next_hor_intersect * sin(ray->angle + PI / 2) + (from_x));

	return (dist_to_next_hor_intersect);
}

t_ray	*ray_init(t_scene *scene, t_ray *ray, double angle)
{
	ray = malloc(sizeof(t_ray));
	// if 
	ray->angle = angle;
	update_dir(scene, ray);

	if (ray->y_dir == -1)
		ray->y_dir = 0;

	ray->vert_dist = find_next_vert(scene, ray, scene->p->x, scene->p->y);
	if (ray->y_dir == -1)
		ray->y_dir = 0;
	ray->hor_dist = find_next_hor(scene, ray, scene->p->x, scene->p->y);
	return(ray);
}

void calc_ray(t_scene *scene, int i, double angle)
{
	t_player	*p;
	t_ray		*ray;

	ray = ray_init(scene, ray, angle);
	if (ray)
		scene->ray[i] = ray;
	// else //
	draww_point(scene, ray->next_vert_y, ray->next_vert_x, 0x00FF00FF);
	draww_point(scene, ray->next_hor_y, ray->next_hor_x, 0x000000FF);

	while (is_inside_map(scene, ray->next_vert_x, ray->next_vert_y) &&
		not_wall_vert(scene, ray->next_vert_x, ray->next_vert_y, ray))
		{
			ray->vert_dist += find_next_vert(scene, ray, ray->next_vert_x, ray->next_vert_y);
			draww_point(scene, ray->next_vert_y, ray->next_vert_x, 0x00FF00FF);
		}
	while (is_inside_map(scene, ray->next_hor_x, ray->next_hor_y) &&
		not_wall_hor(scene, ray->next_hor_x, ray->next_hor_y, ray))
		{
			ray->hor_dist += find_next_hor(scene, ray, ray->next_hor_x, ray->next_hor_y);
			draww_point(scene, ray->next_hor_y, ray->next_hor_x, 0x000000FF);
		}

	if (fabs(ray->vert_dist) < fabs(ray->hor_dist))
		{
			draww_point(scene, ray->next_vert_y, ray->next_vert_x, 0x00FF00FF);
			ray->dist = ray->vert_dist;
		}
	else
		{
			draww_point(scene, ray->next_hor_y, ray->next_hor_x, 0x000000FF);
			ray->dist = ray->hor_dist;
		}
}

void	calc_rays(t_scene *scene)
{
	int		i;
	double	angle;

	i = WIDTH - 1;
	angle = scene->p->angle -  FOV / 2;
	while (i >= 0)
	{
		angle = update_ang(angle);
		calc_ray(scene, i, angle );
		angle +=  FOV / WIDTH;
		i--;
	}
}
/*
void calc_ray(t_scene *scene, int i, double angle)
{
	t_player	*p;
	t_ray		*ray;

	ray = ray_init(scene, ray, angle);
	if (ray)
		scene->ray[i] = ray;
	// else //

	while (is_inside_map(scene, ray->next_vert_x, ray->next_vert_y) &&
		not_wall(scene, ray->next_vert_x, ray->next_vert_y, ray))
			ray->vert_dist += find_next_vert(scene, ray, ray->next_vert_x, ray->next_vert_y);
	while (is_inside_map(scene, ray->next_hor_x, ray->next_hor_y) &&
		not_wall_hor(scene, ray->next_hor_x, ray->next_hor_y, ray))
			ray->hor_dist += find_next_hor(scene, ray, ray->next_hor_x, ray->next_hor_y);

	if (fabs(ray->vert_dist) < fabs(ray->hor_dist))
			ray->dist = ray->vert_dist;
	else
			ray->dist = ray->hor_dist;
}
 */
// cos(angle) = (v_x - p->x) / V 

// v_x - p->x = V * cos(angle);
// v_x =  V * cos(angle) + p->x;

// y :
// sin(angle) = (v_y - p->y ) / V

// v_y - p->y = V * sin(angle)
// v_y = V * sin(angle) + p_y
// */


// /*
// dif_y = |p->y - v_y|
// dif_x = |p->x - v_x|
// */
