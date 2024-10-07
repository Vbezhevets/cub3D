#include <math.h>
#include <stdio.h>
#include "cub3d.h"

int init_player(t_scene *scene, char direct, int y,  int x)
{
	t_player	*p;

	p = malloc(sizeof(t_player));
	if (!p)
		return (1);// 
	p->y = y * SEGM + SEGM / 2 - 10;
    p->x = x * SEGM + SEGM / 2 - 10;
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

	printf("\nVERT:\n");
	
	p->next_vert_x = ((int)(p->x / SEGM) + p->x_dir) * SEGM;
	printf("next_vert_x %d\n", p->next_vert_x);
	dist_to_next_vert_x = fabs(p->x - p->next_vert_x);
	printf("dist_to_next_vert_x %d\n", dist_to_next_vert_x);
	dist_to_next_vert_intersect = fabs(dist_to_next_vert_x / cos(p->angle));
	printf("dist_to_next_vert_intersect %f\n", dist_to_next_vert_intersect );
	p->next_vert_y = (int)(dist_to_next_vert_intersect * sin(p->angle) * -1 +(p->y));
	printf("next_vert_y %d\n", p->next_vert_y);
	return (dist_to_next_vert_intersect);
}


int find_closest_hor(t_scene *scene, t_player *p)
{
	double	dist_to_next_hor_intersect;
	int		dist_to_next_hor_y;
	int		y_dir;
	
	// y_dir = p->y_dir;
	printf("\nHOR:\n");

	p->next_hor_y = ((int)(p->y / SEGM + p->y_dir)) * SEGM; 
	printf("next_hor_y %d\n", p->next_hor_y );
	dist_to_next_hor_y = fabs(p->y - p->next_hor_y);
	printf("dist_to_next_hor_y %d\n", dist_to_next_hor_y);
	dist_to_next_hor_intersect = fabs(dist_to_next_hor_y / cos(p->angle + PI / 2));
	printf("dist_to_next_hor_intersect %f\n", dist_to_next_hor_intersect );
	p->next_hor_x = (int)(dist_to_next_hor_intersect * sin(p->angle + PI / 2) + (p->x) );
	printf("next_hor_x %d\n", p->next_hor_x );

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
	update_dir(scene, p);
	printf("dir: y_dir %d, x_dir %d\n", p->y_dir, p->x_dir);
	
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
