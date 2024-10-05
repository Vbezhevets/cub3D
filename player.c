#include <math.h>
#include <stdio.h>
#include "cub3d.h"

double update_dir(t_scene *scene, t_player *p)
{

	if (p->angle > 0 && p->angle <= PI / 2) //↗️
	{
		p->y_dir = 0;
		p->x_dir = 1;
		return (p->angle);
	}
	if (p->angle > PI /2 && p->angle < PI) // ↖️
	{
		p->y_dir = 0;
		p->x_dir = 0;
		return (PI - p->angle);
	}
	if (p->angle >= PI && p->angle < PI * 1.5)// ↙️
	{
		p->y_dir = 1;
		p->x_dir = 0;
		return (p->angle - PI);
	}
	if (p->angle >= PI * 1.5 && p->angle <= PI * 2)// ↘️
	{
		p->y_dir = 1;
		p->x_dir = 1;
		return(2 * PI - p->angle);
	}
	if (p->angle == 0)
	{
		p->y_dir = 1;
		p->x_dir = 1;
	}

	if (p->angle > PI * 2)
		p->angle = p->angle - PI * 2;
	
	if (p->angle < PI * 2)
		p->angle = p->angle + PI * 2;
	// if (p->angle < 0)
	// 	return(-p->angle);

}

void draww_point(t_scene *scene, int y, int  x)
{
	if (x >= 0 && x < SEGM * scene->map_width && y >= 0 && y < SEGM * scene->map_height)
	{
	mlx_put_pixel(scene->map_img, y, x, PLAYERC, scene);
	mlx_put_pixel(scene->map_img, y, x + 1, PLAYERC, scene);
	mlx_put_pixel(scene->map_img, y, x + 2, PLAYERC, scene);
	mlx_put_pixel(scene->map_img, y, x - 1, PLAYERC, scene);
	mlx_put_pixel(scene->map_img, y, x - 2, PLAYERC, scene);
	mlx_put_pixel(scene->map_img, y + 1, x, PLAYERC, scene);
	mlx_put_pixel(scene->map_img, y + 2, x, PLAYERC, scene);
	mlx_put_pixel(scene->map_img, y - 1, x, PLAYERC, scene);
	mlx_put_pixel(scene->map_img, y - 2, x, PLAYERC, scene);
	}
	
	else 
	{
		printf("\n!!!Out of map: y: %d, x: %d!!!\n", y, x);
		printf("!!!Border map: y: %d, x: %d!!!\n", SEGM * scene->map_height, SEGM * scene->map_width);
	}
}

int find_closest_vert(t_scene *scene, t_player *p)
{
	double	dist_to_next_vert_intersect;
	int		dist_to_next_vert_x;

	update_dir(scene, p);
	p->next_vert_x = ((int)(p->x / SEGM) + p->x_dir) * SEGM; 
	dist_to_next_vert_x = fabs(p->x - p->next_vert_x);
	dist_to_next_vert_intersect = fabs(dist_to_next_vert_x / cos(p->angle));
	p->next_vert_y = (int)(dist_to_next_vert_intersect * sin(p->angle) +(p->y));
	return (dist_to_next_vert_intersect);
}


int find_closest_hor(t_scene *scene, t_player *p)
{
	double	dist_to_next_hor_intersect;
	int		dist_to_next_hor_y;
	int		y_dir;
	
	y_dir = p->y_dir;
	update_dir(scene, p);
	p->next_hor_y = ((int)(p->y / SEGM)) * SEGM; 
	dist_to_next_hor_y = fabs(p->y - p->next_hor_y);
	dist_to_next_hor_intersect = fabs(dist_to_next_hor_y / cos(p->angle + PI / 2));
	p->next_hor_x = (int)(dist_to_next_hor_intersect * sin(p->angle + PI / 2) + (p->x) );
	return (dist_to_next_hor_intersect);
}



void draw_player(t_scene *scene)
{
	t_player	*p;
	int			v_x;
	int			v_y;
	int			y;
	int			x;
	double		angle;
	// let it be in ray structure and this function takes angle and returns x y ray coordinates? (but I calculate intersection )
	p = scene->p;

	printf("P y: %d, x: %d\n", p->y, p->x);
	printf("a %f\n", p->angle);
	draww_point(scene, p->y, p->x);
	if (find_closest_vert(scene, p) < find_closest_hor(scene, p))
		draww_point(scene, p->next_vert_y, p->next_vert_x);
	else
		draww_point(scene, p->next_hor_y, p->next_hor_x);
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
