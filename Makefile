#===============================================================================#
#								SOURCES											#
#===============================================================================#

PARSING_DIR	= parsing
INIT_DIR	= init
KEYHOOK_DIR	= key_hook
MOVE_DIR	= move
DRAW_DIR	= draw
COLOR_DIR	= color
FREE_DIR	= free
BONUS_DIR	= bonus

SRC_FILES = $(addprefix $(INIT_DIR)/, init.c init2.c) \
			$(addprefix $(PARSING_DIR)/, parse_map.c parse_map_utils.c set_infos.c valid_map.c set_map.c surrounded_by_walls.c) \
			$(addprefix $(KEYHOOK_DIR)/, key_hook.c) \
			$(addprefix $(MOVE_DIR)/, move.c) \
			$(addprefix $(DRAW_DIR)/, draw_ray.c texture.c) \
			$(addprefix $(COLOR_DIR)/, color.c) \
			$(addprefix $(FREE_DIR)/, free.c) \
			main.c


 #=============================================================================#
#									OBJETS										#
 #=============================================================================#

OBJS_DIR = objects
OBJS = $(SRC_FILES:%.c=$(OBJS_DIR)/%.o)
DEPS = $(SRC_FILES:%.c=$(OBJS_DIR)/%.d)

 #=============================================================================#
#									LIBRARY										#
 #=============================================================================#

LIB_DIR = libft

 #=============================================================================#
#									COMPILATION									#
 #=============================================================================#

CC = cc
CFLAGS = -g3 -Wall -Wextra -Werror
CDFLAGS = -MMD -MP
CIFLAGS = -Iincludes -I$(LIB_DIR)/includes -Imlx/mlx
CLFLAGS = -L$(LIB_DIR) -lft
MLX_DIR = mlx
MLX = $(MLX_DIR)/libmlx.a
MLXFLAGS = -L. -lXext -lX11 -lm

 #=============================================================================#
#									MAKEFILE									#
 #=============================================================================#

NAME = cub3D

all : $(NAME)


$(NAME) : $(OBJS_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(CIFLAGS) $(OBJS) $(CLFLAGS) $(MLX) $(MLXFLAGS) -o $(NAME)

$(MLX):
		$(MAKE) -C $(MLX_DIR)

$(OBJS_DIR) :
	$(MAKE) -C $(LIB_DIR)
	mkdir -p $(OBJS_DIR)/$(PARSING_DIR)
	mkdir -p $(OBJS_DIR)/$(INIT_DIR)
	mkdir -p $(OBJS_DIR)/$(KEYHOOK_DIR)
	mkdir -p $(OBJS_DIR)/$(MOVE_DIR)
	mkdir -p $(OBJS_DIR)/$(DRAW_DIR)
	mkdir -p $(OBJS_DIR)/$(COLOR_DIR)
	mkdir -p $(OBJS_DIR)/$(FREE_DIR)


$(OBJS) : $(OBJS_DIR)/%.o : %.c
	$(CC) $(CFLAGS) $(CDFLAGS) $(CIFLAGS) -c $< -o $@

bonus :
	make -C bonus all
	cp bonus/$(NAME)_bonus .

clean :
	$(MAKE) clean -C $(LIB_DIR)
	rm -rf $(OBJS_DIR)
	make -C bonus clean

fclean: clean
	rm -rf $(NAME) $(NAME)_bonus
	make -C bonus fclean

re : fclean all

-include $(DEPS)

.PHONY: all bonus clean fclean re

#.SILENT: