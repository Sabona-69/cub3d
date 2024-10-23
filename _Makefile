
NAME	= cub3D

# CC		= cc

RM		= rm -f

OBJ		= $(SRC:.c=.o)

BOBJ	= $(BSRC:.c=.o)

SRC		= mandatory/cub3d.c mandatory/get_next_line.c mandatory/utils.c \
			mandatory/parse/map.c mandatory/parse/store_instructions.c mandatory/parse/store_map.c mandatory/parse/check_walls.c\

GLFW        = -L$(HOME)/.brew/Cellar/glfw/3.4/lib -lglfw \

CFLAGS	= -g3 -fsanitize=address # -Wall -Werror -Wextra

MLX         = -L$(HOME)/MLX42/build -lmlx42

BNAME	= cub3D_bonus

LIBFTA	= libft/libft.a
LIBFT       = -L./libft -lft

all: $(NAME)

bonus: $(BNAME)

mandatory/%.o: mandatory/%.c mandatory/cub3d.h Makefile
			$(CC) $(CFLAGS) -c $<  -o $@

bonus/%.o: bonus/%.c bonus/cub3d_b.h Makefile 
			$(CC) $(CFLAGS) -c $<  -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(GLFW) libft/libft.a $(MLX)  -o $(NAME)

$(LIBFT):
			make -C libft

clean: 
	$(RM) $(OBJ) $(BOBJ)
	make -C libft/ clean

re : clean all

