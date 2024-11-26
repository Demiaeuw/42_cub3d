NAME	= cub3d

SRCS	=	main.c\
			srcs/gameplay/00_gameplay.c\
			srcs/gameplay/01_deplacements.c\
			srcs/gameplay/02_aim.c\
			srcs/gameplay/03_exit.c\
			srcs/minilibx/00_init_mlx.c\
			srcs/parsing/00_parsing_error.c\
			srcs/parsing/01_parsing.c\
			srcs/parsing/02_check_argument.c\
			srcs/parsing/03_check_struct_file.c\
			srcs/parsing/04_init_game.c\
			srcs/parsing/05_path_gestion.c\
			srcs/parsing/06_color_gestion.c\
			srcs/parsing/07_map_gestion.c\
			srcs/parsing/08_map_gestion.c\
			srcs/parsing/09_map_gestion.c\
			srcs/parsing/10_player_gestion.c\
			srcs/parsing/100_print_struct.c\
			srcs/parsing/101_print_struct.c

OBJDIR	= objets
OBJS	= $(SRCS:%.c=$(OBJDIR)/%.o)

# Répertoires des librairies
LIBFT_DIR = srcs/utils/libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX_DIR = include/minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a

# Compilation
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
RM		= rm -rf

# Flags pour la minilibX et libft
MLX_FLAGS = -L$(MLX_DIR) -lmlx -L/usr/lib -lXext -lX11 -lm -lz
LIBFT_FLAGS = -L$(LIBFT_DIR) -lft

all: $(LIBFT) $(MLX_LIB) $(NAME)
	@echo "✅ Compilation terminée avec succès pour $(NAME)"

$(OBJDIR):
	@mkdir -p $(OBJDIR)/srcs/parsing $(OBJDIR)/srcs/utils $(OBJDIR)/srcs/gameplay $(OBJDIR)/srcs/minilibx


$(OBJS): $(OBJDIR)/%.o : %.c | $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

# Compilation du programme principal
$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX_FLAGS) $(LIBFT_FLAGS)

# Compilation de la libft
$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) > /dev/null
	@echo "📚 Libft compilée"

# Compilation de la minilibx
$(MLX_LIB):
	@$(MAKE) -C $(MLX_DIR) > /dev/null
	@echo "🎨 MinilibX compilée"

exe : all clean

clean:
	@$(RM) $(OBJDIR)
	@$(MAKE) -C $(LIBFT_DIR) clean > /dev/null
	@$(MAKE) -C $(MLX_DIR) clean > /dev/null
	@echo "🧹 Fichiers objets supprimés"

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean > /dev/null
	@$(RM) $(MLX_LIB)
	@echo "🧼 Nettoyage complet effectué"

re: fclean all
