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

# define    WALL '1'

# define    SEGM 50
# define	STEP 10
# define    CELLC 0x00D3D3D3
# define    WALLC 0x008B8B8B
# define    PLAYERC 0x00FF0000
# define    WIDTH 1280 // 640
# define    HEIGHT 960 //480
# define	PI 3.1415926
# define    FOV 1.047
# define    VFOV 0.87

#define		T_WIDTH 80//751
#define		T_HEIGHT 80//749


# define	V 70 //px (hypotinuse) ray vector 2d vis 

# define	A 97
# define	D 100
# define	W 119
# define 	S 115
# define	TURN_L 65361
# define	TURN_R 65363
# define 	ESC 65307


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

typedef		struct s_text
{
	char	*key;
	char	*path;
	t_image	*txt_image;
	// char	*txt_data;
}			t_text;

typedef struct s_player
{
	int		y;
	int		x;
	double	angle;
	int		x_dir;
	int		y_dir;
}	t_player;

typedef struct s_ray
{
	double	angle;
	int		dist;

	int		vert_dist;
	int		next_vert_y;
	int		next_vert_x;

	int		hor_dist;
	int		next_hor_y;
	int		next_hor_x;
	int		x_dir;
	int		y_dir;
}	t_ray;

typedef 	struct s_scene
{

	t_text		*texts[4];
	int			parsed_t;
	int			floor_rgb;
	int			ceiling_rgb;
	int			parsed_c;

	t_map_line	*map_list;
	int			map_height; //lines quntity
	int			map_width;
	char		**map;

	t_player	*p;

	t_ray		*ray[WIDTH];

	void		*mlx;
	void		*win_map;
	t_image		*img_map;

	void		*win_3d;
	t_image		*img_3d;


	// t_image		*p_img;

	int 		pl_qty;

}					t_scene;




int		check_and_load_scene(char *path, t_scene  *scene);
void	load_text(t_scene *scene);
int		start_mlx(t_scene *scene);
void    mlx_put_pixel_to_map(int y, int x, int color, t_scene *scene);


int		init_player(t_scene *scene, char direct, int y, int x);
void	calc_ray(t_scene *scene, int, double angle);
void	calc_rays(t_scene *scene);
int		get_x_dir(double angle);
int		get_y_dir(double angle);
double	update_ang(double angle);
void	update_dir(t_scene *scene, t_ray *ray);


int		ft_strsetchr(char *str, char *set);
int		is_inside_map(t_scene *scene, int x, int y);
int		not_wall_vert(t_scene *scene, int x, int y, t_ray *ray);
int		not_wall_hor(t_scene *scene, int x, int y, t_ray *ray);

void	draww_point(t_scene *scene,  int  y, int x, int color);
void	draw_2d_map(t_scene *scene, int y, int x);

void	free_null_text(t_scene *scene, int i);
int		err(char *str);
void 	free_and_nul(char **s);
void 	free_and_nnul(char **s, int i);

void	move_forward(t_scene *scene, double	angle, int x_dir, int y_dir);
void	move_back(t_scene *scene, double angle, int x_dir, int y_dir);
void	move_left(t_scene *scene, double angle);
void	move_right(t_scene *scene, double angle);
void	turn_left(t_scene *scene);
void	turn_right(t_scene *scene);

void	draw_bg(t_scene *scene, int y, int x);
void	draw_3d(t_scene *scene, int y, int x);




#endif