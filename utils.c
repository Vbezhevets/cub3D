#include "cub3d.h"


int (ft_strsetchr(char *str, char *set))
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
/*
void draw_player(t_scene *scene, int y, int x)
{
	mlx_put_pixel(scene->img_player, y, x, PLAYERC);
}

int start_mlx(t_scene *scene)
{
    t_image *image;
	t_image *player;

    scene->mlx = mlx_init();
    if (!scene->mlx)
        return (err("mlx error\n"));

    scene->win_2d = mlx_new_window(scene->mlx, SEGM * scene->map_width, SEGM * scene->map_height, "2d map");
    image = malloc(sizeof(t_image));
    if (!image)
        return (err("image alloc error\n"));
    scene->image = image;
    player = malloc(sizeof(t_image));
	if (!player)
        return (err("image alloc error\n"));
    scene->img_player = player;
    image->img = mlx_new_image(scene->mlx, SEGM * scene->map_width, SEGM * scene->map_height);
    if (!image->img) 
        return (err("image error\n"));
    image->addr = mlx_get_data_addr(image->img, &image->bpp, &image->line_l, &image->endian);
    mlx_put_image_to_window(scene->mlx, scene->win_2d, image->img, 0, 0);
	draw_2d_map(scene, 0, 0);
 	player->img = mlx_new_image(scene->mlx,  SEGM  * scene->map_width, SEGM * scene->map_height);
	player->addr = mlx_get_data_addr(player->img, &player->bpp, &player->line_l, &player->endian);
	// draw_player(scene, scene->p_y, scene->p_x);
    mlx_loop(scene->mlx);
    return (0);
}

} */