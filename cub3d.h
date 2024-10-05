#ifndef CUB3D
#define CUB3D

# include "libft/libft.h"
# include "mlx_linux/mlx.h"
# include <X11/Xlib.h>
# include <fcntl.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>

# define MAP_EXT ".cub"

typedef struct s_ray
{
}	t_ray;

typedef		struct s_text
{
	char	*key;
	char	*path;
}			t_text;

typedef		struct s_map_line
{
	struct s_map_line	*next;
	char				*str;
}			t_map_line;

typedef struct s_image
{
	void 	*img;
	char 	*addr;
	int		bpp;
	int		line_l;
	int		endian;
}		t_image;


typedef struct s_player
{
	int		y;
	int		x;
	double	angle;
	int		next_hor_y;
	int		next_hor_x;
	int		next_vert_y;
	int		next_vert_x;
	// int		v_x; //vector
	// int		v_y; //vector
	int		x_dir;
	int		y_dir;
}	t_player;

typedef 	struct s_scene
{
	t_text		*texts[4];
	int			parsed_t;
	int			floor_rgb[3];
	int			ceiling_rgb[3];
	int			parsed_c;

	t_map_line	*map_list;
	int			map_height; //lines quntity
	int			map_width;
	char		**map;

	t_player	*p;

	void		*mlx;
	void		*win_2d;
	t_image		*map_img;

	t_image		*p_img;

	int 		pl_qty;

}					t_scene;

# define    SEGM 40
# define    CELL2D 0x00D3D3D3
# define    WALL2D 0x008B8B8B
# define    PLAYERC 0x00FF0000
# define    FOV 60
# define	PI 3.1415926
# define	V 70 //px (hypotinuse) ray vector 2d vis 

# define	A 97
# define	D 100
# define	W 119
# define 	S 115
# define	TURN_L 65361
# define	TURN_R 65363
# define 	ESC 65307


int		check_and_load_scene(char *path, t_scene  *scene);

int		start_mlx(t_scene *scene);
void    mlx_put_pixel(t_image *image, int y, int x, int color, t_scene *scene);

void	draw_player(t_scene *scene);


int		ft_strsetchr(char *str, char *set);

void	free_null_text(t_scene *scene, int i);
int		err(char *str);
void 	free_and_nul(char **s);
void 	free_and_nnul(char **s, int i);

void    move_forward(t_scene *scene);
void    move_back(t_scene *scene);
void    move_left(t_scene *scene);
void    move_right(t_scene *scene);
void    turn_left(t_scene *scene);
void    turn_right(t_scene *scene);



#endif