NAME	= cub3D

CC		= cc
CFLAGS	= -g #-Wall -Wextra -Werror

MLX_DIR	= ./mlx_linux
MLX_LIB	= -L$(MLX_DIR) -lmlx -lX11 -lXext -lbsd

LIBDIR	= ./libft
LIBFT	= $(LIBDIR)/libft.a

SRCS    := main.c	 errors_frees.c parse_map_file.c utils.c mlx.c \
					ray.c moves.c draw_3d.c text.c draw_2d.c
OBJS    := $(SRCS:.c=.o)

%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $< -I$(LIBDIR) -I$(MLX_DIR)

$(NAME)	: $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(MLX_LIB) -L$(LIBDIR) -lft -lm 

$(LIBFT):
	make -C $(LIBDIR) all

all		: $(NAME)

# bonus	: all

clean	:
	make -C $(LIBDIR) clean
	rm -f $(OBJS)

fclean	: clean
	make -C $(LIBDIR) fclean
	rm -f $(NAME)

re		: fclean all

.PHONY: all clean fclean re