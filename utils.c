#include "cub3d.h"

int ft_strsetchr(char *str, char *set)
{
    int i;

    while (*str)
    {
        i = 0;
        while (set[i] )
        {
            if (str[i] == *str)
                break;
            printf("%c", *str);
            i++;
            if (!set[i])
                return(*str);
        }
        str++;
    }
    return 0;
}

int		is_inside_map(t_scene *scene, int x, int y)
{
    if ((x >= 0 && x < scene->map_width * SEGM) &&
        (y >= 0 && y < scene->map_height * SEGM))
            return (1);
    return (0);
}

int get_x_dir(double angle)
{
	if ((angle >= 0 && angle <= PI / 2) || (angle >= PI * 1.5 && angle <= PI * 2))
		return 1;
	else 
		return -1;
}
int get_y_dir(double angle)
{
	if (angle >= PI && angle <= PI * 2 || angle == 0)
		return 1;
	else 
		return -1;
}

double update_ang(double angle)
{
    angle = fmod(angle, PI * 2);
    if (angle < 0)
        angle = angle + PI * 2;
    return (angle);
}

void update_dir(t_scene *scene, t_ray *ray)
{

	ray->x_dir = get_x_dir(ray->angle);
	ray->y_dir = get_y_dir(ray->angle);

	if (ray->angle == 0)
	{
		ray->y_dir = 1;
		ray->x_dir = 1;
	}
	ray->angle = update_ang(ray->angle);
}

int not_wall(t_scene *scene, int x, int y, t_ray *ray)
{
    int	add_x;

	update_dir(scene, ray);
    if (ray->x_dir == -1)
        add_x = -1;
    else
        add_x = 0;
	if(scene->map[y / SEGM ][x / SEGM + add_x] != WALL)
    	return(1);
    return (0);
}

int not_wall_hor(t_scene *scene, int x, int y, t_ray *ray)
{
    int	add_y;

	update_dir(scene, ray);
    if (ray->y_dir == -1)
        add_y = -1;
    else
        add_y = 0;
	if(scene->map[y / SEGM + add_y][x / SEGM] != WALL)
        return (1);
    else
        return (0);
}

void draww_point(t_scene *scene, int y, int  x, int color)
{
    int d = 30;
    int maxy = y + SEGM / d;
    int maxx = x + SEGM / d;
    int oldx = x - SEGM / d;

    y -= SEGM / d;
    if (y <0)
        y = 0;
    if  (oldx <0)
        oldx =0;
	if (x >= 0 && x < SEGM * scene->map_width && y >= 0 && y < SEGM * scene->map_height)
	{
        while (y <= maxy)
        {
            while (++x <= maxx)
	            mlx_put_pixel_to_map(y, x, color, scene);
            x = oldx;
            y++;
        }
	}
	// else
	// {
	// 	printf("\n!!!Out of map: y: %d, x: %d!!!\n", y, x);
	// 	printf("!!!Border map: y: %d, x: %d!!!\n", SEGM * scene->map_height, SEGM * scene->map_width);
	// }
}

