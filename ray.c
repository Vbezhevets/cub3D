#include <math.h>
#include <stdio.h>
#include "cub3d.h"



int init_player(t_scene *scene, char direct, int y,  int x)
{
	t_player	*p;

	p = malloc(sizeof(t_player));
	if (!p)
		return (1);// 
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
	t_player	*p;

	p = scene->p;
 	ray->next_vert_x = (int)((from_x / SEGM) + p->x_dir) * SEGM;
	dist_to_next_vert_x = fabs(from_x - ray->next_vert_x);
	update_dir(scene, p);
	dist_to_next_vert_intersect = fabs(dist_to_next_vert_x / cos(p->angle));
	ray->next_vert_y = (int)(dist_to_next_vert_intersect * fabs(sin(p->angle)) * p->y_dir + (from_y));

	return (dist_to_next_vert_intersect);
}



int find_next_hor(t_scene *scene, t_ray *ray, int from_x, int from_y)
{
	double		dist_to_next_hor_intersect;
	int			dist_to_next_hor_y;
	t_player	*p;

	p = scene->p;
	ray->next_hor_y = ((int)(from_y / SEGM + p->y_dir)) * SEGM;
	dist_to_next_hor_y = fabs(from_y - ray->next_hor_y);
	update_dir(scene, p);
	dist_to_next_hor_intersect = fabs(dist_to_next_hor_y / cos(p->angle + PI / 2));
	ray->next_hor_x = (int)(dist_to_next_hor_intersect * sin(p->angle + PI / 2) + (from_x));

	return (dist_to_next_hor_intersect);
} 

t_ray	*ray_init(t_scene *scene, t_ray *ray, t_player *p)
{
	ray = malloc(sizeof(t_ray));

	ray->next_hor_x = p->x;
	ray->next_hor_y = p->y;
	ray->next_vert_x = p->x;
	ray->next_vert_y = p->y;
	if (p->y_dir == -1)
		p->y_dir = 0;
	ray->vert_dist = find_next_vert(scene, ray, p->x, p->y);
	if (p->y_dir == -1)
		p->y_dir = 0;
	ray->hor_dist = find_next_hor(scene, ray, p->x, p->y);
	return(ray);
}
void calc_ray(t_scene *scene)
{
	t_player	*p;
	t_ray		*ray;

	p = scene->p;
	update_dir(scene, p);

	ray = ray_init(scene, ray, p);
	if (ray)
		scene->ray = ray;

	while (is_inside_map(scene, ray->next_vert_x, ray->next_vert_y) &&
		not_wall(scene, ray->next_vert_x, ray->next_vert_y))
				ray->vert_dist += find_next_vert(scene, ray, ray->next_vert_x, ray->next_vert_y);
			// draww_point(scene, ray->next_vert_y, ray->next_vert_x, 0x00FF00FF);

	while (is_inside_map(scene, ray->next_hor_x, ray->next_hor_y) &&
		not_wall_hor(scene, ray->next_hor_x, ray->next_hor_y))
		// {
			ray->hor_dist += find_next_hor(scene, ray, ray->next_hor_x, ray->next_hor_y);
			// draww_point(scene, ray->next_hor_y, ray->next_hor_x, 0x000000FF);
		// }

	if (fabs(ray->vert_dist) < fabs(ray->hor_dist))
		draww_point(scene, ray->next_vert_y, ray->next_vert_x, 0x00FF00FF);
	else
		draww_point(scene, ray->next_hor_y, ray->next_hor_x, 0x000000FF);
}

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
