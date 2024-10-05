#include "cub3d.h"

int err(char *str)
{
	while (*str)
		write(2, str++, 1);
	return (1);
}

void free_null_text(t_scene *scene, int i)
{
	while(scene->texts[i] && i >= 0)
	{
		if(scene->texts[i]->key)
		{
			free(scene->texts[i]->key);
			scene->texts[i]->key = NULL;
		}
		if(scene->texts[i]->path)
        {
            free(scene->texts[i]->path);
            scene->texts[i]->path = NULL;
        }
		free(scene->texts[i]);
		scene->texts[i] = NULL;
		i--;
	}
}

void free_and_nul(char **s)
{
	while (*s)
	{
		free(*s);
		*s = NULL;
		s++;
	}
}
void free_and_nnul(char **s, int i)
{
	while (*s && i >= 0)
	{
		free(*s);
		*s = NULL;
		s++;
		i--;
	}
}

// int free_all(t_data *data, int i)
// {

// }