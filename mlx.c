#include "mlx_linux/mlx.h"
#include "cub3d.h"


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
	load_text(scene);

	scene->win_3d = mlx_new_window(scene->mlx, WIDTH, HEIGHT, "3d scene");
	scene->img_3d = create_mlx_img(scene, WIDTH, HEIGHT);
	draw_3d(scene, 0, 0);
	mlx_put_image_to_window(scene->mlx, scene->win_3d, scene->img_3d->img, 0, 0);

	mlx_key_hook(scene->win_map, key_pressed, scene);
	mlx_hook(scene->win_map, 17, 0L, mlx_stop, scene);
	mlx_loop(scene->mlx);
	return (0);
}
