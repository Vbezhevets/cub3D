#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "cub3d.h"
#include "libft/libft.h"
#include <math.h>


int parse_texts(t_scene *scene, char *str, t_text **loaded, int i)
{
	int l;

	while (++i < 4 && scene->parsed_t)
	{
		if (!ft_strncmp(loaded[i]->key, str, 2))
		{
			if (loaded[i]->path)
				return(err("dublicate texture?? No\n"));
			str += 2;
			while (*str && (*str == ' '))
				str++;
			l = ft_strlen(str);
			while (l && (str[l] == ' '))
				l--;
			if (!l)
				return(err("text string error\n"), i);
			loaded[i]->path = malloc(sizeof(char) * (l + 1));
			if (!loaded[i]->path)
				return(err("mlc error\n"), i);
			ft_strcpy(loaded[i]->path, str);
			scene->parsed_t--;
		}
	}
	return (0);
}

	// i++;
	// while (str[i] && (str[i] == ' ' || str[i] == '\t'  || str[i] == ','  || ft_isdigit(str[i])))
	// 	i++;
int parse_cfcolor(char *str, t_scene *scene, int k, int res)
{
	char	**spl;

	if (!scene->parsed_c || *str != 'F' && *str != 'C')
		return (0);
	spl = ft_split(str  + 1, ',');
	while (spl[k])
	{
		if (*str == 'F')
		{
			scene->floor_rgb[k] = ft_atoi(spl[k]);
			if (scene->floor_rgb[k] < 0 || scene->floor_rgb[k] > 255)
				res = 1;
		}
		if (*str == 'C')
		{
			scene->ceiling_rgb[k] = ft_atoi(spl[k]);
			if (scene->ceiling_rgb[k] < 0 || scene->ceiling_rgb[k] > 255)
				res = 1;
		}
		k++;
		scene->parsed_c--;
	}
	free_and_nul(spl);
	free(spl);
	return(res);
}

int parse_before_map(char *str, t_scene *scene)
{
	int i;

	while (*str && (*str == ' '))
		str++;
	if (!str || '\n' == str[0])
		return (0);
	// if (scene->parsed_t)
	i = parse_texts(scene, str, scene->texts, -1);

	if (i || parse_cfcolor(str, scene, 0, 0) || scene->parsed_c < 0	)
		return (free_null_text(scene, i), get_next_line(-42), err("texture error\n"));	
	return (0);
}

int map_to_array(t_scene *scene, t_map_line *list)
{
	int	i;
	int	k;

	i = 0;
	scene->map = malloc(sizeof(char *) * (scene->map_height));
	if (!scene->map)
		return (err("malloc error\n"));
	while(i < scene->map_height)
	{
		k = -1;
		scene->map[i] = malloc(sizeof(char) * (scene->map_width + 1));
		if (!scene->map[i])
			return(free_and_nnul(scene->map, i--), free(scene->map), err("alloc error\n"));
		while(++k < ft_strlen(list->str) - 1)
			scene->map[i][k] = list->str[k];
		while(k < scene->map_width)
		{
			scene->map[i][k] = ' ';
			k++;
		}
		scene->map[i][k] = '\0';
		list = list->next;
		i++;
	}
	return (0);
}

t_map_line *line_init(char *line, t_scene *scene)
{
	t_map_line *temp;

	temp = malloc(sizeof(t_map_line));
	if (!temp)
		return(NULL);
	temp->str = malloc(sizeof(char) * (ft_strlen(line) + 1));
	if (ft_strlen(line) > scene->map_width)
		scene->map_width = ft_strlen(line );
	ft_strcpy(temp->str, line);
	if (!temp->str)
		return(free(temp), NULL);
	temp->next = NULL;
	return (temp);
}

int load_list_map(t_scene *scene, int fd, char *line)
{
	t_map_line	*temp;
	t_map_line	*map_line;
	
	while (line)
	{
		if (ft_strsetchr(line, "10NSEW \n"))
			return (err("wrong symbol - "));
		temp = line_init(line, scene);
		if (!temp)
			return(err("alloc error\n"));
		if (!scene->map_list)
		{
			scene->map_list = temp;
			map_line = scene->map_list;
		}
		else
		{
			map_line->next = temp;
			map_line = map_line->next;
		}
		scene->map_height++;
		line = get_next_line(fd);
	}
	scene->map_height--;
	return (0);
}

int is_border(char **map, int y, int x, int y_max, int x_max)
{
	if (y == 0 || (map[y - 1][x] == ' '))
		return (1);
	if (x == 0 || (map[y][x - 1] == ' '))
		return (1);
	if (x == x_max || (map[y][x + 1] == ' '))
		return (1);
	if (y == y_max || map[y + 1][x] == ' ')
		return(1);
	return (0);
}

int init_player(t_scene *scene, char direct, int y,  int x)
{
	t_player	*p;

	p = malloc(sizeof(t_player));
	if (!p)
		return (1);// 
	p->y = y * SEGM + SEGM / 2;
    p->x = x * SEGM + SEGM / 2;
	if (direct == 'N')
		p->angle = PI / 2;
	if (direct == 'E')
		p->angle = 0;
	if (direct == 'W')
		p->angle = PI;
	if (direct == 'S')
		p->angle = PI * 1.5; //270
	scene->p = p;
	return (0);
}

int check_map(char **map, int y_max, int x_max, t_scene *scene)
{
	int	y;
	int	x;

	y = 0;
	while(y < y_max)
	{	
		x = 0;
		while (x < x_max - 1)
		{
			if (map[y][x] != ' ' && map[y][x] != '\n')
			{
				if (is_border(map, y, x, y_max - 1, x_max) &&  map[y][x] != '1')
					return (printf("x: %d,   y: %d,   = %c\n",x , y ,map[y][x]), 1);
				if (ft_strchr("NSEW", map[y][x]) && scene->pl_qty--)
					if (init_player(scene, map[y][x], y, x))
						return (err("alloc p error"));
			}
			x++;
		}
		y++;
	}
	return (scene->pl_qty);
}


int check_and_load_scene(char *path, t_scene  *scene)
{
	int			fd;
	char		*line;

	if ((fd = open(path, O_RDONLY)) < 0)
		return (err ("error open map file\n"));
	line = get_next_line(fd);
	while (line && (scene->parsed_c || scene->parsed_t))
	{
		if (parse_before_map(line, scene))
			return(close(fd), 1);
		line = get_next_line(fd);
	}
	if (load_list_map(scene, fd, get_next_line(fd)))
		return(close(fd), err("map error\n"));
	if (map_to_array(scene, scene->map_list))
		return (close(fd), 1);	
	if (check_map(scene->map, scene->map_height, scene->map_width, scene))
		return (err("wrong map!!\n"), close(fd), 1);
	scene->map_width--;
	return (close(fd), 0);
}
