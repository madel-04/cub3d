NAME = cub3d
CC = cc
OBJ_DIR = obj/
SRC_DIR = src/
INCLUDES = -I include/ -I libft/
LIBFT = libft/libft.a
SRC =   $(SRC_DIR)main.c

MLX 		= -L minilibx-linux -lmlx_Linux -lX11 -lXext -lm

CFLAGS = -Wall -Wextra -Werror
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
		@$(CC) $(CFLAGS) $(INCLUDES) $(MLX) -o $(NAME) $(OBJ) $(LDFLAGS)
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