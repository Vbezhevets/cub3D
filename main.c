//  Я ничего не боюсь!

#include "cub3d.h"
#include <stdio.h>

int load_scene_file(char *path, t_scene *scene)
{
	int	i;
	int	l;

	l = ft_strlen(path) - 1;
	i = 3;
	while (path[l] == MAP_EXT[i] && i > 0)
	{
		l--;
		i--;
	}
	if (!i)
		return (check_and_load_scene(path, scene));
	return (i);
}

void text_init(t_scene  *scene)
{
	int	i;

	char	*texts[4];

	texts[0] = "NO";
	texts[1] = "SO";
	texts[2] = "WE";
	texts[3] = "EA";
	i = 0;
	while (i < 4)
	{
		scene->texts[i] = malloc(sizeof(t_text));
		if (scene->texts[i])
			scene->texts[i]->key = ft_strdup(texts[i]);
		if (!scene->texts[i] || !scene->texts[i]->key)
		{
			free_null_text(scene, i--);
			exit(1);
		}
		scene->texts[i]->path = NULL;
		i++;
		scene->parsed_t = i;
	}
	scene->parsed_c = 6;
}

int init(t_scene  *scene)
{
	text_init(scene);
	scene->map = NULL;	
	scene->map_list = NULL;
	scene->map_height = 1;
	scene->pl_qty = 1;
	scene->map_width = 0;
	return (0);
}

int main (int argc, char **argv)
{
    t_scene  scene;

	init(&scene);
	
	if (argc != 2)
		printf("poshel naher\n");
    if (argc != 2 || load_scene_file(argv[1], &scene))
		exit(err("load map error\n")); // free
	start_mlx(&scene);
	//  build_2d_map(scene);
}