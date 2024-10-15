#include "mlx_linux/mlx.h"
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

void	calc_rays(t_scene *scene)
{
	int		i;
	double	angle;

	i = 0;
	angle = scene->p->angle -  FOV / 2;
	while (i < WIDTH)
	{
		angle = update_ang(angle);
		calc_ray(scene, i, angle );
		angle +=  FOV / WIDTH;
		i++;
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

t_image	*create_mlx_img(t_scene *scene, int width, int height)
{
	t_image *image;

	image = malloc(sizeof(t_image));
	if (!image)
		exit (err("image alloc error\n")); // freeeeeee
	image->img = mlx_new_image(scene->mlx, width, height);
	if (!image->img)
		exit(err("image error\n")); // freee
	image->addr = mlx_get_data_addr(image->img, &image->bpp, &image->line_l, &image->endian);
	return (image);
}
int	mlx_stop(t_scene *scene, int status)
{
	// free_img(data);
	printf("GOOD BYE!!!\n");
	mlx_destroy_window(scene->mlx, scene->win_map);
	mlx_destroy_display(scene->mlx);
	// free_data_map(data);
	free(scene->mlx);
	exit(status);
	return (0);
}

int	key_pressed(int key, t_scene *scene)
{
	scene->p->angle = update_ang(scene->p->angle);
	scene->p->x_dir = get_x_dir(scene->p->angle);
	scene->p->y_dir = get_y_dir(scene->p->angle);
	if (key == W)
		move_forward(scene, scene->p->angle, get_x_dir(scene->p->angle), get_y_dir(scene->p->angle));
	if (key == S)
		move_back(scene, scene->p->angle, get_x_dir(scene->p->angle), get_y_dir(scene->p->angle));
	if (key == A)
		move_left(scene, scene->p->angle);
	if (key == D)
		move_right(scene, scene->p->angle);
	if (key == TURN_L)
		turn_left(scene);
	if (key == TURN_R)
		turn_right(scene);
	if (key == ESC)
		mlx_stop(scene, 0);
	draw_2d_map(scene, 0, 0);
	mlx_clear_window(scene->mlx, scene->win_map);
	mlx_put_image_to_window(scene->mlx, scene->win_map, scene->img_map->img, 0, 0);
	draw_3d(scene, 0, 0);
	mlx_clear_window(scene->mlx, scene->win_3d);
	mlx_put_image_to_window(scene->mlx, scene->win_3d, scene->img_3d->img, 0, 0);
	return (0);
}

int	start_mlx(t_scene *scene)
{
	scene->mlx = mlx_init();
	if (!scene->mlx)
		return (err("mlx error\n"));
	scene->win_map = mlx_new_window(scene->mlx, SEGM * scene->map_width, SEGM * scene->map_height, "2d map");
	//if
	scene->img_map = create_mlx_img(scene, SEGM * scene->map_width, SEGM * scene->map_height);
	draw_2d_map(scene, 0, 0);
	mlx_put_image_to_window(scene->mlx, scene->win_map, scene->img_map->img, 0, 0);

	scene->win_3d = mlx_new_window(scene->mlx, WIDTH, HEIGHT, "3d scene");
	scene->img_3d = create_mlx_img(scene, WIDTH, HEIGHT);
	draw_3d(scene, 0, 0);
	mlx_put_image_to_window(scene->mlx, scene->win_3d, scene->img_3d->img, 0, 0);

	mlx_key_hook(scene->win_map, key_pressed, scene);
	mlx_hook(scene->win_map, 17, 0L, mlx_stop, scene);

	mlx_loop(scene->mlx);
	return (0);
}
