#include "cub3d.h"

void temp_text_create(t_image *image)
{
	char	*dst;
	int		color;
	int	x = 0;
	int y = 0;

	while (y < T_HEIGHT)
	{
		while (x < T_HEIGHT)
		{
			if (y % 10 == 0 ||  x % 10 == 0)
				color = CELLC;
			else
				color = WALLC;
			dst = image->addr + (y * image->line_l + x * (image->bpp / 8));
			*(unsigned int *)dst = color;
		}
		x = 0;
		y++;
	}
}

void load_text(t_scene *scene)
{
	int		i;
	int		width;
	int		height;
	t_image*image;

	width = T_WIDTH; // ?
	height = T_HEIGHT; // ?
	i = 0;
	while(i < 4)
	{
		image = malloc(sizeof(t_image));
		if (!image)
			exit (err("txt image alloc error\n")); // freeeeeee
		/*
		image->img = mlx_xpm_file_to_image(scene->mlx, scene->texts[i]->path, &width, &height);
		printf("%s\n", scene->texts[i]->path);
		*/
image->img = mlx_new_image(scene->mlx, width, height);
		if (!image->img)
			exit(err("image error\n")); // freee

		image->addr = mlx_get_data_addr(image->img, &image->bpp, &image->line_l, &image->endian);
		scene->texts[i]->txt_image = image;
		i++;
	}
}
