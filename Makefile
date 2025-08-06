NAME = cub3d
CC = cc
OBJ_DIR = obj/
SRC_DIR = src/
INCLUDES = -I includes/ -I libft/ -I minilibx-linux/
LIBFT = libft/libft.a
SRC =   $(SRC_DIR)main/main.c \
		$(SRC_DIR)raycasting/draw_minimap.c \
		$(SRC_DIR)raycasting/draw_minimap_utils.c \
		$(SRC_DIR)raycasting/move_player.c \
		$(SRC_DIR)raycasting/raycasting_inits.c \
		$(SRC_DIR)raycasting/raycasting_utils.c \
		$(SRC_DIR)raycasting/raycasting.c \
		$(SRC_DIR)parser/parse_map.c \
		$(SRC_DIR)parser/ft_parse_x.c \
		$(SRC_DIR)parser/parser_config.c \
		$(SRC_DIR)utils/utils.c \
		$(SRC_DIR)utils/utils_array.c \
		$(SRC_DIR)utils/utils_tab.c \
		$(SRC_DIR)validations/validate_config.c \
		$(SRC_DIR)validations/validate_map.c \
		$(SRC_DIR)validations/validate_player.c \
		$(SRC_DIR)validations/validate_textures.c \
		$(SRC_DIR)data_init/config_init.c \
		$(SRC_DIR)data_init/init_game.c \
		$(SRC_DIR)data_init/set_orientation.c \
		$(SRC_DIR)frees/free.c \
		$(SRC_DIR)render/render.c \
		$(SRC_DIR)render/get_textures.c \
		$(SRC_DIR)teclas/handle_keys.c \

MLX = -Lminilibx-linux -lmlx -lX11 -lXext -lm

CFLAGS = -Wall -Wextra -Werror #-g3 -fsanitize=address
LDFLAGS = -lreadline -Llibft -lft

OBJ = $(SRC:$(SRC_DIR)%= $(OBJ_DIR)%)
OBJ := $(OBJ:.c=.o)

SANITIZER = -fsanitize=address
VALGRIND = valgrind --leak-check=full --track-origins=yes

# SANITIZER = -fsanitize=thread // -fsanitize=address
# valgrind --tool=helgrind 
# valgrind --tool=drd 

.PHONY: all clean fclean re debug

all: $(NAME)

minilibx-linux/libmlx.a:
	@echo "$(YELLOW)Compiling MinilibX library$(CLEAR)"
	@make -sC minilibx-linux

$(NAME): $(OBJ) $(LIBFT) minilibx-linux/libmlx.a
		@echo "Compilando el ejecutable: $(NAME)"
		@$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJ) $(MLX) $(LDFLAGS)
		@echo "Compilación completada"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
		@mkdir -p $(dir $@)
		@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
		@mkdir -p $(OBJ_DIR)

$(LIBFT):
	@echo "Compilando libft..."
	@make -s -C libft

clean:
	@rm -rf $(OBJ_DIR)
	@make -s fclean -C libft

fclean: clean
	@rm -f $(NAME)
	@make -s fclean -C libft

re: fclean all