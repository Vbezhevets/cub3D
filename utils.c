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


int not_wall(t_scene *scene, int x, int y, char *str)
{
	t_player	*p;
    int         add_x;
    int         add_y = 0;

	p = scene->p;
    if (p->x_dir == -1)
        add_x = -1;
    else
        add_x = 0;
    if (p->y_dir == -1)
        add_y = -1;
    else
        add_y = 0;

	if(scene->map[y / SEGM ][x / SEGM + add_x] != WALL) //  + p->y_dir +
    	return(1);
    return (0);
}

int not_wall_hor(t_scene *scene, int x, int y, char *str)
{
	t_player	*p;
    int         add_x = 0;
    int         add_y = 0;

	p = scene->p;
	update_dir(scene, p);

    // if (p->x_dir == -1)
    //     add_x = -1;
    // else
    //     add_x = 0;
    if (p->y_dir == -1)
        add_y = -1;
    else
        add_y = 0;


	if(scene->map[y / SEGM + add_y][x / SEGM] != WALL) //  + p->y_dir +
    	return(1);
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
	            mlx_put_pixel(scene->map_img, y, x, color, scene);
            x = oldx;
            y++;
        }
	}
	else
	{
		printf("\n!!!Out of map: y: %d, x: %d!!!\n", y, x);
		printf("!!!Border map: y: %d, x: %d!!!\n", SEGM * scene->map_height, SEGM * scene->map_width);
	}
}

