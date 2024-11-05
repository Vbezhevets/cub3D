#include "cub3d.h"


void	mlx_put_pixel_to_map(int y, int x, int color, t_scene *scene)
{
	char	*dst;
	t_image	*image;

	image = scene->img_map;
	if (x >= 0 && x < SEGM * scene->map_width && y >= 0 && y < SEGM * scene->map_height)
	{
		dst = image->addr + (y * image->line_l + x * (image->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

void	draw_segm(t_scene *scene, int x_start, int y_start, int color)
{
	int	x;
	int y;

	y = 0;
	while(y < SEGM -1)
	{
		x = 0;
		while(x < SEGM - 1)
		{
			mlx_put_pixel_to_map(y_start + y, x_start + x, color, scene);
			x++;
		}
		y++;
	}
}

void	draw_2d_map(t_scene *scene, int y, int x)
{
	while(y < scene->map_height )
	{
		x = 0;
		while(x < scene->map_width)
		{
			if (scene->map[y][x] == WALL)
				draw_segm(scene, x * SEGM, y * SEGM, WALLC);
			else
				draw_segm(scene, x * SEGM, y * SEGM, CELLC);
			x++;
		}
		y++;
	}
	draww_point(scene, scene->p->y, scene->p->x, PLAYERC);
	calc_rays(scene);
}