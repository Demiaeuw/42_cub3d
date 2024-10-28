NAME	= cub3d

SRCS	=	main.c\
			srcs/00_error.c\
			srcs/01_parsing.c\
			srcs/02_parsing_file01.c\
			srcs/02_parsing_file02.c\
			srcs/03_check_infofile.c\
			srcs/04_check_map00.c\
			include/utils/utils00.c\
			include/utils/utils01.c\
			include/utils/utils02.c\
			include/utils/utils_parsing.c\
			include/utils/gnl/00_gnl.c\
			include/utils/gnl/01_gnl.c

OBJS	= $(SRCS:srcs/%.c=objets/%.o)

# MLX_DIR	= include/minilibx-linux
# MLX_LIB	= $(MLX_DIR)/libmlx.a

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
# $(MAKE) -C $(MLX_DIR) clean

fclean: clean
	$(RM) $(NAME)
# $(MAKE) -C $(MLX_DIR) fclean

re: fclean all
