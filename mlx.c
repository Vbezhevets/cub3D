#include "mlx_linux/mlx.h"
#include "cub3d.h"


void    mlx_put_pixel(t_image *image, int y, int x, int color, t_scene *scene)
{
	char    *dst;

	if (x >= 0 && x < SEGM * scene->map_width && y >= 0 && y < SEGM * scene->map_height)
	{
		dst = image->addr + (y * image->line_l + x * (image->bpp / 8));
		*(unsigned int *)dst = color;
	}
	else
		printf("error coor: y: %d, x: %d\n", y, x);
}



void draw_segm(t_scene *scene, t_image *image, int x_start, int y_start, int color)
{
	int	x;
	int y;

	y = 0;
	while(y < SEGM -1)
	{
		x = 0;
		while(x < SEGM - 1)
		{
			mlx_put_pixel(scene->map_img, y_start + y, x_start + x, color, scene);
			x++;
		}
		y++;
	}
}

void draw_2d_map(t_scene *scene, int y, int x)
{
	while(y < scene->map_height )
	{
		x = 0;
		while(x < scene->map_width)
		{
			if (scene->map[y][x] == WALL)
				draw_segm(scene, scene->map_img, x * SEGM, y * SEGM, WALL2D);
			else
				draw_segm(scene, scene->map_img, x * SEGM, y * SEGM, CELL2D);
			x++;
		}
		y++;
	}
	printf("\n y: %d, x: %d!!!\n", scene->p->y,scene->p->x);

	draww_point(scene, scene->p->y, scene->p->x, PLAYERC);

	calc_ray(scene);
}

t_image	*create_mlx_img(t_scene *scene)
{
	t_image *image;

	image = malloc(sizeof(t_image));
	if (!image)
		exit (err("image alloc error\n")); // freeeeeee
	image->img = mlx_new_image(scene->mlx, SEGM * scene->map_width, SEGM * scene->map_height);
	if (!image->img)
		exit(err("image error\n")); // freee
	image->addr = mlx_get_data_addr(image->img, &image->bpp, &image->line_l, &image->endian);
	return (image);
}
int	mlx_stop(t_scene *scene, int status)
{
	// free_img(data);
	printf("GOOD BYE!!!\n");
	mlx_destroy_window(scene->mlx, scene->win_2d);
	mlx_destroy_display(scene->mlx);
	// free_data_map(data);
	free(scene->mlx);
	exit(status);
	return (0);
}
int	key_pressed(int key, t_scene *scene)
{
	update_dir(scene, scene->p);
	if (key == W)
		move_forward(scene, scene->p->angle);
	if (key == S)
		move_back(scene, scene->p->angle);
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
	if (scene->p->angle > 2 * PI)
		scene->p->angle = scene->p->angle - 2 * PI;
	// scene->p->angle = 2;
	printf("PRESSED\n");
	draw_2d_map(scene, 0, 0);
	mlx_clear_window(scene->mlx, scene->win_2d);
	mlx_put_image_to_window(scene->mlx, scene->win_2d, scene->map_img->img, 0, 0);

	return (0);
}



int start_mlx(t_scene *scene)
{
	scene->mlx = mlx_init();
	if (!scene->mlx)
		return (err("mlx error\n"));
	scene->win_2d = mlx_new_window(scene->mlx, SEGM * scene->map_width, SEGM * scene->map_height, "2d map");
	//if
	scene->map_img = create_mlx_img(scene);
	draw_2d_map(scene, 0, 0);
	mlx_put_image_to_window(scene->mlx, scene->win_2d, scene->map_img->img, 0, 0);
	
	mlx_key_hook(scene->win_2d, key_pressed, scene);
	mlx_hook(scene->win_2d, 17, 0L, mlx_stop, scene);
	
	mlx_loop(scene->mlx);
	return (0);
}
 