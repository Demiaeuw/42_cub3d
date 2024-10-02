NAME	= cub3d

SRCS	=	/srcs/error.c\
			/srcs/parsing.c
OBJS	= $(SRCS:srcs/%.c=objets/%.o)

MLX_DIR	= include/minilibx-linux
MLX_LIB	= $(MLX_DIR)/libmlx.a

CC	= gcc
CFLAGS	= -Wall -Wextra -Werror
RM	= rm -rf
OBJDIR	= objets

MLX_FLAGS = -L$(MLX_DIR) -lmlx -L/usr/lib -lXext -lX11 -lm -lz

all: $(MLX_LIB) $(NAME)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

$(NAME): $(OBJDIR) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX_FLAGS)

objets/%.o: srcs/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJDIR)
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(MLX_DIR) fclean

re: fclean all
