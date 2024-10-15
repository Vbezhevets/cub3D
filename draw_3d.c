#include "cub3d.h"
void	mlx_put_pixel_to_3d(int y, int x, int color, t_scene *scene)
{
	char	*dst;
	t_image	*image;

	image = scene->img_3d;
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		dst = image->addr + (y * image->line_l + x * (image->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

void draw_bg(t_scene *scene, int y, int x)
{
	while (y < HEIGHT / 2)
	{
		while(x < WIDTH)
		{
			mlx_put_pixel_to_3d(y, x, scene->ceiling_rgb, scene);
			x++;
		}
		x = 0;
		y++;
	}
	while (y < HEIGHT)
	{
		while(x < WIDTH)
		{
			mlx_put_pixel_to_3d(y, x, scene->floor_rgb, scene);
			x++;
		}
		y++;
		x = 0;
	}
}

void	draw_3d(t_scene *scene, int y, int x)
{
	int	strap;
	int i;

	i = 0;
	draw_bg(scene, 0, 0);

	while (x < WIDTH)
	{
	
		while(y < strap)
		{
			strap =   HEIGHT * (20 * tan(VFOV)) / scene->ray[x]->dist ;
			// printf("strap - %d, ray dist %d, ", strap, scene->ray[WIDTH / 2]->dist);
			mlx_put_pixel_to_3d( HEIGHT / 2 + y, x, WALLC, scene);
			mlx_put_pixel_to_3d( HEIGHT / 2 - y, x, WALLC, scene);
			y++;
		}
		x++;
		y = 0;
	}
}